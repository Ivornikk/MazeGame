#include "../headers/resourceManager.h"

ResourceManager::ResourceManager() {
	npcsAnimations = {};
	itemsAnimations = {};

	npcsModels = {};
	itemsModels = {};

	npcsCount = 0;
}

void ResourceManager::setNpcsCount(int count) {
	this->npcsCount = count;
}

Texture2D ResourceManager::getItemIcon(int id) {
	for (auto icon : itemsHotBarIcons)
		if (icon.first == id)
			return icon.second;
	return {};
}

Model ResourceManager::getNpcModel(int id) {
	for (std::pair<int, Model> model : npcsModels) {
		if (model.first == id)
			return model.second;
	}
	return {};
}

Model ResourceManager::getItemModel(int id) {
	for (std::pair<int, Model> model : itemsModels) {
		if (model.first == id)
			return model.second;
	}
	return {};
}

ModelAnimation* ResourceManager::getNpcAnimations(int id) {
	for (std::pair<std::pair<int, ModelAnimation*>, int*> animation : npcsAnimations) {
		if (animation.first.first == id)
			return animation.first.second;
	}
	return nullptr;
}

ModelAnimation* ResourceManager::getItemAnimations(int id) {
	for (std::pair<std::pair<int, ModelAnimation*>, int*> animation : itemsAnimations) {
		if (animation.first.first == id)
			return animation.first.second;
	}
	return nullptr;
}

int ResourceManager::getNpcAnimationsCount(int id) {
	for (int i = 0; i < npcsAnimations.size(); i++) {
		if (npcsAnimations[i].first.first == id)
			return *npcsAnimations[i].second;
	}
}

int ResourceManager::getItemAnimationsCount(int id) {
	for (int i = 0; i < itemsAnimations.size(); i++) {
		if (itemsAnimations[i].first.first == id)
			return *itemsAnimations[i].second;
	}
}

void ResourceManager::loadItemIcon(int id, std::string filepath) {
	Image img = LoadImage(filepath.c_str());
	ImageResize(&img, 100, 100);
	Texture2D tex = LoadTextureFromImage(img);
	UnloadImage(img);
	itemsHotBarIcons.push_back({ id, tex });
}

void ResourceManager::loadNpcModel(int id, std::string filePath) {
	bool flag = true;
	for (int i = 0; i < npcsModels.size(); i++) {
		auto model = npcsModels[i];
		if (model.first == id) {
			flag = false;
			break;
		}
	}
	if (flag) {
		Model model = LoadModel(filePath.c_str());
		npcsModels.push_back({ id, model });
	}
}

void ResourceManager::loadItemModel(int id, std::string filePath) {
	itemsModels.push_back({ id, LoadModel(filePath.c_str()) });
}

void ResourceManager::loadNpcAnimations(int id, std::string filePath, int* animCount) {
	bool flag = true;
	for (int i = 0; i < npcsAnimations.size(); i++) {
		auto animation = npcsAnimations[i];
		if (animation.first.first == id) {
			flag = false;
			break;
		}
	}
	if (flag)
		npcsAnimations.push_back({
			{ id, LoadModelAnimations(filePath.c_str(), animCount)},
				animCount
			});
}

void ResourceManager::loadItemAnimations(int id, std::string filePath, int* animCount) {
	itemsAnimations.push_back({
		{ id, LoadModelAnimations(filePath.c_str(), animCount)},
			animCount
		});
}

void ResourceManager::unloadNpc(int id) {
	if (npcsCount <= 1) {
		for (int i = 0; i < npcsModels.size(); i++) {
			if (npcsModels[i].first == id) {
				UnloadModel(npcsModels[i].second);
				npcsModels.erase(npcsModels.begin() + i);
				break;
			}
		}
		for (int i = 0; i < npcsAnimations.size(); i++) {
			if (npcsAnimations[i].first.first == id) {
				UnloadModelAnimations(npcsAnimations[i].first.second, *npcsAnimations[i].second);
				npcsAnimations.erase(npcsAnimations.begin() + i);
				break;
			}
		}
	}
}

void ResourceManager::unloadItem(int id) {
	for (auto icon: itemsHotBarIcons)
		if (icon.first == id) {
			UnloadTexture(icon.second);
		}
	for (std::pair<int, Model> model : itemsModels) {
		if (model.first == id) {
			UnloadModel(model.second);
			break;
		}
	}
	for (std::pair<std::pair<int, ModelAnimation*>, int*> animation : itemsAnimations) {
		if (animation.first.first == id) {
			UnloadModelAnimations(animation.first.second, *animation.second);
			break;
		}
	}
}
