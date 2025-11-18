#include "../headers/item.h"

float Item::getCameraYaw(Camera3D camera)
{
	Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
	float yaw = atan2(forward.x, forward.z);
	return yaw;
}

void Item::Draw(Camera3D camera) {
	float yawDeg = getCameraYaw(camera) * RAD2DEG;
	Vector3 pos = { camera.target.x, 1, camera.target.z };
	DrawModelEx(model, camera.target, { 0,1,0 }, yawDeg, { 1,1,1 }, WHITE);
}

void Item::Draw() {
	DrawModel(model, pos, 0.8, WHITE);
}

void Item::setState(State newState) {
	state = newState;
}

void Item::Update() {
	handleAnimations();
}

void Item::handleAnimations() {
	ModelAnimation idleAnim = getModelAnimationByName("Idle", animations, animationsCount);
	ModelAnimation walkAnim = getModelAnimationByName("Walk", animations, animationsCount);
	ModelAnimation attackAnim = getModelAnimationByName("Attack", animations, animationsCount);
	ModelAnimation hoverAnim = getModelAnimationByName("Hover", animations, animationsCount);

	if (state == DROPPED) {
		frameCount++;
		UpdateModelAnimation(model, hoverAnim, frameCount);
	}
	else if (state == EQUIPPED) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isAttackFinished) {
			frameCount = 0;
			isAttackFinished = false;
		}
		if (isAttackFinished)
			if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
				frameCount++;
				UpdateModelAnimation(model, walkAnim, frameCount);
			}
			else if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_S) || IsKeyReleased(KEY_D)) {
				frameCount = 0;
				UpdateModelAnimation(model, walkAnim, frameCount);
			}
			else {
				frameCount++;
				UpdateModelAnimation(model, idleAnim, frameCount);
			}
		else {
			frameCount++;
			if (attackAnim.frameCount == frameCount) isAttackFinished = true;
			UpdateModelAnimation(model, attackAnim, frameCount);
		}
	}

}

float Item::getDamage() {
	return damage;
}

float Item::getRange() {
	return range;
}

bool Item::isReloaded() {
	return isAttackFinished;
}

int Item::getId() {
	return id;
}

BoundingBox Item::getHitbox() {
	return {
		{ pos.x - 1, 0, pos.z - 1 },
		{ pos.x + 1, 2, pos.z + 1 }
	};
}

Texture2D Item::getHotBarIcon() {
	return hotBarIcon;
}

ModelAnimation Item::getModelAnimationByName(std::string name, ModelAnimation* animations, int animationsCount) {
	for (int i = 0; i < animationsCount; i++) {
		if (animations[i].name == name) return animations[i];
	}
	return animations[0];
}

