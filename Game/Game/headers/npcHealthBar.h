#pragma once

#include "raylib.h"

class NpcHealthBar {
	float maxHealth;
	float health;
	Vector3 npcPos;
	Vector2 healthBarPos;
	Camera camera;
public:
	NpcHealthBar(float maxHealthTemp, Vector3 pos, Camera cameraTemp);
	void Draw();
	void Update(Camera cameraTemp, Vector3 pos, float healthTemp);
};