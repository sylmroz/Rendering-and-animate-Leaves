#include "texture.h"
#include "stb_image.h"

Texture::Texture()
{

}

Texture::Texture(const std::string& FileName)
{
	m_texture.push_back(LoadTexture(FileName));
}

Texture::Texture(const std::vector<std::string>& textures)
{
	m_texture = LoadTexture(textures);
}

GLuint Texture::LoadTexture(const std::string& FileName)
{
	GLuint tex;
	int width, height, numComponents;
	unsigned char* data = stbi_load(FileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);
	if (data == nullptr)
		std::cerr << "unable load texture " << FileName << "\n";
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return tex;
}

std::vector<GLuint> Texture::LoadTexture(const std::vector<std::string>& textures)
{
	std::vector<GLuint> texture;
	int size = textures.size();
	GLuint* tex = new GLuint[size];
	glGenTextures(size, tex);
	for (unsigned int i = 0; i < size; ++i)
	{
		int width, height, numComponents;
		unsigned char* data = stbi_load(textures[i].c_str(), &width, &height, &numComponents, STBI_rgb_alpha);
		if (data == nullptr)
			std::cerr << "unable load texture " << textures[i] << "\n";
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	for (int i = 0; i < size; ++i)
		texture.push_back(tex[i]);
	delete tex;
	return texture;
}

void Texture::BindTexture()
{
	if (m_texture.size())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	}
}

void Texture::BindTexture(unsigned int index, const char* materialname,GLuint& program)
{
	if (m_texture.size() >= index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_texture[index]);
		glUniform1i(glGetUniformLocation(program, materialname), index);
	}
}

void Texture::BindArrayTextures(const std::vector<const char*> texturename, GLuint& program)
{
	for (int i = 0; i < texturename.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_texture[i]);
		glUniform1i(glGetUniformLocation(program, texturename[i]), i);
	}
}

Texture::~Texture()
{
	for (int i = 0; i < m_texture.size(); ++i)
		glDeleteTextures(m_texture.size(), m_texture.data());
}