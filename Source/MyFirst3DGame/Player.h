#pragma once
#include "Obgects/models/Model.h"

class Player
{
public:
	Player();
	~Player();

	glm::vec3 p_position;
	glm::vec3 p_velocity;
	glm::vec3 p_acceleration;
	glm::vec3 p_Front;
	glm::vec3 p_Up;
	GLfloat maxSpeed;
	inline void SetMaxSpeed(GLfloat newMaxSpeed) { maxSpeed = newMaxSpeed; };
	inline virtual void SetPosition(const glm::vec3 newposition) { p_position = newposition; };
	inline virtual void SetVelocity(const glm::vec3 newvelocity) { p_velocity = newvelocity; };
	inline virtual void SetAcceleration(const glm::vec3 newacceleration) { p_acceleration = newacceleration;};
	void Move();

	void SetModel(Model* model);
	inline void SetKeys(bool* keyboard, bool* mouse) { keysref = keyboard; mousebuttonsref = mouse; };
	void SetCursorData(double* coord, GLfloat firstCursorX, GLfloat firstCursorY);
	inline Model* GetModel()const { return playerModel; };

private:
	Model* playerModel;
	double* cursorCoord;
	bool* keysref;
	bool* mousebuttonsref;
	GLfloat deltaTime = 0.0f;
	GLfloat previousFrameTime = 0.0f;
	GLfloat cursorPreviousX;
	GLfloat cursorPreviousY;
	GLfloat theta = 0.0f;
	GLfloat phi = 0.0f;
	GLfloat phiFrame = 0.0f;
	GLfloat thetaFrame = 0.0f;	
	GLfloat cam_Sensitivity = 0.05f;
	glm::mat4 coordinatesMatr;
};

