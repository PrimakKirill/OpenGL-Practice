#include "World.h"

double cursorCoordinates[2];
void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	cursorCoordinates[0] = xpos;
	cursorCoordinates[1] = ypos;
}

bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool mousebuttons[8];
void mouse_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		mousebuttons[button] = true;
	else if (action == GLFW_RELEASE)
		mousebuttons[button] = false;
}

World::World(glm::vec3 playerPos, GLFWwindow* window):
	actualCam(playerPos, window), mapSize(1000), numAsteroids(100), maxAsteroidsRadius(50)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	actualCam.SetKeys(&keys[0]);
	keysref = &keys[0];
	mousebuttonsref = &mousebuttons[0];
	this->cursorCoord = &cursorCoordinates[0];
	actualCam.SetMouseButtons(&mousebuttons[0]);
	actualCam.SetCursorPos(&cursorCoordinates[0]);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);	
	glfwSetCursorPosCallback(window, cursor_callback);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2.0, height / 2.0);
	player.SetKeys(keysref, mousebuttonsref);
	player.SetCursorData(&cursorCoordinates[0], width / 2.0, height / 2.0);
	player.SetPosition(playerPos);
	actualCam.SetPosition(playerPos - glm::vec3(3 * player.p_Front.x, 0.0f, 2 * player.p_Up.z));
	//AddObjectToWorld(player.GetModel());

	enemies.resize(10);
}

void World::AddObjectToWorld(AObject* newobject)
{
	if (newobject->ObjectWorldID == -1) {
		vectorOfObjects.push_back(newobject);
		newobject->ObjectWorldID = vectorOfObjects.size() - 1;
		newobject->SetFirstScaleCoof();
	}
}

void World::RemoveObject(AObject& object)
{
	if (object.ObjectWorldID != -1) {
		vectorOfObjects.erase(vectorOfObjects.begin() + object.ObjectWorldID);
		for (int i = object.ObjectWorldID; i < vectorOfObjects.size(); i++)
			vectorOfObjects[i]->ObjectWorldID -= 1;
		object.ObjectWorldID = -1;
	}
}


void World::SetBackground(AObject& newbackground)
{
	background = &newbackground;
	background->dirLightCollor[0] = glm::vec3(20.0f);
}

void World::AddLightToWorld(ALight& newlight)
{
	if (newlight.lightWorldID == -1) {
		vectorOfLights.push_back(&newlight);
		newlight.lightWorldID = vectorOfLights.size() - 1;
	}
}

void World::RemoveLight(ALight & light)
{
	if (light.lightWorldID != -1) {
		vectorOfLights.erase(vectorOfLights.begin() + light.lightWorldID);
		for (int i = light.lightWorldID; i < vectorOfLights.size(); i++)
			vectorOfLights[i]->lightWorldID -= 1;
		light.lightWorldID = -1;
	}
}

void World::ApplyLightsToObjectes()
{
	for (int i = 0; i < vectorOfObjects.size(); i++)
	{
		vectorOfObjects[i]->AddLightsToMatr(vectorOfLights);
	}
}

void World::DrawAndUpdateTheWorld()
{
	player.Move();
	MoveEnemies();
	actualCam.SetPosition(player.p_position - GLfloat(2.5)*player.p_Front + GLfloat(1.2)*player.p_Up);
	actualCam.SetCamDir(player.p_Front,player.p_Up);
	if(background != nullptr)
		background->DrawAt(actualCam.GetPos().x, actualCam.GetPos().y, actualCam.GetPos().z, &actualCam);
	DrawMap();
	DrawObjects();
	DrawEnemies();	
	//actualCam.Move();		
}

void World::SetPlayerModel(Model * model)
{
	player.SetModel(model);
	vectorOfObjects.emplace(vectorOfObjects.begin(), model);
	model->ObjectWorldID = 0;
	for (int i = 1; i < vectorOfObjects.size(); i++)
		vectorOfObjects[i]->ObjectWorldID++;
}

void World::SetMapData()
{
	mapData.resize(numAsteroids);	
	for (int i = 0; i < numAsteroids; i++)
	{
		srand(time(0)*i+17*i);
		mapData[i].x = rand() % (int(mapSize) * 2) - mapSize;
		mapData[i].y = rand() % (int(mapSize) * 2) - mapSize;
		mapData[i].z = rand() % (int(mapSize) * 2) - mapSize;
		mapData[i].w = rand() % int(maxAsteroidsRadius-1) + 1;
	}
}

void World::AddAsteroidModelToWorld(AObject * newAsteroid)
{
	vectorOfAsteroidsModels.push_back(newAsteroid);
	newAsteroid->SetFirstScaleCoof();
}

void World::RemoveAsteroidModel(AObject * newAsteroid)
{
	for(int i=0;i<vectorOfAsteroidsModels.size()-1;i++)
		if (vectorOfAsteroidsModels[i] = newAsteroid)
		{
			vectorOfAsteroidsModels.erase(vectorOfAsteroidsModels.begin() + i);
			return;
		}
}

void World::SetEnemyModel(Model * model)
{
	for(int i=0;i<enemies.size();i++)
		enemies[i].SetModel(model);
	AddObjectToWorld(model);
}

void World::SetNumOfEnemies(int num)
{
	if (num > 1)
	{
		enemies.resize(num);
		for (int i = 1; i < enemies.size(); i++)
			enemies[i].SetModel(enemies[0].GetModel());
	}
}

void World::DrawEnemies()
{
	if(enemies[0].GetModel() != nullptr)
		for (int i = 0; i < enemies.size(); i++)
		{
			//enemies[i].GetModel()->DrawAt(enemies[i].e_position+glm::vec3(i), &actualCam);
			enemies[i].Draw(&actualCam);
		}
}

void World::MoveEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Move();
	}
}

void World::DrawMap()
{
	int numModels = vectorOfAsteroidsModels.size();
	for (int i = 0; i < vectorOfAsteroidsModels.size(); i++)
	{
		vectorOfAsteroidsModels[i]->AddLightsToMatr(vectorOfLights);
	}
	for (int i = 1; i < mapData.size(); i++) 
	{
		vectorOfAsteroidsModels[i % numModels]->Scale(vectorOfAsteroidsModels[i % numModels]->first_scaleCoof * mapData[i].w);
		vectorOfAsteroidsModels[i % numModels]->DrawAt(mapData[i].x, mapData[i].y, mapData[i].z, &actualCam);
	}
}

void World::DrawObjects()
{
	ApplyLightsToObjectes();
	if (player.GetModel() != nullptr)
	{
		player.GetModel()->DrawAt(player.p_position, &actualCam);
		for (int i = 1; i < vectorOfObjects.size(); i++) {
			vectorOfObjects[i]->DrawAt(vectorOfObjects[i]->m_position, &actualCam);
		}
	}
	else
		for (int i = 1; i < vectorOfObjects.size(); i++) {
			if(vectorOfObjects[i] != enemies[0].GetModel())
				vectorOfObjects[i]->DrawAt(vectorOfObjects[i]->m_position, &actualCam);
		}
	
}


World::~World()
{
}
