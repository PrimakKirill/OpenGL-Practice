#include "GLEW/include/GL/glew.h"
#include "GLFW/include/GLFW/glfw3.h"
#include "glm\glm\glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "Obgects/Box/Box.h"
#include "Obgects/models/Model.h"
#include "Camera.h"
#include "World.h"
#include "Obgects/Light/PointLight.h"
#include "Obgects/Light/DirectedLight.h"
#include "Obgects/Light/FlashLight.h"

#include <vector>
#include <Windows.h>

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "assimp\config.h"


int main()
{
	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1080, 720, "My Test", NULL, NULL);//960, 540, "My Test", NULL, NULL);
	glfwSwapInterval(100);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewInit();

	glEnable(GL_DEPTH_TEST);

	ShowWindow(GetConsoleWindow(), 0);//Скрывает консоль

	World world(glm::vec3(-15.0f, 0.0f, 10.0f), window);

	//Экран во время загрузки и фон
	/* Render here */
	glClearColor(2.0f, 0.5f, 2.0f, 1.0f);
	Box background(1150.0f);
	background.SetTexture("Obgects/Box/Res/Space.png");
	world.SetBackground(background);
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
	/* Poll for and process events */
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			

	//Box с подсказками управления
	Box box1(30.0f);
	box1.SetTexture("Obgects/Box/Res/Control.png");
	box1.SetSpecularMap("Obgects/Box/Res/BoxSpec.png");
	box1.SetPosition(glm::vec3(70.0f, 0.0f, 5.0f));
	world.AddObjectToWorld(&box1);

	//Направленный свет от звезды на фоне
	DirectedLight starLight;
	starLight.SetDir(glm::vec3(-1.0f, 0.0f, 0.0f));
	starLight.SetColor(glm::vec3(252.0, 153.0, 0.8f) / 255.0f);
	world.AddLightToWorld(starLight);

	//Направленный свет из космоса
	DirectedLight spaceLight;
	spaceLight.SetDir(glm::vec3(1.0f, 0.1f, 0.1f));
	spaceLight.SetColor(glm::vec3(3.0f, 30.0f, 100.0f) / 255.0f);
	world.AddLightToWorld(spaceLight);
	
	//Свет на корабле(фонарик)
	FlashLight sheapLight;
	sheapLight.SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	sheapLight.SetAngle(15.0f);
	sheapLight.SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
	sheapLight.SetDir(glm::vec3(1.0f, 0.0f, 0.0f));
	world.AddLightToWorld(sheapLight);
	
	//Модель астероида  и передача его модели миру
	Model astr("Obgects/models/Asteroids/13905_Jupiter_V1_l3.obj");
	astr.SetPosition(glm::vec3(10.0f));
	astr.Scale(0.002);
	world.AddAsteroidModelToWorld(&astr);

	//Модель корабля персонажа и установка как игровой модели в мир
	Model playerModel("Obgects/models/Player/13885_UFO_Triangle_V1_L2.obj");
	playerModel.Rotate(glm::vec3(0.0f, 0.0f, 1.0f), 180.0f);
	playerModel.Scale(0.0005f);
	world.SetPlayerModel(&playerModel);
	world.player.SetMaxSpeed(50.0);

	//Модель врагов и передача их миру
	Model enemyrmod("Obgects/models/Enemies/10475_Rocket_Ship_v1_L3.obj");
	enemyrmod.Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);
	enemyrmod.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
	enemyrmod.Rotate(glm::vec3(0.0f, 0.0f, 1.0f), 180.0f);
	enemyrmod.Scale(0.01f);
	world.SetEnemyModel(&enemyrmod);

	//Задание параметров астероидов на карте
	world.SetMaxAsteroidsRadius(70.0f);
	world.SetNumAsteroids(175);
	//Генерация случайной карты
	world.SetMapData();
	
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(2.0f, 0.5f, 2.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Прикрепление света корабля к позиции корабля
		sheapLight.SetDir(world.actualCam.GetCamDir());
		sheapLight.SetPosition(world.actualCam.GetPos());
		
		//Отрисовка мира и рассчет нвых координат объектов на карте
		world.DrawAndUpdateTheWorld();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}