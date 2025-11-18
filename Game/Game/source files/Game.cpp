#include "../headers/Game.h"

Game::Game() {
	rm = new ResourceManager();
	srand(time(0));
	maze = new Maze();
	maze->generateTree();
	scene = new Scene(maze->getArray(), maze->getWidth(), maze->getHeight(), rm);

	miniMap = new MiniMap(maze->getArray(), maze->getWidth(), maze->getHeight(),
		maze->getFinishCell().x, maze->getFinishCell().y);

	gameState = MAIN_MENU;
	gui = new GUI();
	player = new Player(rm);
}

void Game::Display() {

	SetTargetFPS(60);

	while (!WindowShouldClose() && gameState != GAME_EXIT) {
		ClearBackground(BLACK);

		Update();
		BeginDrawing();

		Draw();

		EndDrawing();
	}
	CloseWindow();
}

void Game::resetGame() {
	if (!isGameReset) {
		player->resetHealth();
		player->resetInventory();
		maze->generateTree();
		scene->reset();
		isGameReset = true;
		EnableCursor();
	}
}

void Game::Draw() {
	switch (gameState) {

	case MAIN_MENU:
		gui->Draw(&gameState);
		break;

	case GAME_START:
		scene->Display(player, &gameState);
		player->Display(scene->getCamera());
		miniMap->Draw();
		gui->drawHealthBar(player->getHealth(), player->getMaxHealth());
		break;
	case GAME_PAUSE:
		scene->Display(player, &gameState);
		miniMap->Draw();
		gui->drawHealthBar(player->getHealth(), player->getMaxHealth());
		gui->drawPauseMenu();
		break;
	case CONTROLS_MENU:
		gui->Draw(&gameState);
	case GAME_OVER:
		gui->Draw(&gameState);
		break;
	case GAME_WON:
		gui->Draw(&gameState);
		break;
	}
}

void Game::handlePlayerDeath() {
	if (player->getHealth() <= 0) {
		gameState = GAME_OVER;
		EnableCursor();
	}
}

void Game::Update() {
	switch (gameState) {
	case MAIN_MENU:
		gui->Update(&gameState);
		break;

	case GAME_START:
		isGameReset = false;
		miniMap->setPlayerPos(scene->getPlayerMazePosition());
		miniMap->setViewAngle(scene->getCameraTarget(), scene->getCameraPos());
		handlePlayerDeath();
		break;
	case GAME_PAUSE:
		gui->Update(&gameState);
		if (gameState == MAIN_MENU)
			resetGame();
		break;
	case CONTROLS_MENU:
		gui->Update(&gameState);
		break;
	case GAME_OVER:
		gui->Update(&gameState);
		resetGame();
		break;
	case GAME_WON:
		gui->Update(&gameState);
		resetGame();
		break;
	}
}