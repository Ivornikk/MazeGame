#pragma once

#include <raylib.h>
#include <vector>
#include <utility>
#include <string>

class ResourceManager {

	std::vector<std::pair<int, Model>> npcsModels;
	std::vector <std::pair<int, Model>> itemsModels;
	std::vector<std::pair<int, Texture2D>> itemsHotBarIcons;

	std::vector<std::pair<std::pair<int, ModelAnimation*>, int*>> npcsAnimations;
	std::vector<std::pair<std::pair<int, ModelAnimation*>, int*>> itemsAnimations;

	int npcsCount;

public:
	ResourceManager();

	void setNpcsCount(int count);

	Texture2D getItemIcon(int id);

	Model getNpcModel(int id);
	Model getItemModel(int id);
	ModelAnimation* getNpcAnimations(int id);
	ModelAnimation* getItemAnimations(int id);
	int getNpcAnimationsCount(int id);
	int getItemAnimationsCount(int id);

	void loadItemIcon(int id, std::string filepath);
	void loadNpcModel(int id, std::string filePath);
	void loadItemModel(int id, std::string filePath);
	void loadNpcAnimations(int id, std::string filePath, int* animCount);
	void loadItemAnimations(int id, std::string filePath, int* animCount);

	void unloadNpc(int id);
	void unloadItem(int id);
};