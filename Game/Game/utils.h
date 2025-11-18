#pragma once
#include "raylib.h"

enum GAME_STATES {
	MAIN_MENU,
	GAME_START,
	GAME_EXIT,
	GAME_PAUSE,
	CONTROLS_MENU,
	GAME_WON,
	GAME_OVER,
};

// Returns the center in the 3d space of a cell from maze array
Vector2 GetCellCenter(Vector2 cell);