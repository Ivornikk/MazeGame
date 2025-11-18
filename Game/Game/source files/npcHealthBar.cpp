#include "../headers/npcHealthBar.h"
NpcHealthBar::NpcHealthBar(float maxHealthTemp, Vector3 pos, Camera cameraTemp) {
	maxHealth = maxHealthTemp;
	health = maxHealth;
	camera = cameraTemp;
	npcPos = pos;
	npcPos.y += 0.5;
	healthBarPos = GetWorldToScreen(npcPos, camera);
}

void NpcHealthBar::Draw() {
	EndMode3D();
	float healthPercentage = health / (maxHealth / 100.f);
	float width = 300.f * healthPercentage / 100.f;
	DrawRectangleV(healthBarPos, { width, 30 }, GREEN);
	DrawRectangleLines(healthBarPos.x, healthBarPos.y, 300, 30, DARKGRAY);
}

void NpcHealthBar::Update(Camera cameraTemp, Vector3 pos, float healthTemp) {

	healthBarPos = GetWorldToScreen(pos, cameraTemp);
	healthBarPos.x -= 150;
	healthBarPos.y -= 60;
	health = healthTemp;
}
