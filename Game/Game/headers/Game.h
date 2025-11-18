#pragma once

#include <raylib.h>
#include "maze.h"
#include "minimap.h"
#include "scene.h"
#include "../utils.h"
#include "gui.h"
#include "player.h"
#include "resourceManager.h"

class Game {
	Maze* maze;
	MiniMap* miniMap;
	Scene* scene;
	GUI* gui;
	Player* player;
	GAME_STATES gameState;
	ResourceManager* rm;
	bool isGameReset;
public:
	Game();
	void Display();
	void resetGame();
	// Predicts collisions, updates position of the game character.
	void Update();
	// Shows the updated game content on the screen.
	void Draw();
	void handlePlayerDeath();
};