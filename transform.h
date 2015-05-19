#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"

class Transform
{
public:
	Transform();
	~Transform();
	glm::mat4 GetModel();
	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScal();
	void SetPos(const glm::vec3& pos);
	void SetRot(const glm::vec3& rot);
	void SetScale(const glm::vec3& scale);
protected:
private:
	glm::vec3 m_pos, m_rot, m_scal;
};

#endif //TRANSFORM_H