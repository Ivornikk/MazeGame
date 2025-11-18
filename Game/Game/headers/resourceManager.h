#pragma once

#include <raylib.h>
#include <vector>
#include <utility>
#include <string>

class ResourceManager {

	std::vector<std::pair<int, Model>> npcsModels;
	std::vector <std::pair<int, Model>> itemsModels;

	std::vector<std::pair<std::pair<int, ModelAnimation*>, int*>> npcsAnimations;
	std::vector<std::pair<std::pair<int, ModelAnimation*>, int*>> itemsAnimations;

	int npcsCount;

public:
	ResourceManager();

	void setNpcsCount(int count);

	Model getNpcModel(int id);
	Model getItemModel(int id);
	ModelAnimation* getNpcAnimations(int id);
	ModelAnimation* getItemAnimations(int id);
	int getNpcAnimationsCount(int id);
	int getItemAnimationsCount(int id);

	void loadNpcModel(int id, std::string filePath);
	void loadItemModel(int id, std::string filePath);
	void loadNpcAnimations(int id, std::string filePath, int* animCount);
	void loadItemAnimations(int id, std::string filePath, int* animCount);

	void unloadNpc(int id);
	void unloadItem(int id);
};