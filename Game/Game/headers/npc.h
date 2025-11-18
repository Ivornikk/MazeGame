#pragma once

#include <raylib.h>
#include <raymath.h>
#include <random>
#include <vector>
#include <queue>
#include "player.h"
#include "npcHealthBar.h"
#include "resourceManager.h"
#include "../utils.h"

class NPC {
	ResourceManager* rm;
	int id = 1;
	// Basically a copy of the original maze map with the difference that cells which were chosen for npc spawn point
	// are assigned the value 2.
	int** mazeArray;
	std::vector<Vector2> emptyCells;
	std::vector<Vector2> path;
	int emptyCellsNum;
	int mazeWidth;
	int mazeHeight;
	float cooldown;
	// The time that has passed after the npc hit the player
	float timePassedAfterHit;
	float health;
	float damage;
	float speed;
	float range;
	Vector2 spawnCell;
	Vector2 playerPos;
	Vector2 currentCell;
	BoundingBox hitbox;
	Model model;
	Vector3 pos;
	NpcHealthBar* healthBar;
	int animationsCount;
	unsigned int animCurrentFrame;
	ModelAnimation* animations;
	bool isDead;
	int npcsCount;
	// When the player is close enough this variable will change to true and the npc will start to follow him.
	bool isTriggered = false;
	bool attackAnimFinished = true;
	bool isStunFinished = true;
	bool isDeathFinished = false;

	// If true then the npc will drop a key after death
	bool hasKey;
public:
	NPC() :
		health(100), damage(10), speed(4), range(4), mazeWidth(30), mazeHeight(30), rm(new ResourceManager()) {
		int** maze = new int*[mazeWidth];
		for (int i = 0; i < mazeWidth; i++)
			maze[i] = new int[mazeHeight];
		mazeArray = maze;
	}
	NPC(Camera3D camera, int** mazeArray, float healthTemp, float damageTemp, float speedTemp, float rangeTemp, int mazeWidthTemp, int mazeHeightTemp, ResourceManager* resourceManager);
	~NPC();
	void Display(Vector2 newPlayerPos, Player* player, Camera3D newCamera, int npcsLasted);
	void Draw();
	void Update(Vector2 newPlayerPos, Player* player, Camera3D newCamera, int npcsLasted);
	void updateCooldown();
	void damagePlayer(Player* player);
	void takeDamage(float damage);
	float getHealth();
	void followPlayer();
	void handleOrientation();
	void handleAnimation();
	void initializeEmptyCells();
	void setPlayerPos(Vector2 pos);
	void handleHealthBarDrawing();
	void setKey(bool val);
	bool checkIfHasKey();
	// Returns randomly chosen cell that is assigned as a spawn point of the npc.
	Vector2 chooseSpawnCell(int** npcMapTemp);
	Vector3 getPosition();
	BoundingBox getHitbox();
	ModelAnimation getAnimationByName(std::string name, ModelAnimation* animations, int animationsCount);
	std::vector<Vector2> bfsShortestPath();
	bool isCellValid(int x, int y);
	bool getIsDead();
};