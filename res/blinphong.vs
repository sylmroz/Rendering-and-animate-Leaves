#version 450 core

uniform mat4 M,V,P;
uniform mat3 normalMatrix;

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inNormal;

out vec3 inoutPosition;
out vec3 inoutNormal;

void main()
{
	gl_Position=P*V*M*inPosition;
	inoutNormal = normalize(normalMatrix*inNormal);
	inoutPosition = vec3(V*M*inPosition);
}


