#include "Camera.h"
#include <iostream>



//double cursorCoord[2];
//void cursor_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	cursorCoord[0] = xpos;
//	cursorCoord[1] = ypos;
//}

Camera::Camera(const glm::vec3 position, GLFWwindow* window)
	:cam_Position(position), cam_Front(glm::vec3(-1.0f, 0.0f, 0.0f)),cam_Up(glm::vec3(0.0f, 0.0f, 1.0f)),
	cam_ProjMatr(glm::mat4(1.0f)), cam_ViewMatr(glm::mat4(1.0f))
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	cam_ProjMatr = glm::perspective(45.0f, (width*1.0f) / (height*1.0f), 0.1f, 1000.0f);
	cam_ViewMatr = glm::lookAt(cam_Position, cam_Position + cam_Front, cam_Up);

	
	//glfwSetCursorPos(window, width / 2.0, height / 2.0);
	coursorPreviousX = width / 2.0;
	coursorPreviousY = height / 2.0;
	//glfwSetCursorPosCallback(window, cursor_callback);	
}

Camera::~Camera()
{
}



void Camera::Move()
{	
	daltaTime = glfwGetTime() - previousFrameTime;
	previousFrameTime = glfwGetTime();
	cam_Speed = 3.0f * daltaTime;

	//Rotation
	phi += cam_Sensitivity * (cursorCoord[0] - coursorPreviousX);
	theta += cam_Sensitivity * (cursorCoord[1] - coursorPreviousY);
	coursorPreviousX = cursorCoord[0];
	coursorPreviousY = cursorCoord[1];
	if (theta > 89.5)
		theta = 89.5;
	if (theta < -89.5)
		theta = -89.5;

	if (phi >= 360.0)
		phi -= 360.0;
	if (phi <= 0.0)
		phi += 360.0;

	cam_Front.x = cos(glm::radians(theta))*cos(glm::radians(phi));
	cam_Front.y = -cos(glm::radians(theta))*sin(glm::radians(phi));
	cam_Front.z = -sin(glm::radians(theta));
	cam_Front = glm::normalize(cam_Front);

	//Translation
	//float camz = cam_Position.z;
	//if (keys[GLFW_KEY_W])
	//{
	//	cam_Position += cam_Speed * cam_Front;
	//	//cam_Position.z = camz;
	//}
	//if (keys[GLFW_KEY_S])
	//{
	//	cam_Position -= cam_Speed * cam_Front;
	//	//cam_Position.z = camz;
	//}
	//if (keys[GLFW_KEY_A])
	//{
	//	cam_Position += glm::normalize(glm::cross(cam_Up, cam_Front))*cam_Speed;
	//	//cam_Position.z = camz;
	//}
	//if (keys[GLFW_KEY_D])
	//{
	//	cam_Position += glm::normalize(glm::cross(cam_Front, cam_Up))*cam_Speed;
	//	//cam_Position.z = camz;
	//}

	if (mousebuttons[GLFW_MOUSE_BUTTON_1])
	{
		cam_Position += cam_Front *2.0f;
		//cam_Position.z = camz;
	}

	//MakeMatrix
	cam_ViewMatr = glm::lookAt(cam_Position, cam_Position + cam_Front, cam_Up);
}

void Camera::SetCamDir(glm::vec3 newDir,glm::vec3 camUp)
{
	cam_Front = newDir;
	cam_Up = camUp;
	cam_ViewMatr = glm::lookAt(cam_Position, cam_Position + cam_Front, camUp);
}

//void Camera::AddLightAt(glm::vec3 position, ALight &light)
//{
//	vectorOfWorldLights.push_back({ position,light.GetColor() });
//	light.numberAtWorld = vectorOfWorldLights.size()-1;
//	
//}
//
//void Camera::RemoveLight(ALight light)
//{
//	if (light.numberAtWorld != -1) {
//		vectorOfWorldLights.erase(vectorOfWorldLights.begin() + light.numberAtWorld);
//		light.numberAtWorld = -1;
//	}
//}
//
//void Camera::ApplyLightChanges(ALight light)
//{
//	
//	if (light.numberAtWorld != -1) {
//		vectorOfWorldLights[light.numberAtWorld].lightColor = light.GetColor();	
//		vectorOfWorldLights[light.numberAtWorld].lightPosition = light.GetPosition();
//	}
//}



