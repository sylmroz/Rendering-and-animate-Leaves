#ifndef MESH_H
#define MESH_H

#include "GL\glew.h"
#include <vector>
#include "glm\glm.hpp"
#include "OBJLoader.h"
class Mesh
{
public:
	Mesh(const std::string& FileName);
	Mesh(const std::vector<glm::vec3>& position);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<GLuint>& indicies);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indicies);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord);
	Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies);
	~Mesh();
	void DrawLine(float size);
	void DrawObject();
	void DrawPoints(float size);
	void DrawLineStrip(float size);
	GLuint GetVAO(){ return vao; }
protected:
private:
	void Draw(GLenum en);
	template <typename T> void CreateBuffer(int number, int num_variables, const std::vector<T>& vertex);
	void CreateArrayObiect(const std::vector<glm::vec3>& position);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<GLuint>& indicies);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indicies);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord);
	void CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies);
	GLuint vao;
	GLint m_counter{ 0 };
	GLint vertex_size;
	enum { NUMBER_BUFFERS = 4 };
	GLuint vbos[NUMBER_BUFFERS];
	OBJLoader obj;
};


void Initialize(GLuint& ar, GLuint& vertexBufer);
void Draw(GLuint& ar, GLuint& vertexBufer);
void Delete(GLuint& ar);


#endif