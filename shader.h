#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "GL\glew.h"

namespace shader
{
	std::string GetShaderSource(const char* FileName);
	GLuint LoadShader(const GLenum type, const char* FileName);
	GLuint LoadShader(const GLenum type, const char** src);
	GLuint LoadVertexShader(const char* FileName);
	GLuint LoadVertexShader(const char** src);
	GLuint LoadFragmentShader(const char* FileName);
	GLuint LoadFragmentShader(const char** src);
	GLuint LoadTessControlShader(const char* FileName);
	GLuint LoadTessControlShader(const char** src);
	GLuint LoadTessEvaulationShader(const char* FileName);
	GLuint LoadTessEvaulationShader(const char** src);
	GLuint LoadGeometryShader(const char* FileName);
	GLuint LoadGeometryShader(const char** src);
	void AttachShader(GLuint& program,const GLuint& shader);
	void AttachVertexShader(GLuint& program, const char* name);
	void AttachVertexShader(GLuint &program, const char **src);
	void AttachFragmentShader(GLuint &program, const char *name);
	void AttachFragmentShader(GLuint &program, const char **src);
	void AttachGeometryShader(GLuint &program, const char *name);
	void AttachGeometryShader(GLuint &program, const char **src);
	void AttachTessControlShader(GLuint &program, const char *name);
	void AttachTessControlShader(GLuint &program, const char **src);
	void AttachTessEvaluationShader(GLuint &program, const char *name);
	void AttachTessEvaluationShader(GLuint &program, const char **src);
	void LinkProgram(GLuint& program);
	void DeleteShader(GLuint& pogram);
}

#endif //SHADER_H