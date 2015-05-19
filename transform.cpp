#include "transform.h"

Transform::Transform()
{
	m_pos = glm::vec3(0.0f, 0.f, 0.0f);
	m_rot = glm::vec3(0.0f, 0.f, 0.0f);
	m_scal = glm::vec3(1.0f, 1.0f, 1.0f);
}
Transform::~Transform()
{
}
glm::mat4 Transform::GetModel()
{
	glm::mat4 position = glm::translate(m_pos);
	glm::mat4 scale = glm::scale(m_scal);
	glm::mat4 rotateX = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotateZ = glm::rotate(m_rot.z, glm::vec3(1.0f, 0.0f, 1.0f));

	glm::mat4 rotate = rotateZ*rotateY*rotateX;

	return position*rotate*scale;
}
glm::vec3 Transform::GetPos()
{
	return m_pos;
}
glm::vec3 Transform::GetRot()
{
	return m_rot;
}
glm::vec3 Transform::GetScal()
{
	return m_scal;
}
void Transform::SetPos(const glm::vec3& pos)
{
	m_pos = pos;
}
void Transform::SetRot(const glm::vec3& rot)
{
	m_rot = rot;
}
void Transform::SetScale(const glm::vec3& scale)
{
	m_scal = scale;
}