#pragma once
#include "Obgects/models/Model.h"
class Enemy
{
public:
	Enemy();
	~Enemy();

	glm::vec3 e_position;
	glm::vec3 e_velocity;
	glm::vec3 e_acceleration;
	glm::vec3 e_Front;
	glm::vec3 e_Up;
	GLfloat maxSpeed;
	inline void SetMaxSpeed(GLfloat newMaxSpeed) { maxSpeed = newMaxSpeed; };
	inline virtual void SetPosition(const glm::vec3 newposition) { e_position = newposition; };
	inline virtual void SetVelocity(const glm::vec3 newvelocity) { e_velocity = newvelocity; };
	inline virtual void SetAcceleration(const glm::vec3 newacceleration) { e_acceleration = newacceleration; };
	void Move();
	void Draw(Camera* cam);

	void SetModel(Model* model);
	inline Model* GetModel()const { return enemyModel; };

private:
	Model* enemyModel;
	GLfloat deltaTime = 0.0f;
	GLfloat previousFrameTime = 0.0f;
	glm::mat4 coordinatesMatr;
	glm::mat4 modelMatr;
};

