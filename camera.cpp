#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 pos, float fov, float znear, float zfar, float aspect, glm::vec3 target)
{
	position = pos;
	front = target;
	worldup = glm::vec3(0.0, 1.0, 0.0);
	projection = glm::perspective(glm::radians(fov), aspect, znear, zfar);
	orhogonal = glm::ortho(-1.5f * float(aspect), 1.5f * float(aspect), -1.5f, 1.5f, -10.0f, 10.f);
	yaw = -90.0f;
	pich = 0.0f;
	Update();
}

void Camera::Update()
{
	glm::vec3 f;
	f.x = glm::cos(glm::radians(yaw))*glm::cos(glm::radians(pich));
	f.y = glm::sin(glm::radians(pich));
	f.z = glm::sin(glm::radians(yaw))*glm::cos(glm::radians(pich));
	front = glm::normalize(f);
	right = glm::normalize(glm::cross(front, worldup));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::Rotate(float xoffsed, float yoffsed)
{
	yaw += xoffsed;
	pich += yoffsed;
	if (pich > 89.9f)
		pich = 89.8f;
	if (pich < -89.9f)
		pich = -89.8f;
	Update();
}
void Camera::Translate(float atm)
{
	position += front*atm;
	std::cout << position.y << std::endl;
	Update();
}

void Camera::TranslateInRL(float atm)
{
	position -= right*atm;
	Update();
}