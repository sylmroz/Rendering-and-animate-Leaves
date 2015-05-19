#include "shader.h"
#include <iostream>
#include <fstream>

std::string shader::GetShaderSource(const char* FileName)
{
	std::fstream file;
	file.open(FileName,std::ios::in);
	std::string output;
	if (file.is_open())
	{
		std::string line;
		while (!file.eof())
		{
			line.clear();
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Problem with file " << FileName << std::endl;
	}
	return output;
}

GLuint shader::LoadShader(const GLenum type, const char** src)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, src, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status !=GL_TRUE)
	{
		std::cout << "shader not compiled\n";
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* info = new char[length + 1];
		glGetShaderInfoLog(shader, length, nullptr, info);
		std::cout << info << std::endl;
		delete[] info;
	}
	return shader;
}

GLuint shader::LoadShader(const GLenum type, const char* FileName)
{
	std::string temp = shader::GetShaderSource(FileName);
	const char* src = temp.c_str();
	return LoadShader(type, &src);
}

GLuint shader::LoadVertexShader(const char* FileName)
{
	return shader::LoadShader(GL_VERTEX_SHADER, FileName);
}
GLuint shader::LoadVertexShader(const char** src)
{
	return shader::LoadShader(GL_VERTEX_SHADER, src);
}
GLuint shader::LoadFragmentShader(const char* FileName)
{
	return shader::LoadShader(GL_FRAGMENT_SHADER, FileName);
}
GLuint shader::LoadFragmentShader(const char** src)
{
	return shader::LoadShader(GL_FRAGMENT_SHADER, src);
}
GLuint shader::LoadTessControlShader(const char* FileName)
{
	return shader::LoadShader(GL_TESS_CONTROL_SHADER, FileName);
}
GLuint shader::LoadTessControlShader(const char** src)
{
	return shader::LoadShader(GL_TESS_CONTROL_SHADER, src);
}
GLuint shader::LoadTessEvaulationShader(const char* FileName)
{
	return shader::LoadShader(GL_TESS_EVALUATION_SHADER, FileName);
}
GLuint shader::LoadTessEvaulationShader(const char** src)
{
	return shader::LoadShader(GL_TESS_EVALUATION_SHADER, src);
}
GLuint shader::LoadGeometryShader(const char* FileName)
{
	return shader::LoadShader(GL_GEOMETRY_SHADER, FileName);
}
GLuint shader::LoadGeometryShader(const char** src)
{
	return shader::LoadShader(GL_GEOMETRY_SHADER, src);
}

void shader::AttachShader(GLuint& program, const GLuint& shader)
{
	if (!glIsProgram(program))
		program = glCreateProgram();
	glAttachShader(program,shader);
}

void shader::AttachVertexShader(GLuint& program, const char* name)
{
	GLuint shader = shader::LoadVertexShader(name);
	shader::AttachShader(program, shader);
}
void shader::AttachVertexShader(GLuint& program, const char** src)
{
	GLuint shader = shader::LoadVertexShader(src);
	shader::AttachShader(program, shader);
}
void shader::AttachFragmentShader(GLuint &program, const char *name)
{
	GLuint shader = shader::LoadFragmentShader(name);
	shader::AttachShader(program, shader);
}
void shader::AttachFragmentShader(GLuint &program, const char **src)
{
	GLuint shader = shader::LoadFragmentShader(src);
	shader::AttachShader(program, shader);
}
void shader::AttachGeometryShader(GLuint &program, const char *name)
{
	GLuint shader = shader::LoadGeometryShader(name);
	shader::AttachShader(program, shader);
}
void shader::AttachGeometryShader(GLuint &program, const char **src)
{
	GLuint shader = shader::LoadGeometryShader(src);
	shader::AttachShader(program, shader);
}
void shader::AttachTessControlShader(GLuint &program, const char *name)
{
	GLuint shader = shader::LoadTessControlShader(name);
	shader::AttachShader(program, shader);
}
void shader::AttachTessControlShader(GLuint &program, const char **src)
{
	GLuint shader = shader::LoadTessControlShader(src);
	shader::AttachShader(program, shader);
}
void shader::AttachTessEvaluationShader(GLuint &program, const char *name)
{
	GLuint shader = shader::LoadTessEvaulationShader(name);
	shader::AttachShader(program, shader);
}
void shader::AttachTessEvaluationShader(GLuint &program, const char **src)
{
	GLuint shader = shader::LoadTessEvaulationShader(src);
	shader::AttachShader(program, shader);
}
void shader::LinkProgram(GLuint& program)
{
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Bad consolodation \n";
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* info = new char[length + 1];
		glGetProgramInfoLog(program, length, nullptr, info);
		std::cout << info << std::endl;
		delete[] info;
	}
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Bad validation \n";
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* info = new char[length + 1];
		glGetProgramInfoLog(program, length, nullptr, info);
		std::cout << info << std::endl;
		delete[] info;
	}
}

void shader::DeleteShader(GLuint& program)
{
	glDeleteProgram(program);
}