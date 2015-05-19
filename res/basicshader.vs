#version 450

layout(location = 0) in vec3 position;
uniform mat4 MVP;
uniform vec4 clipPlane[1];
out float gl_ClipDistance[1];
void main()
{
	gl_Position = MVP*vec4(position,1.0);
	gl_ClipDistance[0] = dot( clipPlane[0], gl_Position );
}