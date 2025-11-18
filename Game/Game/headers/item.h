#pragma once

#include "raylib.h"
#include "raymath.h"
#include "resourceManager.h"

enum State {
	DROPPED,
	PICKED_UP,
	EQUIPPED,
};

enum ItemType {
	WEAPON,
	ITEM
};

class Item {
	State state;
protected:
	ResourceManager* rm;
	int id;
	float damage;
	float range;
	int frameCount;
	int animationsCount;
	bool isAttackFinished;
	ItemType type;
	Texture2D hotBarIcon;
	Model model;
	ModelAnimation* animations;
	Vector3 pos;
public:
	Item(ResourceManager* resourceManager, Vector3 defPos, float damageTemp, float rangeTemp)
		: rm(resourceManager), pos(defPos), damage(damageTemp), range(rangeTemp) {
		state = DROPPED;
		frameCount = 0;
		isAttackFinished = true;
	};
	float getCameraYaw(Camera3D camera);
	void Draw(Camera3D camera);
	void Draw();
	void setState(State newState);
	void Update();
	void handleAnimations();
	float getDamage();
	float getRange();
	bool isReloaded();
	int getId();
	BoundingBox getHitbox();
	Texture2D getHotBarIcon();
	ModelAnimation getModelAnimationByName(std::string name, ModelAnimation* animations, int animationsCount);
};