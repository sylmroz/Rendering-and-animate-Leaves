#version 450 core

struct MaterialParametrs
{
	vec4 emmision; //Me
	vec4 ambient; //Ma
	vec4 diffuse; //Md
	vec4 specular; //Ms
	float shinnes; //Sh
};
vec4 CookTorranceLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float m,float F0);

vec4 BlinPhongLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float shinnes);

vec4 CookTorranceGaussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float m,float F0,float c);

vec4 OrenNayarLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,float sigma);

vec4 StraussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,const vec4 specular,float s,float m,float t);

vec4 WardIzotropicLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const vec4 emmision,const float sigma);


vec4 WardAnizotropicSpotLight(const int number, const vec3 position, const vec3 tangent, const vec3 bitangent, const vec3 normal, const vec4 diffuse, const vec4 specular, const vec4 ambient,const vec4 emmision, const float sigmax, const float sigmay);

in vec3 inoutPosition;
in vec3 inoutNormal;

out vec4 outColor;

void main()
{
	vec3 normal=normalize(inoutNormal);
	MaterialParametrs mat=MaterialParametrs
			(
				vec4( 0.0, 0.0, 0.0, 1.0 ),
                vec4( 0.0, 0.0, 0.0,  1.000000 ),
                vec4( 0.5, 0.5, 0.0, 1.000000 ),
                vec4( 0.60, 0.60, 0.50, 1.000000 ),
                32.0
			);
	vec3 tangent = vec3(1.0,0.0,0.0);
	float NdotT = dot(normal,tangent);
	tangent -= NdotT*normal;
	tangent = normalize(tangent);
	vec3 bitangent = cross(tangent,normal);
	/*if(gl_FrontFacing==true)
		outColor = StraussLight(0,inoutPosition,normal,mat.diffuse,mat.ambient,mat.emmision,mat.specular,1.0-mat.shinnes/128.0,mat.shinnes/128.0,0.1);
	else
		outColor = StraussLight(0,inoutPosition,-normal,mat.diffuse,mat.ambient,mat.emmision,mat.specular,1.0-mat.shinnes/128.0f,mat.shinnes/128.0f,0.0);*/
	/*if(gl_FrontFacing==true)
		outColor = WardIzotropicLight(0,inoutPosition,normal,mat.diffuse,mat.specular,mat.ambient,mat.emmision,mat.shinnes/128.0);
	else
		outColor = WardIzotropicLight(0,inoutPosition,-normal,mat.diffuse,mat.specular,mat.ambient,mat.emmision,mat.shinnes/128.0f);*/
	/*if(gl_FrontFacing==true)
		outColor = WardAnizotropicSpotLight(0,inoutPosition,tangent,bitangent,normal,mat.diffuse,mat.specular,mat.ambient,mat.emmision,0.25+mat.shinnes/128.0,0.05+mat.shinnes/128.0);
	else
		outColor = WardAnizotropicSpotLight(0,inoutPosition,tangent,bitangent,-normal,mat.diffuse,mat.specular,mat.ambient,mat.emmision,0.25+mat.shinnes/128.0,0.05+mat.shinnes/128.0);*/


	if(gl_FrontFacing==true)
		outColor = CookTorranceLight(0,inoutPosition,normal,mat.diffuse,mat.ambient,mat.specular,mat.emmision,0.25,1.0);
	else
		outColor = CookTorranceLight(0,inoutPosition,-normal,mat.diffuse,mat.ambient,mat.specular,mat.emmision,0.25,1.0);
}

















