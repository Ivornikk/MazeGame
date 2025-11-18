#pragma once
#include "maze.h"
#include "raylib.h"
#include "raymath.h"

class MiniMap {
	int** mazeArr;
	std::vector<Vector2> npcPath;
	int width;
	int height;
	int finishCellX;
	int finishCellY;
	Texture2D playerArrow;
	Vector2 PlayerPos;
	// The angle of rotation of the player. Used to set the rotation of the arrow and synchronize it with 
	// the 3D camera.
	float viewAngle;
public:
	MiniMap(int** mazeTemp, int widthTemp, int heightTemp, int finishXTemp, int finishYTemp);
	void Draw();
	void setPlayerPos(Vector2 pos);
	void setViewAngle(Vector3 cameraTarget, Vector3 cameraPosition);
};