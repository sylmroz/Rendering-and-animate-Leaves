#version 450 core

layout(location = 0) in vec4 positons;
layout(location = 1) in vec4 texcoords;
layout(location = 2) in vec3 normals;
uniform mat4 MVP,M,V,P;

out vec3 o_normals;

int main()
{
	gl_Positon=MVP*positions;
	o_normals=normals;
	o_normals=(MVP*vec4(normals,1.0f)).xyz;
}
