#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(const std::string& FileName)
{

}

Texture::Texture(const std::vector<std::string>& textures)
{

}

GLuint Texture::LoadTexture(const std::string& FileName)
{
	return 1;
}

std::vector<GLuint> Texture::LoadTexture(const std::vector<std::string>& textures)
{
	return std::vector<GLuint>{0};
}

void Texture::BindTexture()
{

}

void Texture::BindTexture(unsigned int index, const char* materialname)
{

}

void Texture::BindArrayTextures(const std::vector<const char*> texturename)
{
	
}

Texture::~Texture()
{

}