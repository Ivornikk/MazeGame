#pragma once

#include <raylib.h>
#include <raymath.h>
#include "resourceManager.h"
#include "inventory.h"

class Player {
	float health;
	float maxHealth;
	Inventory inventory;
	Item* currentWeapon;
public:
	Player(ResourceManager* resourceManager) : inventory(Inventory(resourceManager)) {
		maxHealth = 1000.f;
		health = maxHealth;
		currentWeapon = inventory.getSelectedItem();
	};
	Player() : inventory(Inventory(new ResourceManager())) {
		maxHealth = 1000.f;
		health = maxHealth;
		currentWeapon = inventory.getSelectedItem();
	};

	float getHealth();
	float getMaxHealth();
	void takeDamage(float damage);
	void resetHealth();
	void Display(Camera3D camera);
	void Draw(Camera3D camera);
	void Update();
	void updateSelectedWeapon();
	void pickUpItem(Item* item);
	int getKeysCount();
	float getDamage();
	float getRange();
	bool isReloaded();
	void resetInventory();
};