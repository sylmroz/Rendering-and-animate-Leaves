#ifndef CAMERA_H
#define CAMERA_H

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtx\euler_angles.hpp"

class Camera
{
public:
	Camera(glm::vec3 pos, float fov, float znear, float zfar, float aspect, glm::vec3 target=glm::vec3(0.0, 0.0, -1.0));
	void Translate(float atm);
	void TranslateInRL(float atm);
	void Rotate(float xoffsed, float yoffsed);
	glm::mat4 GetVievMatrix(){ return glm::lookAt(position, position + front, up); }
	glm::mat4 GetProjectionMatrix(){ return projection; }
	glm::mat4 GetOrthogonalMatrix(){ return orhogonal; }
	glm::vec4 GetEye() { return glm::vec4(position, 1.0); }
protected:
private:
	glm::mat4 projection, orhogonal;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldup;
	float yaw, pich;
	void Update();
};

#endif