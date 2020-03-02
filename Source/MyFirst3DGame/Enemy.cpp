#include "Enemy.h"



Enemy::Enemy()
	:e_position(glm::vec3(0)), e_velocity(glm::vec3(0)), e_acceleration(glm::vec3(0)),
	e_Front(glm::vec3(1.0f, 0.0f, 0.0f)), e_Up(glm::vec3(0.0f, 0.0f, 1.0f)), maxSpeed(10),
	coordinatesMatr(glm::mat4(1.0f)), enemyModel(nullptr)
{
}

void Enemy::Move()
{
	deltaTime = glfwGetTime() - previousFrameTime;
	previousFrameTime = glfwGetTime();
	GLfloat accRate = deltaTime * GLfloat(250.0f);
	GLfloat angleRate = deltaTime * GLfloat(0.01f);

	e_position += deltaTime * e_velocity;
	enemyModel->SetPosition(e_position);
	e_velocity += deltaTime * e_acceleration;
	if (sqrt(glm::dot(e_velocity, e_velocity)) > maxSpeed)
		e_velocity = glm::normalize(e_velocity) *maxSpeed;

	e_acceleration = glm::vec3(0.0f);

	//Front/Back
	srand(deltaTime / accRate + glfwGetTime() + reinterpret_cast<int>(this));
	e_acceleration += GLfloat((rand() % 10000)/5000.0-1) * e_Front * accRate;
	if (deltaTime < 5.0)
	{
		//Rotete
		GLfloat angle = angleRate * GLfloat((rand() % 10000) / 5000.0 - 1);
		e_Up = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(e_Front, 0.0f))) * glm::vec4(e_Up, 0.0f);
		modelMatr = glm::rotate(modelMatr, angle, glm::vec3(coordinatesMatr * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
		//Up/Down
		angle = angleRate * GLfloat((rand() % 10000) / 5000.0 - 1);
		glm::vec3 prevRight = glm::cross(e_Front, e_Up);
		e_Up = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_Up, 0.0f);
		e_Front = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_Front, 0.0f);
		//enemyModel->Rotate(coordinatesMatr * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), glm::degrees(angle));
		modelMatr = glm::rotate(modelMatr, angle, glm::vec3(coordinatesMatr * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)));
		e_velocity = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_velocity, 0.0f);
		//Left/Right
		prevRight = glm::cross(e_Front, e_Up);
		angle = angleRate * GLfloat((rand() % 10000) / 5000.0 - 1);
		e_Up = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_Up, 0.0f);
		e_Front = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_Front, 0.0f);
		//enemyModel->Rotate(coordinatesMatr * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), glm::degrees(angle));
		modelMatr = glm::rotate(modelMatr, angle, glm::vec3(coordinatesMatr * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)));
		e_velocity = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(e_velocity, 0.0f);
	}
}

void Enemy::Draw(Camera* cam)
{
	enemyModel->m_Matrix = modelMatr;
	enemyModel->DrawAt(e_position, cam);
}

void Enemy::SetModel(Model * model)
{
	enemyModel = model;
	enemyModel->SetPosition(e_position);
	enemyModel->SetVelocity(e_velocity);
	coordinatesMatr = glm::inverse(model->m_Matrix);
	modelMatr = model->m_Matrix;
}


Enemy::~Enemy()
{
}
