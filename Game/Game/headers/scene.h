#pragma once

#include "raylib.h"
#include "raymath.h"
#include "npc.h"
#include <string>
#include <vector>
#include "../utils.h"
#include "rlgl.h"
#include "resourceManager.h"
#include "items.h"

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); // Draw cube textured
void DrawPlaneTexture(Texture2D texture, Vector3 center, Vector2 size, Color color);

class Scene {
	ResourceManager* rm;
	int** mazeArray;
	int mazeWidth;
	int mazeHeight;
	int minEnemies;
	int maxEnemies;
	Camera3D camera;
	std::vector<NPC*> npcs;
	std::vector<Item*> droppedItems;
	Vector2 finishCell;
	Texture2D texture = LoadTexture("models/textures/craiyon_202557_tile_32x32_pixel_representing_wall.png");
	Texture2D floorTexture = LoadTexture("models/textures/jacob-wheat-finalstonetexture.png");
	Texture2D ceilingTexture = LoadTexture("models/textures/file.png");
public:
	Scene(int** mazeTemp, int widthTemp, int heightTemp, ResourceManager* resourceManager);
	void Display(Player* player, GAME_STATES* gameState);
	void Update(Player* player, GAME_STATES* gameState);
	void Draw();
	void drawCrossbar();
	void handleCameraCollision();
	void handlePlayerAttack(Player* player);
	void updateItems(Player* player);
	void drawItems();
	void reset();
	void handleGameFinish(GAME_STATES* gameState, Player* player);
	Vector2 getPlayerMazePosition();
	bool isWallAtPosition(Vector3 pos);
	Vector3 getCameraTarget();
	Vector3 getCameraPos();
	Camera3D getCamera();
};