#pragma once

#include "items.h"
#include "resourceManager.h"
#include <vector>

class Inventory {
	ResourceManager* rm;
	std::vector<Item*> items;
	Item* selectedItem;
	int selectedSlot;
	const int maxSlots = 10;
public:
	Inventory(ResourceManager* resourceManager);
	Item* getSelectedItem();
	void setSelectedItem(int slotNum);
	void drawHotBar();
	void addItem(Item* item);
	int getKeysCount();
	void reset();
};