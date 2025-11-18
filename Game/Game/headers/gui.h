#pragma once

#include "button.h"
#include "window.h"
#include "../utils.h"

class GUI {
	
	Window mainMenu = Window(0.f,0.f,"Main Menu");
	Window controlsMenu = Window(100.f, 100.f, "Controls");
	Window gameOverMenu = Window(100.f, 75.f, "Game Over");
	Window gameWonMenu = Window(100.f, 75.f, "You Won!");

	Window pauseMenu = Window(200.f, 150.f, "Pause");
public:
	GUI(); 
	void Draw(GAME_STATES* state);
	void drawHealthBar(float health, float maxHealth);
	void drawPauseMenu();
	void Update(GAME_STATES* state);

};

