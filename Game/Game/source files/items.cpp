#include "../headers/items.h"

Key::Key(ResourceManager* resourceManager, Vector3 defPos) : Item(resourceManager, defPos, 5, 3) {
	id = 1;
	type = ITEM;
	rm = resourceManager;
	rm->loadItemModel(id, "models/glb/key.glb");
	rm->loadItemAnimations(id, "models/glb/key.glb", &animationsCount);
	model = rm->getItemModel(id);
	animationsCount = rm->getItemAnimationsCount(id);
	animations = rm->getItemAnimations(id);
	model.transform = MatrixMultiply(model.transform, MatrixRotateY(90.f * DEG2RAD));
	model.transform = MatrixMultiply(model.transform, MatrixTranslate(-0.2f, -1.f, 0.8f));
	Image hotBarImage = LoadImage("images/key.png");
	ImageResize(&hotBarImage, 100, 100);
	hotBarIcon = LoadTextureFromImage(hotBarImage);
	UnloadImage(hotBarImage);
}

Sword::Sword(ResourceManager* resourceManager, Vector3 defPos) : Item(resourceManager, defPos, 30, 2) {
	id = 2;
	type = WEAPON;
	rm = resourceManager;
	rm->loadItemModel(id, "models/glb/sword.m3d");
	rm->loadItemAnimations(id, "models/glb/sword.m3d", &animationsCount);
	model = rm->getItemModel(id);
	animationsCount = rm->getItemAnimationsCount(id);
	animations = rm->getItemAnimations(id);
	model.transform = MatrixMultiply(model.transform, MatrixRotateY(-90.f * DEG2RAD));
	model.transform = MatrixMultiply(model.transform, MatrixTranslate(-0.4f, -0.5f, -0.6f));
	Image hotBarImage = LoadImage("images/sword.png");
	ImageResize(&hotBarImage, 100, 100);
	hotBarIcon = LoadTextureFromImage(hotBarImage);
	UnloadImage(hotBarImage);
}

Mace::Mace(ResourceManager* resourceManager, Vector3 defPos) : Item(resourceManager, defPos, 50, 3) {
	id = 3;
	type = WEAPON;
	rm = resourceManager;
	rm->loadItemModel(id, "models/glb/mace.glb");
	rm->loadItemAnimations(id, "models/glb/mace.glb", &animationsCount);
	model = rm->getItemModel(id);
	animationsCount = rm->getItemAnimationsCount(id);
	animations = rm->getItemAnimations(id);
	model.transform = MatrixMultiply(model.transform, MatrixScale(0.8, 0.8, 0.8));
	model.transform = MatrixMultiply(model.transform, MatrixRotateY(90.f * DEG2RAD));
	model.transform = MatrixMultiply(model.transform, MatrixTranslate(0, -1, -0.5f));
	Image hotBarImage = LoadImage("images/mace.png");
	ImageResize(&hotBarImage, 100, 100);
	hotBarIcon = LoadTextureFromImage(hotBarImage);
	UnloadImage(hotBarImage);
}

CrystalSword::CrystalSword(ResourceManager* resourceManager, Vector3 defPos) : Item(resourceManager, defPos, 75, 4) {
	id = 4;
	type = WEAPON;
	rm = resourceManager;
	rm->loadItemModel(id, "models/glb/crystalSword.glb");
	rm->loadItemAnimations(id, "models/glb/crystalSword.glb", &animationsCount);
	model = rm->getItemModel(id);
	animationsCount = rm->getItemAnimationsCount(id);
	animations = rm->getItemAnimations(id);
	model.transform = MatrixMultiply(model.transform, MatrixScale(0.3, 0.3, 0.3));
	model.transform = MatrixMultiply(model.transform, MatrixRotateY(-90.f * DEG2RAD));
	model.transform = MatrixMultiply(model.transform, MatrixTranslate(0, -1, -0.5f));
	Image hotBarImage = LoadImage("images/crystalSword.png");
	ImageResize(&hotBarImage, 100, 100);
	hotBarIcon = LoadTextureFromImage(hotBarImage);
	UnloadImage(hotBarImage);
}