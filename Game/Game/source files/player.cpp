#include "../headers/player.h"

float Player::getHealth() {
	return health;
}

float Player::getMaxHealth() {
	return maxHealth;
}

void Player::takeDamage(float damage) {
	health -= damage;
}

void Player::resetHealth() {
	health = maxHealth;
}

void Player::Display(Camera3D camera) {
	Update();

	BeginMode3D(camera);

	Draw(camera);

	EndMode3D();
}

void Player::Draw(Camera3D camera) {
	currentWeapon->Draw(camera);
	EndMode3D();
	inventory.drawHotBar();
	BeginMode3D(camera);
}

void Player::Update() {
	updateSelectedWeapon();
	currentWeapon->Update();
}

void Player::updateSelectedWeapon() {
	if (IsKeyPressed(KEY_ONE))
		inventory.setSelectedItem(1);
	if (IsKeyPressed(KEY_TWO))
		inventory.setSelectedItem(2);
	if (IsKeyPressed(KEY_THREE))
		inventory.setSelectedItem(3);
	if (IsKeyPressed(KEY_FOUR))
		inventory.setSelectedItem(4);
	if (IsKeyPressed(KEY_FIVE))
		inventory.setSelectedItem(5);
	if (IsKeyPressed(KEY_SIX))
		inventory.setSelectedItem(6);
	if (IsKeyPressed(KEY_SEVEN))
		inventory.setSelectedItem(7);
	if (IsKeyPressed(KEY_EIGHT))
		inventory.setSelectedItem(8);
	if (IsKeyPressed(KEY_NINE))
		inventory.setSelectedItem(9);
	currentWeapon = inventory.getSelectedItem();

}

void Player::pickUpItem(Item* item) {
	inventory.addItem(item);
}

int Player::getKeysCount() {
	return inventory.getKeysCount();
}

float Player::getDamage() {
	return currentWeapon->getDamage();
}

float Player::getRange() {
	return currentWeapon->getRange();
}

bool Player::isReloaded() {
	return currentWeapon->isReloaded();
}

void Player::resetInventory() {
	inventory.reset();
}
