#version 450 core

struct MaterialParametrs
{
	vec4 emmision; //Me
	vec4 ambient; //Ma
	vec4 diffuse; //Md
	vec4 specular; //Ms
	float shinnes; //Sh
};

vec4 BlinPhongLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float shinnes);

vec4 CookTorranceGaussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float m,float F0,float c);

vec4 OrenNayarLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,float sigma);

vec4 StraussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,const vec4 specular,float s,float m,float t);

in vec3 inoutPosition;
in vec3 inoutNormal;

out vec4 outColor;

void main()
{
	vec3 normal=normalize(inoutNormal);
	MaterialParametrs mat=MaterialParametrs
			(
				vec4( 0.0, 0.0, 0.0, 1.0 ),
                vec4( 0.174500, 0.011750, 0.011750, 0.550000 ),
                vec4( 0.614240, 0.041360, 0.041360, 0.550000 ),
                vec4( 0.727811, 0.626959, 0.626959, 0.550000 ),
                76.8
			);
	if(gl_FrontFacing==true)
		outColor = StraussLight(0,inoutPosition,normal,mat.diffuse,mat.ambient,mat.emmision,mat.specular,1.0-mat.shinnes/128.0,mat.shinnes/128.0,0.1);
	else
		outColor = StraussLight(0,inoutPosition,-normal,mat.diffuse,mat.ambient,mat.emmision,mat.specular,1.0-mat.shinnes/128.0f,mat.shinnes/128.0f,0.0);
}
