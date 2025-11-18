#pragma once

#include "item.h"

class Key : public Item {
	ResourceManager* rm;
public:
	Key(ResourceManager* resourceManager, Vector3 defPos);
}; 

class Sword : public Item {
	ResourceManager* rm;
public:
	Sword(ResourceManager* resourceManager, Vector3 defPos);
};

class Mace : public Item {
	ResourceManager* rm;
public:
	Mace(ResourceManager* resourceManager, Vector3 defPos);
};

class CrystalSword : public Item {
	ResourceManager* rm;
public:
	CrystalSword(ResourceManager* resourceManager, Vector3 defPos);
};
