#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include "glm\glm.hpp"
#include "GL\glew.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& FileName);
	~Texture();
	GLuint LoadTexture(const std::string& FileName);
protected:
private:
	
};

#endif //TEXTURE_H