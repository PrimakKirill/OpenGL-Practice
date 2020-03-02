#pragma once

#include "GLEW/include/GL/glew.h"
#include "GLFW/include/GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include <vector>
#include "Obgects/Light/ALight.h"
//#include "Obgects/AObject.h"

//struct Lights
//{
//	glm::vec3 lightPosition;
//	glm::vec3 lightColor;
//};

class Camera
{
public:
	Camera(const glm::vec3 position , GLFWwindow* window);
	~Camera();
	void Move();
	inline glm::mat4 GetMatr() const { return cam_ProjMatr * cam_ViewMatr;};
	inline glm::vec3 GetPos() const { return cam_Position; };
	void inline SetPosition(glm::vec3 newPos) { cam_Position = newPos; };
	inline GLfloat GetCamSpeed() const { return cam_Speed; };
	glm::vec3 GetCamDir() const { return cam_Front; };
	void SetCamDir(glm::vec3 newDir, glm::vec3 camUp);
	
	//void AddLightAt(glm::vec3 position, ALight& light);
	//void RemoveLight(ALight light);
	//void ApplyLightChanges(ALight light);
	//std::vector<Lights> vectorOfWorldLights;

	inline GLfloat GetDeltaTime() { return daltaTime; };
	

private:
	glm::vec3 cam_Position;
	glm::vec3 cam_Front;
	glm::vec3 cam_Up;
	glm::mat4 cam_ViewMatr;
	glm::mat4 cam_ProjMatr;

	GLfloat cam_Speed;
	GLfloat daltaTime=0.0f;
	GLfloat previousFrameTime=0.0f;

	GLfloat coursorPreviousX;
	GLfloat coursorPreviousY;
	GLfloat theta = 0.0f;
	GLfloat phi = 0.0f;
	GLfloat cam_Sensitivity = 0.05f;

	bool* keys;
	bool* mousebuttons;
	double* cursorCoord;
public:
	inline void SetKeys(bool* newkey) { keys=newkey; };
	inline void SetMouseButtons(bool* newkey) { mousebuttons = newkey; }; 
	inline void SetCursorPos(double* coord) { cursorCoord = coord; };
};




