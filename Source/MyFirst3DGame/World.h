#pragma once
#include <ctime>

#include "Camera.h"
#include "Obgects/AObject.h"
#include "Obgects/Light/ALight.h"
#include "Mesh.h"
#include "Player.h"
#include "Enemy.h"

class World
{
public:
	World(glm::vec3 playerPos, GLFWwindow* window);
	~World();

	Camera actualCam;

	void AddObjectToWorld(AObject* newobject);
	void RemoveObject(AObject& object);
	std::vector<AObject*> vectorOfObjects;

	AObject* background;
	void SetBackground(AObject& newbackground);

	void AddLightToWorld(ALight& newlight);
	void RemoveLight(ALight& light);
	std::vector<ALight*> vectorOfLights;
	void ApplyLightsToObjectes();

	void DrawAndUpdateTheWorld();
	Player player;
	void SetPlayerModel(Model* model);

	void SetMapData();
	inline void SetNumAsteroids(int newNum) {numAsteroids = newNum;	};
	inline void SetMaxAsteroidsRadius(float newR) { maxAsteroidsRadius = newR; };
	void AddAsteroidModelToWorld(AObject* newAsteroid);
	void RemoveAsteroidModel(AObject* newAsteroid);

	void SetEnemyModel(Model* model);
	void SetNumOfEnemies(int num);

private:
	bool* keysref;
	bool* mousebuttonsref;
	double* cursorCoord;

	std::vector<glm::vec4> mapData;
	int numAsteroids;
	float maxAsteroidsRadius;
	float mapSize;
	std::vector<AObject*> vectorOfAsteroidsModels;
	void DrawMap();
	void DrawObjects();

	std::vector<Enemy> enemies;
	void DrawEnemies();
	void MoveEnemies();
};

