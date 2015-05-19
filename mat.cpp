#include "mat.h"
#include <fstream>
#include <sstream>
#include <algorithm>

int MatLoader::TextureLayer(const std::string& name)
{
	auto it = std::find(texturename.begin(), texturename.end(), name);
	if (it == texturename.end())
		return -1;
	else
		return static_cast<int>(it - texturename.begin());
}

void Mat::clear()
{
	kd = ka = ks = glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f );
	d = 0.0f;
	name.clear();
	map_Ka.clear();
	map_Kd.clear();
	map_Ns.clear();
	map_d.clear();
	map_bump.clear();
	map_displ.clear();
	Ns = 0.0f;
}

MatLoader::MatLoader(){}
MatLoader::MatLoader(const std::string& FileName)
{
	if (!LoadFile(FileName))
		std::cout << "File " << FileName << " doesn't exist\n";
	//for (const auto& x : materials)
		//std::cout << x << std::endl;
}

bool MatLoader::LoadFile(const std::string& FileName)
{
	std::fstream file;
	std::string line;
	file.open(FileName.c_str());
	if (file.is_open())
	{
		CreatePath(FileName);
		Mat mat;
		while (std::getline(file, line))
		{
			std::istringstream is(line);
			std::string text;
			is >> text;
			if (text == "newmtl")
			{
				if (mat.name.length() > 0)
					materials.push_back(mat);
				mat.clear();
				is >> mat.name;
			}
			else if (text == "Ka")
				is >> mat.ka.r >> mat.ka.g >> mat.ka.b;
			else if (text == "Kd")
				is >> mat.kd.r >> mat.kd.g >> mat.kd.b;
			else if (text == "Ks")
				is >> mat.ks.r >> mat.ks.g >> mat.ks.b;
			else if (text == "d")
			{
				is >> mat.d;
				mat.ks.a = mat.d;
				mat.kd.a = mat.d;
				mat.ka.a = mat.d;
			}
			else if (text == "Ns")
			{
				is >> mat.Ns;
				mat.Ns /= 1000.0f;
				mat.Ns *= 128.0f;
			}
			else if (text == "Tr")
			{
				float tr;
				is >> tr;
				mat.ka.a = 1.0f - tr;
				mat.ks.a = 1.0f - tr;
				mat.kd.a = 1.0f - tr;
			}
			else if (text == "map_Ka")
			{
				is >> mat.map_Ka;
				if (TextureLayer(mat.map_Ka) < 0)
					texturename.push_back(path + mat.map_Ka);
			}
			else if (text == "map_Kd")
			{
				is >> mat.map_Kd;
				if (TextureLayer(mat.map_Kd) < 0)
					texturename.push_back(path + mat.map_Kd);
			}
			else if (text == "map_Ns")
			{
				is >> mat.map_Ns;
				if (TextureLayer(mat.map_Ns) < 0)
					texturename.push_back(path + mat.map_Ns);
			}
			else if (text == "map_bump")
			{
				is >> mat.map_bump;
				if (TextureLayer(mat.map_bump) < 0)
					texturename.push_back(path + mat.map_bump);
			}
		}
		materials.push_back(mat);
		return true;
	}
	return false;
}

void MatLoader::CreatePath(std::string name)
{
	
	for (; name[name.length() - 1] != '/' && name[name.length() - 1] != '\\' && name.size() != 0; name.pop_back());
	path = name;
}

MatLoader::~MatLoader(){}