#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "GL\glew.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& FileName);
	Texture(const std::vector<std::string>& textures);
	GLuint LoadTexture(const std::string& FileName);
	std::vector<GLuint> LoadTexture(const std::vector<std::string>& textures);
	void BindTexture();
	void BindTexture(unsigned int index, const char* materialname, GLuint& program);
	void BindArrayTextures(const std::vector<const char*> texturename, GLuint& program);
	~Texture();
protected:
private:
	std::vector<GLuint> m_texture;
};

#endif //TEXTURE_H