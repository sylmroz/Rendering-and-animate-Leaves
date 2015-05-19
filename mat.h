#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <string>
#include "glm\glm.hpp"
#include <vector>


struct  RGBA
{
	float r, g, b, a;
};
struct Mat
{
	glm::vec4 kd, ka, ks;
	float d,Ns;
	std::string name,map_Ka, map_Kd, map_Ns, map_d, map_bump, map_displ;
	void clear();
	friend std::ostream& operator<<(std::ostream& os, const Mat& mat)
	{
		os << "name " << mat.name << std::endl 
			<< "ka " << mat.ka.r << " " << mat.ka.g << " " << mat.ka.b << " " << mat.ka.a << std::endl
			<< "kd " << mat.kd.r << " " << mat.kd.g << " " << mat.kd.b << " " << mat.kd.a << std::endl
			<< "ks " << mat.ks.r << " " << mat.ks.g << " " << mat.ks.b << " " << mat.ks.a << std::endl
			<< "d " << mat.d << std::endl
			<< "Ns " << mat.Ns << std::endl
			<< "map_Ka " << mat.map_Ka  
			<< std::endl<< "map_Kd " << mat.map_Kd << std::endl
			<< "map_Ns " << mat.map_Ns << std::endl
			<< "map_d " << mat.map_d << std::endl
			<< "map_disp " << mat.map_displ << std::endl
			<< "map_bump " << mat.map_bump << std::endl;
		return os;
	}
};

class MatLoader
{
public:
	MatLoader();
	MatLoader(const std::string& FileName);
	~MatLoader();
	
protected:
	std::vector<Mat> materials;
	std::vector<std::string> texturename;
	std::string path;

	void CreatePath(std::string name);
	bool LoadFile(const std::string& FileName);
	int TextureLayer(const std::string& name);
private:
};


#endif //MAT_H