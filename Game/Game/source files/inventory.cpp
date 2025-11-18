#include "../headers/inventory.h"

Inventory::Inventory(ResourceManager* resourceManager) {
	rm = resourceManager;
	items.push_back(new Sword(rm, { 0.f,0.f,0.f }));
	items.push_back(new Mace(rm, { 0.f,0.f,0.f }));
	items.push_back(new CrystalSword(rm, { 0.f,0.f,0.f }));

	for (int i = 0; i < items.size(); i++)
		items[i]->setState(EQUIPPED);

	selectedItem = items[0];
	selectedSlot = 1;
}

Item* Inventory::getSelectedItem() {
	return selectedItem;
}

void Inventory::setSelectedItem(int slotNum) {
	if (slotNum <= items.size()) {
		selectedItem = items[slotNum - 1];
		selectedSlot = slotNum;
	}
}

void Inventory::drawHotBar() {
	for (int i = 0; i < maxSlots; i++)
		DrawRectangle(GetScreenWidth() / 2 - (maxSlots * 100 / 2) + i * 100, GetScreenHeight() - 100, 100, 100, { 0,0,0,125 });

	for (int i = 0; i < items.size(); i++) {
		Item* item = items[i];
		if (i == selectedSlot - 1) {
			DrawRectangle(GetScreenWidth() / 2 - (maxSlots * 100 / 2) + i * 100, GetScreenHeight() - 100, 100, 100, { 0,0,0,255 });
		}
		DrawTexture(item->getHotBarIcon(), GetScreenWidth() / 2 - (maxSlots * 100 / 2) + i * 100, GetScreenHeight() - 100, WHITE);
	}

	for (int i = 0; i < maxSlots; i++)
		DrawText(std::to_string(i + 1).c_str(), GetScreenWidth() / 2 - (maxSlots * 100 / 2) + i * 100, GetScreenHeight() - 100, 15, WHITE);
}

void Inventory::addItem(Item* item) {
	item->setState(EQUIPPED);
	items.push_back(item);
}

int Inventory::getKeysCount() {
	int counter = 0;
	for (int i = 0; i < items.size(); i++)
		if (items[i]->getId() == 1) counter++;
	return counter;
}

// Resets keys
void Inventory::reset() {
	for (int i = 0; i < items.size(); i++) {
		// The key item's id is 1
		if (items[i]->getId() == 1)
			items.erase(items.begin() + i);
	}
	for (int i = items.size()-1; i >= 0; i--) {
		if (items[i]->getId() == 1)
			items.erase(items.begin() + i);
	}
}
