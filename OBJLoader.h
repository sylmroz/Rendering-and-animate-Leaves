#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "mat.h"
#include <sstream>

template<typename T>
struct vector4
{
	T x, y, z, w;
	vector4(T X, T Y, T Z, T W) :x(X), y(Y), z(Z), w(W){};
	bool operator<(const vector4 a) const { return memcmp((void*)this, (void*)&a, sizeof(vector4))>0; };
};


class OBJLoader:public MatLoader
{
public:
	friend class Mesh;
	OBJLoader();
	OBJLoader(const std::string& FileName);
	bool LoadFile(const std::string& FileName);
	std::vector<glm::vec4> GetVertex(){ return v; }
	std::vector<glm::vec4> GetVertexTexture(){ return vt; }
	std::vector<glm::vec3> GetVertexNOrmals(){ return vn; }
	std::vector<GLint> GetIndices(){ return indices; }
	std::vector<glm::vec3> GetVertexTangents(){ return vtang; }
	void CreateTangents();

	~OBJLoader() = default;
	
protected:
	void AddFace(std::istringstream& os, const std::vector<glm::vec4>& vtemp, const std::vector<glm::vec4>& vttemp, const std::vector<glm::vec3>& vntemp, std::map<vector4<GLint>,GLint>& indextemp,const GLint matId);
	GLint AddVertex(const vector4<GLint> fvtnm, const std::vector<glm::vec4>& vtemp, const std::vector<glm::vec4>& vttemp, const std::vector<glm::vec3>& vntemp, std::map<vector4<GLint>, GLint>& indextemp);
	void CreateNormals();
	std::vector<glm::vec4> v;
	std::vector<glm::vec4> vt;
	std::vector<glm::vec3> vn;
	std::vector<glm::vec3> vtang;
	std::vector<GLint> indices;
	std::vector<GLint> index_materials;
	std::string objectpath;
private:
};

#endif //OBJLOADER_H