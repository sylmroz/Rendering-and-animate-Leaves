#include "OBJLoader.h"
#include <algorithm>
#include <functional>
#include <algorithm>

OBJLoader::OBJLoader(){}
OBJLoader::OBJLoader(const std::string& FileName)
{
	if (LoadFile(FileName) == GL_FALSE)
		std::cout << "Cannot load " << FileName << "\n";
}

GLint OBJLoader::AddVertex(const vector4<GLint> fvtnm, const std::vector<glm::vec4>& vtemp, const std::vector<glm::vec4>& vttemp, const std::vector<glm::vec3>& vntemp, std::map<vector4<GLint>, GLint>& indextemp)
{
	GLint index = -1;
	if (indextemp.find(fvtnm) == indextemp.end())
	{
		index = static_cast<GLint>(v.size());
		if (fvtnm.x >= 0)
			v.push_back(vtemp[fvtnm.x]);
		if (fvtnm.y >= 0)
			vt.push_back(vttemp[fvtnm.x]);
		else if (vttemp.size() > 0)
			vt.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (fvtnm.z >= 0)
			vn.push_back(vntemp[fvtnm.x]);
		if (fvtnm.w >= 0)
			index_materials.push_back(fvtnm.w);
		indextemp[fvtnm] = index;
	}
	else
		index = indextemp[fvtnm];
	indices.push_back(index);
	return index;
}

void OBJLoader::AddFace(std::istringstream &txt, const std::vector<glm::vec4>& vtemp, const std::vector<glm::vec4>& vttemp, const std::vector<glm::vec3>& vntemp, std::map<vector4<GLint>, GLint>& indextemp, const GLint matId)
{
	//std::cout << "add face\n";
	std::vector<GLint> ivtmn;
	txt.seekg(2, std::ios::beg);
	while (!txt.eof() && txt.peek()!=EOF && txt.peek() !='\x0D' )
	{
		vector4<GLint> fvtnm(-1, -1, -1, matId);
		txt >> fvtnm.x;
		--fvtnm.x;
		if (txt.peek() == '/')
		{
			txt.seekg(1, std::ios::cur);
			if (txt.peek() != '/')
			{
				txt >> fvtnm.y;
				--fvtnm.y;
			}
			if (txt.peek() == '/')
			{
				txt.seekg(1, std::ios::cur);
				txt >> fvtnm.z;
				--fvtnm.z;
			}
		}
		txt.seekg(1, std::ios::cur);
		if (ivtmn.size() > 2)
		{
			indices.push_back(ivtmn[0]);
			indices.push_back(ivtmn[ivtmn.size() - 1]);
		}
		ivtmn.push_back(AddVertex(fvtnm, vtemp, vttemp, vntemp, indextemp));
	}
}

bool OBJLoader::LoadFile(const std::string& FileName)
{
	v.clear();
	vt.clear();
	vn.clear();
	vtang.clear();
	materials.clear();
	index_materials.clear();
	texturename.clear();
	objectpath.clear();
	std::string name = FileName;
	auto offset = name.find_last_of('\\');
	if (offset != std::string::npos)
		objectpath = name.substr(0, offset + 1);
	else
	{
		offset = name.find_last_of('/');
		if (offset != std::string::npos)
			objectpath = name.substr(0, offset + 1);
	}

	std::ifstream file;
	file.open(FileName.c_str());
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		int length = file.tellg();
		file.seekg(0, std::ios::beg);
		int res = length / 10;
		std::vector<glm::vec4> vtemp, vttemp;
		std::vector<glm::vec3> vntemp;
		vtemp.reserve(res);
		vntemp.reserve(res);
		vttemp.reserve(res);
		std::map<vector4<GLint>, GLint> indextemp;
		indices.reserve(3 * res);
		int matId = 0;
		std::string line;
		std::string str;
		while (getline(file, line))
		{
			str.clear();
			std::istringstream txt(line);
			txt >> str;
			if (str == "v")
			{
				glm::vec4 temp(0.0f, 0.0f, 0.0f, 1.0f);
				txt >> temp.x >> temp.y >> temp.z >> temp.w;
				vtemp.push_back(temp);
			}
			else if (str == "vt")
			{
				glm::vec4 temp(0.0f, 0.0f, 0.0f, 1.0f);
				txt >> temp.x >> temp.y >> temp.z >> temp.w;
				vttemp.push_back(temp);
			}
			else if (str == "vn")
			{
				glm::vec3 temp(0.0f, 0.0f, 0.0f);
				txt >> temp.x >> temp.y >> temp.z;
				vntemp.push_back(temp);
			}
			else if (str == "f")
				AddFace(txt, vtemp, vttemp, vntemp, indextemp, matId);
			else if (str == "mtllib")
			{
				while (!txt.eof())
				{
					txt >> str;
					str = objectpath + str;
					MatLoader::LoadFile(str.c_str());
				}
			}
			else if (str == "usemtl")
			{
				matId = 0;
				txt >> str;
				for (unsigned int i = 0; i < materials.size(); ++i)
				{
					if (materials[i].name == str)
					{
						matId = i;
						break;
					}
				}
			}
			else if (str == "#")
				continue;
		}
		if (vntemp.size() == 0)
			CreateNormals();
	}
	else
		return GL_FALSE;
	file.close();
	if (materials.size() == 0)
	{
		Mat mat;
		mat.clear();
		materials.push_back(mat);
	}
	return GL_TRUE;
}

void OBJLoader::CreateNormals()
{
	vn.clear();
	vn.reserve(v.size());
	vn.assign(v.size(), glm::vec3(0.0, 0.0, 0.0));
	const unsigned int ivSize3 = indices.size() / 3;
	for (unsigned int i = 0; i < ivSize3; ++i)
	{
		glm::vec4 v1temp = v[indices[3*i + 1]] - v[indices[3*i]];
		glm::vec4 v2temp = v[indices[3*i + 2]] - v[indices[3*i+1]];
		glm::vec3 v1(v1temp.x, v1temp.y, v1temp.z);
		glm::vec3 v2(v2temp.x, v2temp.y, v2temp.z);
		glm::vec3 norm = glm::normalize(glm::cross(v1, v2));
		vn[indices[3*i + 2]] += norm;
		vn[indices[3*i + 1]] += norm;
		vn[indices[3*i]] += norm;
	}
	for (unsigned int i = 0; i < vn.size(); ++i)
		vn[i] = glm::normalize(vn[i]);
}

void OBJLoader::CreateTangents()
{
	if (!vt.size())
		return;
	const size_t vSize = v.size();
	vtang.clear();
	vtang.reserve(vSize);
	vtang.assign(vSize, glm::vec3(0.0f, 0.0f, 0.0f));
	for (size_t i = 0; i < vSize; i+=3)
	{
		const glm::vec4 v10 = v[indices[i + 1]] - v[indices[i]];
		const glm::vec4 v20 = v[indices[i + 2]] - v[indices[i]];
		const glm::vec4 st10 = vt[indices[i + 1]] - vt[indices[i]];
		const glm::vec4 st20 = vt[indices[i + 2]] - vt[indices[i]];
		
		const float det = st10.x*st20.y - st20.x*st10.y;

		glm::vec3 tangent;
		if (fabs(det) <= 10e-7)
		{
			tangent.x = 1.0f;
			tangent.y = 0.0f;
			tangent.z = 0.0f;
		}
		else
		{
			tangent = (st20.y*glm::vec3(v10.x, v10.y, v10.z) - st10.y*glm::vec3(v20.x, v20.y, v20.z)) / det;
			glm::normalize(tangent);
		}
		vtang[indices[i]] += tangent;
		vtang[indices[i + 1]] += tangent;
		vtang[indices[i + 2]] += tangent;
	}
	for (size_t i = 0; i < vSize; ++i)
	{
		const float NdotT = glm::dot(vn[indices[i]], vtang[indices[i]]);
		vtang[indices[i]] -= NdotT*vn[indices[i]];
		glm::normalize(vtang[indices[i]]);
	}
}