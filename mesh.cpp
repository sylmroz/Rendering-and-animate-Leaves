#include "mesh.h"

void Initialize(GLuint& ar, GLuint& vertexBufer)
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	glGenVertexArrays(1, &ar);
	glBindVertexArray(ar);
	glGenBuffers(1, &vertexBufer);
	glBindBuffer(GL_VERTEX_ARRAY, vertexBufer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//glBindVertexArray(0);
}

void Draw(GLuint& ar, GLuint& vertexBufer)
{
	//glBindVertexArray(array);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, vertexBufer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	//glBindVertexArray(0);
}

void Delete(GLuint& array)
{
	glDeleteVertexArrays(1, &array);
}
template <typename T> void Mesh::CreateBuffer(int number,int num_variables,const std::vector<T>& vertex)
{
	if (number>=0 && number < NUMBER_BUFFERS)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbos[number]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex[0])*vertex.size(), &vertex[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(number);
		glVertexAttribPointer(number, num_variables, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);

	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<GLuint>& indicies)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indicies.size(), &indicies[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec3>(1, 3, normals);
	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec2>(1, 2, texcoord);
	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indicies)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec3>(1, 3, normals);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indicies.size(), &indicies[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec2>(1, 2, texcoord);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indicies.size(), &indicies[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec3>(1, 3, normals);
	CreateBuffer<glm::vec2>(2, 2, texcoord);
	glBindVertexArray(0);
}
void Mesh::CreateArrayObiect(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	CreateBuffer<glm::vec3>(0, 3, position);
	CreateBuffer<glm::vec3>(1, 3, normals);
	CreateBuffer<glm::vec2>(2, 2, texcoord);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indicies.size(), &indicies[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<glm::vec3>& position)
{
	vertex_size = position.size();
	CreateArrayObiect(position);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<GLuint>& indicies)
{
	vertex_size = position.size();
	m_counter = indicies.size();
	CreateArrayObiect(position,indicies);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals)
{
	vertex_size = position.size();
	CreateArrayObiect(position, normals);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indicies)
{
	vertex_size = position.size();
	m_counter = indicies.size();
	CreateArrayObiect(position, normals,indicies);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord)
{
	vertex_size = position.size();
	CreateArrayObiect(position, texcoord);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies)
{
	vertex_size = position.size();
	m_counter = indicies.size();
	CreateArrayObiect(position, texcoord, indicies);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord)
{
	vertex_size = position.size();
	CreateArrayObiect(position, normals, texcoord);
}
Mesh::Mesh(const std::vector<glm::vec3>& position, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texcoord, const std::vector<GLuint>& indicies)
{
	vertex_size = position.size();
	m_counter = indicies.size();
	CreateArrayObiect(position, normals, texcoord, indicies);
}

Mesh::Mesh(const std::string& FileName)
{
	obj.LoadFile(FileName);
	m_counter = obj.indices.size();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(4, vbos);
	if (obj.v.size())
		CreateBuffer<glm::vec4>(0, 4, obj.v);
	if (obj.vn.size())
		CreateBuffer<glm::vec3>(1, 3, obj.vn);
	if (obj.vt.size())
		CreateBuffer<glm::vec4>(2, 4, obj.vt);
	if (obj.indices.size())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*obj.indices.size(), &obj.indices[0], GL_STATIC_DRAW);
	}
	glBindVertexArray(0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
}

void Mesh::DrawObject()
{
	Draw(GL_TRIANGLES);
}
void Mesh::DrawLine(float size)
{
	glLineWidth(size);
	Draw(GL_LINES);
}
void Mesh::DrawPoints(float size)
{
	glPointSize(size);
	Draw(GL_POINTS);
}

void Mesh::DrawLineStrip(float size)
{
	glLineWidth(size);
	Draw(GL_LINE_STRIP);
}

void Mesh::Draw(GLenum en)
{
	if (m_counter > 0)
	{
		glBindVertexArray(vao);
		glDrawElements(en, m_counter, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(vao);
		glDrawArrays(en, 0, vertex_size);
		glBindVertexArray(0);
	}
}