#version 450 core

const float pi=3.14159265359;

struct LightParametrs
{
	vec4 ambient; //La
	vec4 diffuse; //Ld
	vec4 specular; //Ls
	vec4 position; //Lp
	vec3 SpotDirection; //S
	float SpotCuttof; //Sc
	float SpotExponent; //Se
	float ConstantAttention; //Kc
	float LinearAttention; //Kl
	float QuadratureAttention; //Kq
};

const int MaxLight = 8;

uniform LightParametrs Light[MaxLight] = LightParametrs[MaxLight]
	(
		LightParametrs(
			vec4( 0.0, 0.0, 0.0, 1.0 ),
            vec4( 1.0, 1.0, 1.0, 1.0 ),
            vec4( 1.0, 1.0, 1.0, 1.0 ),
            vec4( 0.0, 0.0, 1.0, 0.0 ),
            vec3( 0.0, 0.0, -1.0 ),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		),
		LightParametrs(
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,0.0,1.0),
			vec4 (0.0,0.0,1.0,1.0),
			vec3 (0.0,0.0,-1.0),
			180.0,
			0.0,
			0.0,
			0.0,
			0.0
		)
	);



struct MaterialParametrs
{
	vec4 emmision; //Me
	vec4 ambient; //Ma
	vec4 diffuse; //Md
	vec4 specular; //Ms
	float shinnes; //Sh
};

struct LightModelParametrs
{
	vec4 ambient;
};

uniform LightModelParametrs LightModel = LightModelParametrs(vec4(0.2,0.2,0.2,1.0));

uniform vec4 EyePosition=vec4(0.0,0.0,0.0,1.0);

uniform vec4 SkyColor = vec4(1.0,1.0,1.0,1.0);

uniform vec4 GroundColor = vec4(0.0,0.0,0.0,1.0);

uniform vec3 HemisphereLightFirection;

vec4 Hemisphere(const vec3 normal)
{
	float a = 0.5 + 0.5*dot(HemisphereLightFirection,normal);
	return mix(GroundColor,SkyColor,a);
}

vec4 GlobalAmbientLight(const vec4 ambient)
{
	return LightModel.ambient*ambient;
}

vec4 LocalAmbientLight(const int number,const vec4 ambient)
{
	return Light[number].ambient*ambient;
}

vec4 LambertianDirectionLight(const int number,const vec3 normal,const vec4 diffuse)
{
	float NdotL=max(dot(normal,Light[number].position.xyz),0.0);
	if(NdotL>0)
		return normalize(NdotL)*Light[number].diffuse*diffuse;
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 LambertianPointLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 ambient)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance=length(LV);
	LV=normalize(LV);
	float NdotL=max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		float att=1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL*Light[number].diffuse*diffuse);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 LambertianSpotLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 ambient)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance=length(LV);
	LV=normalize(LV);
	float NdotL=max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			spot = pow(spot,Light[number].SpotExponent);
			float att=spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL*Light[number].diffuse*diffuse);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}


vec4 LamberianLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 ambient,const vec4 emission )
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient)+LocalAmbientLight(number,ambient)+LambertianDirectionLight(number,normal,diffuse) + emission;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + LambertianPointLight(number,position,normal,diffuse,ambient) + emission;
		else
			return GlobalAmbientLight(ambient) + LambertianSpotLight(number,position,normal,diffuse,ambient) + emission;
	}
}

vec4 PhongDirectionalLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 specular,float shinnes)
{
	vec3 LV=Light[number].position.xyz-position;
	LV=normalize(LV);
	float NdotL=max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 R=-reflect(Light[number].position.xyz,normal);
		float RdotE=max(dot(normalize(LV),R),0.0);
		return  NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(RdotE,shinnes);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 PhongPointLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float shinnes)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 R = -reflect(Light[number].position.xyz,normal);
		float RdotE = max(dot(normalize(LV),R),0.0);
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(RdotE,shinnes));
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 PhongSpotLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float shinnes)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV=normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 R = -reflect(Light[number].position.xyz,normal);
		float RdotE = max(dot(normalize(Light[number].position.xyz-position),R),0.0);
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			spot = pow(spot,Light[number].SpotExponent);
			float att=spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(RdotE,shinnes));
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 PhongLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float shinnes)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + PhongDirectionalLight(number,position,normal,diffuse,specular,shinnes) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + PhongPointLight(number,position,normal,diffuse,ambient,specular,shinnes) + emmision;
		else
			return GlobalAmbientLight(ambient) + PhongSpotLight(number,position,normal,diffuse,ambient,specular,shinnes) + emmision;
	}
}

vec4 BlinPhongDirectionalLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 specular,float shinnes)
{
	vec3 LV = Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 H=normalize(LV+normalize(EyePosition.xyz-position));
		float NdotH=max(dot(normal,H),0.0);
		return NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(NdotH,shinnes);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 BlinPhongPointLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float shinnes)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance=length(LV);
	LV=normalize(LV);
	float NdotL=max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 H=normalize(LV+normalize(EyePosition.xyz-position));
		float NdotH=max(dot(normal,H),0.0);
		float att=1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(NdotH,shinnes));
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 BlinPhongSpotLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float shinnes)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance=length(LV);
	LV=normalize(LV);
	float NdotL=max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 H=normalize(LV+normalize(EyePosition.xyz-position));
		float NdotH=max(dot(normal,H),0.0);
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			spot = pow(spot,Light[number].SpotExponent);
			float att=spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * pow(NdotH,shinnes));
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 BlinPhongLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float shinnes)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + BlinPhongDirectionalLight(number,position,normal,diffuse,specular,shinnes) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + BlinPhongPointLight(number,position,normal,diffuse,ambient,specular,shinnes) + emmision;
		else
			return GlobalAmbientLight(ambient) + BlinPhongSpotLight(number,position,normal,diffuse,ambient,specular,shinnes) + emmision;
	}
}


vec4 CookTorranceDirectionalLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 specular,float m,float F0)
{
	vec3 LV = Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float EdotH = max(dot(Eye,H),0.0);
		float F = F0+(1-pow(1-EdotH,5)*(1-F0));
		float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
		float D = exp((pow(NdotH,2)-1)/(m*m*pow(NdotH,2)))/(pow(NdotH,4)*m*m);
		float k = F*G*D/(pi*NdotL*NdotE);
		return (NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 CookTorrancePointLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float m,float F0)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float EdotH = max(dot(Eye,H),0.0);
		float F = F0+(1-pow(1-EdotH,5)*(1-F0));
		float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
		float D = exp((pow(NdotH,2)-1)/(m*m*pow(NdotH,2)))/(pow(NdotH,4)*m*m);
		float k = F*G*D/(pi*NdotL*NdotE);
		float att=1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}


vec4 CookTorranceSpotLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float m,float F0)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{	
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 H = normalize(LV+Eye);
			float NdotH = max(dot(normal,H),0.0);
			float EdotH = max(dot(Eye,H),0.0);
			float F = F0+(1-pow(1-NdotH,5)*(1-F0));
			float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
			float D = exp((pow(NdotH,2)-1)/(m*m*pow(NdotH,2)))/(pow(NdotH,4)*m*m);
			float k = F*G*D/(pi*NdotL*NdotE);
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}


vec4 CookTorranceLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float m,float F0)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + CookTorranceDirectionalLight(number,position,normal,diffuse,specular,m,F0) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + CookTorrancePointLight(number,position,normal,diffuse,ambient,specular,m,F0) + emmision;
		else
			return GlobalAmbientLight(ambient) + CookTorranceSpotLight(number,position,normal,diffuse,ambient,specular,m,F0) + emmision;
	}
}


vec4 CookTorranceGaussDirectionalLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 specular,float m,float F0,float c)
{
	vec3 LV = Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float EdotH = max(dot(Eye,H),0.0);
		float F = F0+(1-pow(1-NdotH,5)*(1-F0));
		float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
		float D = c*exp(-acos(NdotH)/(m*m));
		float k = F*G*D/(pi*NdotL*NdotE);		
		return NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k;
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 CookTorranceGaussPointLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float m,float F0,float c)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float EdotH = max(dot(Eye,H),0.0);
		float F = F0+(1-pow(1-NdotH,5)*(1-F0));
		float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
		float D = c*exp(-acos(NdotH)/(m*m));
		float k = F*G*D/(pi*NdotL*NdotE);
		
		float att=1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}


vec4 CookTorranceGaussSpotLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,float m,float F0,float c)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{	
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 H = normalize(LV+Eye);
			float NdotH = max(dot(normal,H),0.0);
			float EdotH = max(dot(Eye,H),0.0);
			float F = F0+(1-pow(1-NdotH,5)*(1-F0));
			float G = min(1,min(2*NdotH*NdotE/EdotH,2*NdotH*NdotL/EdotH));
			float D = c*exp(-acos(NdotH)/(m*m));
			float k = F*G*D/(pi*NdotL*NdotE);
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse + Light[number].specular * specular * k);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}


vec4 CookTorranceGaussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient, const vec4 specular,const vec4 emmision,float m,float F0,float c)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + CookTorranceGaussDirectionalLight(number,position,normal,diffuse,specular,m,F0,c) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + CookTorranceGaussPointLight(number,position,normal,diffuse,ambient,specular,m,F0,c) + emmision;
		else
			return GlobalAmbientLight(ambient) + CookTorranceGaussSpotLight(number,position,normal,diffuse,ambient,specular,m,F0,c) + emmision;
	}
}


vec4 OrenNayarDirectionalLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,float sigma)
{
	vec3 LV = Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = dot(normal,Eye);
	if(NdotL>0)
	{
		float sig2 = sigma*sigma;
		float A = 1-(0.5*sig2)/(sig2 + 0.33);
		float B = (0.45*sig2)/(sig2 + 0.09);
		float C1 = sin(max(acos(NdotE),acos(NdotL)));
		float C2 = tan(min(acos(NdotE),acos(NdotL)));
		return NdotL * Light[number].diffuse * diffuse* C1 * C2 *(A + B*(max(0.0,dot(Eye-normal*NdotE,LV-normal*NdotL))))/pi;
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 OrenNayarPointLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,float sigma)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = dot(normal,Eye);
	if(NdotL>0)
	{
		float sig2 = sigma*sigma;
		float A = 1-(0.5*sig2)/(sig2 + 0.33);
		float B = (0.45*sig2)/(sig2 + 0.09);
		float C1 = sin(max(acos(NdotE),acos(NdotL)));
		float C2 = tan(min(acos(NdotE),acos(NdotL)));
		float att=1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + NdotL * Light[number].diffuse * diffuse* C1 * C2 *(A + B*(max(0.0,dot(Eye-normal*NdotE,LV-normal*NdotL))))/pi);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 OrenNayarSpotLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,float sigma)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{	
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 H = normalize(LV+Eye);
			float NdotH = max(dot(normal,H),0.0);
			float EdotH = max(dot(Eye,H),0.0);
			float A = 1-(0.5*sigma*sigma)/(sigma*sigma + 0.33);
			float B = (0.45*sigma*sigma)/(sigma*sigma + 0.09);
			float C1 = sin(max(acos(NdotE),acos(NdotL)));
			float C2 = tan(max(acos(NdotE),acos(NdotL)));
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + NdotL*Light[number].diffuse*diffuse * C1 * C2 * (A + B*(max(0.0,dot(Eye-normal*NdotE,Light[number].position.xyz-normal*NdotL))))/pi);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 OrenNayarLighting(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,float sigma)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + OrenNayarDirectionalLighting(number,position,normal,diffuse,sigma) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + OrenNayarPointLighting(number,position,normal,diffuse,ambient,sigma) + emmision;
		else
			return GlobalAmbientLight(ambient) + OrenNayarSpotLighting(number,position,normal,diffuse,ambient,sigma) + emmision;
	}
}

float Fersnel(const float x)
{
	return ((1/((x-1.12)*(x-1.12)))-0.797193878)/68.64725056;
}

float Geomoetric(const float x)
{
	return (10000.0-(1/((x-1.01)*(x-1.01))))/9999.0197;
}

vec4 StraussDirectionalLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 specular,float s,float m,float t)
{
	vec3 LV = Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		const float pi2 = 1.5707963267948966192313216916398;
		float sm = s*s*s;
		float r = 1.0-t-(1-sm)*(1-t);
		//float FersnelNdotL = Fersnel(NdotL/(pi/2));
		float Ref=min(1.0,r+Fersnel(NdotL/pi2)*Geomoetric(NdotL/pi2)*Geomoetric(NdotE/pi2)*(r+0.1));
		vec3 R=-reflect(Light[number].position.xyz,normal);
		float RdotE=max(dot(R,Eye),0.0);
		vec3 Cs = vec3(1.0,1.0,1.0)+m*(1-Fersnel(NdotL/(pi/2)))*(Light[number].specular.rgb*specular.rgb-vec3(1.0,1.0,1.0));
		vec3 D = NdotL*(1-m*s)*(1-sm)*(1-t)*Light[number].diffuse.rgb*diffuse.rgb;
		vec3 S = max( vec3( 0.0 ), Cs * Ref * pow( dot( R, Eye ), 3.0 / (1.0 - s) ) );
		vec4 I = vec4(D + S,1.0);
		return I;
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 StraussPointLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,vec4 ambient,const vec4 specular,float s,float m,float t)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		const float pi2 = 1.5707963267948966192313216916398;
		float sm = s*s*s;
		float r = 1.0-t-(1-sm)*(1-t);
		//float FersnelNdotL = Fersnel(NdotL/(pi/2));
		float Ref=min(1.0,r+Fersnel(NdotL/pi2)*Geomoetric(NdotL/pi2)*Geomoetric(NdotE/pi2)*(r+0.1));
		vec3 R=-reflect(Light[number].position.xyz,normal);
		float RdotE=max(dot(R,Eye),0.0);
		vec3 Cs = vec3(1.0,1.0,1.0)+m*(1-Fersnel(NdotL/(pi/2)))*(Light[number].specular.rgb*specular.rgb-vec3(1.0,1.0,1.0));
		vec3 D = NdotL*(1-m*s)*(1-sm)*(1-t)*Light[number].diffuse.rgb*diffuse.rgb;
		vec3 S = max( vec3( 0.0 ), Cs * Ref * pow( dot( R, Eye ), 3.0 / (1.0 - s) ) );
		vec4 I = vec4(D + S,1.0);
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient) + I);
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);	
}


vec4 StraussSpotLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,vec4 ambient,const vec4 specular,float s,float m,float t)
{
	vec3 LV=Light[number].position.xyz-position;

	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	vec3 Eye = normalize(EyePosition.xyz-position);
	float NdotE = max(dot(normal,Eye),0.0);
	if(NdotL>0 && NdotE>0)
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			const float pi2 = 1.5707963267948966192313216916398;
			float sm = s*s*s;
			float r = 1.0-t-(1-sm)*(1-t);
			//float FersnelNdotL = Fersnel(NdotL/(pi/2));
			float Ref=min(1.0,r+Fersnel(NdotL/pi2)*Geomoetric(NdotL/pi2)*Geomoetric(NdotE/pi2)*(r+0.1));
			vec3 R=-reflect(Light[number].position.xyz,normal);
			float RdotE=max(dot(R,Eye),0.0);
			vec3 Cs=vec3(1.0,1.0,1.0)+m*(1-Fersnel(NdotL/(pi/2)))*(Light[number].specular.rgb*specular.rgb-vec3(1.0,1.0,1.0));
			vec3 D = NdotL*(1-m*s)*(1-sm)*(1-t)*Light[number].diffuse.rgb*diffuse.rgb;
			vec3 S = max( vec3( 0.0 ), Cs * Ref * pow( dot( R, Eye ), 3.0 / (1.0 - s) ) );
			vec4 I = vec4(D + S,1.0);
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient) + I);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);	
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);	
}

vec4 StraussLight(const int number,const vec3 position, const vec3 normal,const vec4 diffuse,const vec4 ambient,vec4 emmision,const vec4 specular,float s,float m,float t)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + StraussDirectionalLight(number,position,normal,diffuse,specular,s,m,t) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + StraussPointLight(number,position,normal,diffuse,ambient,specular,s,m,t) + emmision;
		else
			return GlobalAmbientLight(ambient) + StraussSpotLight(number,position,normal,diffuse,ambient,specular,s,m,t) + emmision;
	}
}


vec4 WardDirectionalIzotropicLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 specular,const float sigma)
{
	vec3 LV=Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float sig=sigma*sigma;
		float Is=(exp((-2*pow(tan(acos(NdotH)),2.0))/(sig)))/(4.0*pi*sig*sqrt(NdotE*NdotL));
		return NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is;
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardPointIzotropicLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const float sigma)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float sig=sigma*sigma;
		float Is=(exp((-2*pow(tan(acos(NdotH)),2.0))/(sig)))/(4.0*pi*sig*sqrt(NdotE*NdotL));
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient)*ambient + NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is);
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardSpotIzotropicLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const float sigma)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 Eye = normalize(EyePosition.xyz-position);
			vec3 H = normalize(Light[number].position.xyz+Eye);
			float NdotH = max(dot(normal,H),0.0);
			float NdotE = max(dot(normal,Eye),0.0);
			float sig=sigma*sigma;
			float Is=(exp((-2*pow(tan(acos(NdotH)),2.0))/(sig)))/(4.0*pi*sig*sqrt(NdotE*NdotL));
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient)*ambient + NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else 
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardIzotropicLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const vec4 emmision,const float sigma)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + WardDirectionalIzotropicLight(number,position,normal,diffuse,specular,sigma) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + WardPointIzotropicLight(number,position,normal,diffuse,specular,ambient,sigma) + emmision;
		else
			return GlobalAmbientLight(ambient) + WardSpotIzotropicLight(number,position,normal,diffuse,specular,ambient,sigma) + emmision;
	}
}

vec4 WardAnizotropicDirectionalLight(const int number,const vec3 position,const vec3 tangent,const vec3 bitangent,const vec3 normal,const vec4 diffuse,const vec4 specular,const float sigmax,const float sigmay)
{
	vec3 LV=Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	const vec3 Eye = normalize(EyePosition.xyz-position);
	const float NdotE = dot(normal,Eye);
	if(NdotL>0.0 && NdotE != 0.0 )
	{
		const vec3 H = normalize(LV+Eye);
		const float HdotT = dot(tangent,H);
		const float HdotB = dot(bitangent,H);
		const float NdotH = dot(normal,H);
		const float A = exp(-2*((HdotT/sigmax)*(HdotT/sigmax)+(HdotB/sigmay)*(HdotB/sigmay))/(1+NdotH));
		const float Is = A/(4*pi*sigmax*sigmay*sqrt(NdotE*NdotL));
		return NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is;  
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardAnizotropicPointLight(const int number,const vec3 position,const vec3 tangent,const vec3 bitangent,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const float sigmax,const float sigmay)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	const vec3 Eye = normalize(EyePosition.xyz-position);
	const float NdotE = dot(normal,Eye);
	if(NdotL>0.0 && NdotE != 0.0 )
	{
		const vec3 H = normalize(LV+Eye);
		const float HdotT = dot(tangent,H);
		const float HdotB = dot(bitangent,H);
		const float NdotH = dot(normal,H);
		const float A = exp(-2*((HdotT/sigmax)*(HdotT/sigmax)+(HdotB/sigmay)*(HdotB/sigmay))/(1+NdotH));
		const float Is = A/(4*pi*sigmax*sigmay*sqrt(NdotE*NdotL));
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att * (LocalAmbientLight(number,ambient)*ambient + NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is);  
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardAnizotropicSpotLight(const int number,const vec3 position,const vec3 tangent,const vec3 bitangent,const vec3 normal,const vec4 diffuse,const vec4 specular,const vec4 ambient,const float sigmax,const float sigmay)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	const vec3 Eye = normalize(EyePosition.xyz-position);
	const float NdotE = dot(normal,Eye);
	if(NdotL>0.0 && NdotE != 0.0 )
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			const vec3 H = normalize(LV+Eye);
			const float HdotT = dot(tangent,H);
			const float HdotB = dot(bitangent,H);
			const float NdotH = dot(normal,H);
			const float A = exp(-2*((HdotT/sigmax)*(HdotT/sigmax)+(HdotB/sigmay)*(HdotB/sigmay))/(1+NdotH));
			const float Is = A/(4*pi*sigmax*sigmax*sqrt(NdotE*NdotL));
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att * (LocalAmbientLight(number,ambient)*ambient + NdotL*Light[number].diffuse*diffuse + Light[number].specular*specular*Is);  
		}
		else
			return vec4(0.0,0.0,0.0,1.0);	
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 WardAnizotropicLight(const int number, const vec3 position, const vec3 tangent, const vec3 bitangent, const vec3 normal, const vec4 diffuse, const vec4 specular, const vec4 ambient,const vec4 emmision, const float sigmax, const float sigmay)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + WardAnizotropicDirectionalLight(number, position, tangent, bitangent, normal, diffuse, specular, sigmax, sigmay) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + WardAnizotropicPointLight(number, position, tangent, bitangent, normal, diffuse, specular, emmision, sigmax, sigmay) + emmision;		
		else
			return GlobalAmbientLight(ambient) + WardAnizotropicSpotLight(number, position, tangent, bitangent, normal, diffuse, specular, emmision, sigmax, sigmay) + emmision; + emmision;
	}
}

vec4 AskikhmininShirleyIzotropidDirectionalLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse, const vec4 specular,const float Rd, const float Rs, const float n)
{
	vec3 LV=Light[number].position.xyz-position;
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float HdotL = dot(H,LV);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float F = Rs + pow(1.0 - HdotL,5.0)*(1.0 - Rs);
		float Is = F*((n+1.0)*pow(NdotH,n))/(8.0*pi*HdotL*max(NdotL,NdotE));
		float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
		return 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is;
	}
	else
		return vec4(0.0,0.0,0.0,1.0);

}

vec4 AskikhmininShirleyIzotropidPointLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse, const vec4 specular,const vec4 ambient,const float Rd, const float Rs, const float n)
{
	vec3 LV = Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float HdotL = dot(H,LV);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float F = Rs + pow(1.0 - HdotL,5.0)*(1.0 - Rs);
		float Is = F*((n+1.0)*pow(NdotH,n))/(8.0*pi*HdotL*max(NdotL,NdotE));
		float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att*(LocalAmbientLight(number,ambient)*ambient + 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 AskikhmininShirleyIzotropidSpotLight(const int number,const vec3 position,const vec3 normal,const vec4 diffuse, const vec4 specular,const vec4 ambient,const float Rd, const float Rs, const float n)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 Eye = normalize(EyePosition.xyz-position);
			vec3 H = normalize(LV+Eye);
			float NdotH = max(dot(normal,H),0.0);
			float NdotE = max(dot(normal,Eye),0.0);
			float F = Rs + pow(1.0 - NdotL,5.0)*(1.0 - Rs);
			float Is = F*((n+1.0)*pow(NdotH,n))/(8.0*pi*NdotL*max(NdotL,NdotE));
			float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
		
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att*(LocalAmbientLight(number,ambient)*ambient + 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 AskikhmininShirleyIzotropidLight(const int number, const vec3 position, const vec3 normal, const vec4 diffuse, const vec4 specular, const vec4 ambient,const vec4 emmision,const float Rd, const float Rs, const float n)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + AskikhmininShirleyIzotropidDirectionalLight(number,position,normal,diffuse, specular, Rd, Rs, n) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + AskikhmininShirleyIzotropidPointLight(number,position,normal,diffuse,specular,ambient,Rd,Rs,n) + emmision;		
		else
			return GlobalAmbientLight(ambient) + AskikhmininShirleyIzotropidSpotLight(number,position,normal,diffuse,specular,ambient,Rd,Rs,n) + emmision; + emmision;
	}
}

vec4 AskikhmininShirleyAnizotropidDirectionalLight(const int number, const vec3 position, const vec3 normal,const vec3 tangent, const vec3 bitangent, const vec4 diffuse, const vec4 specular, const float Rd, const float Rs, const float nx, const float ny)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float HdotL = dot(H,LV);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float TdotH = dot(tangent,H);
		float BdotH = dot(bitangent,H);
		float F = Rs + pow(1.0 - HdotL,5.0)*(1.0 - Rs);
		float Is = F*(sqrt((nx+1)*(ny+1))*pow(NdotH,((nx*pow(TdotH,2) + ny*pow(BdotH,2))/(1-pow(NdotH,2)))))/(8.0*pi*HdotL*max(NdotL,NdotE));
		float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
		return 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is;
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 AskikhmininShirleyAnizotropicPointLight(const int number, const vec3 position, const vec3 normal,const vec3 tangent, const vec3 bitangent, const vec4 diffuse, const vec4 specular,const vec4 ambient, const float Rd, const float Rs, const float nx, const float ny)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		vec3 Eye = normalize(EyePosition.xyz-position);
		vec3 H = normalize(LV+Eye);
		float HdotL = dot(H,LV);
		float NdotH = max(dot(normal,H),0.0);
		float NdotE = max(dot(normal,Eye),0.0);
		float TdotH = dot(tangent,H);
		float BdotH = dot(bitangent,H);
		float F = Rs + pow(1.0 - HdotL,5.0)*(1.0 - Rs);
		float Is = F*(sqrt((nx+1)*(ny+1))*pow(NdotH,((nx*pow(TdotH,2) + ny*pow(BdotH,2))/(1-pow(NdotH,2)))))/(8.0*pi*HdotL*max(NdotL,NdotE));
		float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
		float att = 1/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
		return att*(LocalAmbientLight(number,ambient)*ambient + 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is);
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 AskikhmininShirleyAnizotropicSpotLight(const int number, const vec3 position, const vec3 normal,const vec3 tangent, const vec3 bitangent, const vec4 diffuse, const vec4 specular,const vec4 ambient, const float Rd, const float Rs, const float nx, const float ny)
{
	vec3 LV=Light[number].position.xyz-position;
	float distance = length(LV);
	LV = normalize(LV);
	float NdotL = max(dot(normal,LV),0.0);
	if(NdotL>0)
	{
		float spot = dot(Light[number].SpotDirection,-LV);
		if(spot>cos(radians(Light[number].SpotCuttof)))
		{
			vec3 Eye = normalize(EyePosition.xyz-position);
			vec3 H = normalize(LV+Eye);
			float HdotL = dot(H,LV);
			float NdotH = max(dot(normal,H),0.0);
			float NdotE = max(dot(normal,Eye),0.0);
			float TdotH = dot(tangent,H);
			float BdotH = dot(bitangent,H);
			float F = Rs + pow(1.0 - HdotL,5.0)*(1.0 - Rs);
			float Is = F*(sqrt((nx+1)*(ny+1))*pow(NdotH,((nx*pow(TdotH,2) + ny*pow(BdotH,2))/(1-pow(NdotH,2)))))/(8.0*pi*NdotL*max(NdotL,NdotE));
			float Id = 28.0*Rd*(1.0-Rs)*(1.0-pow(1.0-(NdotL/2.0),5.0))*(1.0-pow(1.0-(NdotE/2.0),5.0))/(23.0*pi);
			spot = pow(spot,Light[number].SpotExponent);
			float att = spot/(Light[number].ConstantAttention + Light[number].LinearAttention * distance + Light[number].QuadratureAttention * distance * distance);
			return att*(LocalAmbientLight(number,ambient)*ambient + 5.5*NdotL*Id*Light[number].diffuse*diffuse + 7.5*Light[number].specular*specular*Is);
		}
		else
			return vec4(0.0,0.0,0.0,1.0);	
	}
	else
		return vec4(0.0,0.0,0.0,1.0);
}

vec4 AskikhmininShirleyAnizotropidLight(const int number, const vec3 position, const vec3 normal,const vec3 tangent, const vec3 bitangent, const vec4 diffuse, const vec4 specular,const vec4 ambient,const vec4 emmision, const float Rd, const float Rs, const float nx, const float ny)
{
	if(Light[number].position.w==0.0)
		return GlobalAmbientLight(ambient) + LocalAmbientLight(number,ambient) + AskikhmininShirleyAnizotropidDirectionalLight(number,  position, normal, tangent, bitangent, diffuse, specular, Rd, Rs, nx, ny) + emmision;
	else
	{
		if(Light[number].SpotCuttof==180.0)
			return GlobalAmbientLight(ambient) + AskikhmininShirleyAnizotropicPointLight(number, position, normal, tangent, bitangent, diffuse, specular, ambient, Rd, Rs, nx, ny) + emmision;		
		else
			return GlobalAmbientLight(ambient) + AskikhmininShirleyAnizotropicSpotLight(number, position, normal, tangent, bitangent, diffuse, specular, ambient, Rd, Rs, nx, ny) + emmision; + emmision;
	}
}




















