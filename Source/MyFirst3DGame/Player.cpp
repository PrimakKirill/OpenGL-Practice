#include "Player.h"


Player::Player()
	:p_position(glm::vec3(0)), p_velocity(glm::vec3(0)), p_acceleration(glm::vec3(0)),
	p_Front(glm::vec3(1.0f,0.0f,0.0f)),p_Up(glm::vec3(0.0f,0.0f,1.0f)),maxSpeed(10),
	coordinatesMatr(glm::mat4(1.0f))
{
}


Player::~Player()
{
}

void Player::Move()
{
	deltaTime = glfwGetTime() - previousFrameTime;
	previousFrameTime = glfwGetTime();
	GLfloat accRate = deltaTime * GLfloat(400.0f);
	GLfloat angleRate = deltaTime * GLfloat(0.6f);

	p_position += deltaTime * p_velocity;
	playerModel->SetPosition(p_position);
	p_velocity += deltaTime * p_acceleration;
	if (sqrt(glm::dot(p_velocity, p_velocity)) > maxSpeed)
		p_velocity = glm::normalize(p_velocity) *maxSpeed;

	p_acceleration = glm::vec3(0.0f);	

	if (keysref[GLFW_KEY_LEFT_SHIFT])
	{
		p_acceleration += accRate * p_Front;
	}

	if (keysref[GLFW_KEY_LEFT_CONTROL])
	{
		p_acceleration -= accRate * p_Front;
	}

	GLfloat v = sqrt(glm::dot(p_velocity, p_velocity));
	if (v != 0.0)
	{
		if (keysref[GLFW_KEY_Q])
		{
			p_Up = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(p_Front, 0.0f))) * glm::vec4(p_Up, 0.0f);
			playerModel->Rotate(coordinatesMatr*glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::degrees(-angleRate));
		}

		if (keysref[GLFW_KEY_E])
		{
			p_Up = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(p_Front, 0.0f))) * glm::vec4(p_Up, 0.0f);
			playerModel->Rotate(coordinatesMatr * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::degrees(angleRate));
		}
		glm::vec3 prevRight = glm::cross(p_Front, p_Up);
		if (keysref[GLFW_KEY_W])
		{
			p_Up = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_Up, 0.0f);
			p_Front = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_Front, 0.0f);
			playerModel->Rotate(coordinatesMatr * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), glm::degrees(-angleRate));
			p_velocity = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_velocity, 0.0f);
		}

		if (keysref[GLFW_KEY_S])
		{
			p_Up = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_Up, 0.0f);
			p_Front = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_Front, 0.0f);
			playerModel->Rotate(coordinatesMatr * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), glm::degrees(angleRate));
			p_velocity = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(prevRight, 0.0f))) * glm::vec4(p_velocity, 0.0f);
		}

		if (keysref[GLFW_KEY_A])
		{
			p_Front = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(p_Up, 0.0f))) * glm::vec4(p_Front, 0.0f);
			playerModel->Rotate(coordinatesMatr * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::degrees(angleRate));
			p_velocity = glm::rotate(glm::mat4(1.0f), angleRate, glm::vec3(glm::vec4(p_Up, 0.0f))) * glm::vec4(p_velocity, 0.0f);
		}

		if (keysref[GLFW_KEY_D])
		{
			p_Front = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(p_Up, 0.0f))) * glm::vec4(p_Front, 0.0f);
			playerModel->Rotate(coordinatesMatr * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::degrees(-angleRate));
			p_velocity = glm::rotate(glm::mat4(1.0f), -angleRate, glm::vec3(glm::vec4(p_Up, 0.0f))) * glm::vec4(p_velocity, 0.0f);
		}
	}	
}

void Player::SetModel(Model * model)
{
	playerModel = model; 
	playerModel->SetPosition(p_position);
	playerModel->SetVelocity(p_velocity);
	coordinatesMatr = glm::inverse(model->m_Matrix);
}

void Player::SetCursorData(double * coord, GLfloat firstCursorX, GLfloat firstCursorY)
{
	cursorCoord = coord; 
	cursorPreviousX = firstCursorX; 
	cursorPreviousY = firstCursorY;
}
