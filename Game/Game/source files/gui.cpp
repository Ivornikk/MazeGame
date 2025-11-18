#include "../headers/gui.h"

GUI::GUI() {
	mainMenu.addButton(CENTER, 0, 300, 100, "Start", GAME_START, WHITE, WHITE, "images/button.png");
	mainMenu.addButton(CENTER, 10, 300, 100, "Controls", CONTROLS_MENU, WHITE, WHITE, "images/button.png");
	mainMenu.addButton(TOP_RIGHT, 0, 100, 100, "", GAME_EXIT, WHITE, WHITE, "images/ExitButton.png");
	mainMenu.setBackgroundImage("images/mainMenuBackground.png");
	
	controlsMenu.addButton(BOTTOM, 5, 150, 50, "Back", MAIN_MENU, WHITE, WHITE, "images/button.png");

	gameOverMenu.addButton(CENTER, 10, 200, 75, "Main Menu", MAIN_MENU, WHITE, WHITE, "images/button.png");
	gameOverMenu.addButton(CENTER, 10, 200, 75, "Restart", GAME_START, WHITE, WHITE, "images/button.png");
	gameOverMenu.setBackgroundImage("images/menuBackground.png");

	pauseMenu.addButton(CENTER, 0, 300, 100, "Resume", GAME_START, WHITE, WHITE, "images/button.png");
	pauseMenu.addButton(CENTER, 5, 300, 100, "Controls", CONTROLS_MENU, WHITE, WHITE, "images/button.png");
	pauseMenu.addButton(CENTER, 10, 300, 100, "Main Menu", MAIN_MENU, WHITE, WHITE, "images/button.png");
	pauseMenu.setBackgroundImage("images/menuBackground.png");

	gameWonMenu.addButton(CENTER, 10, 200, 75, "Main Menu", MAIN_MENU, WHITE, WHITE, "images/button.png");
	gameWonMenu.addButton(CENTER, 10, 200, 75, "Restart", GAME_START, WHITE, WHITE, "images/button.png");
	gameWonMenu.setBackgroundImage("images/menuBackground.png");
}

void GUI::Draw(GAME_STATES* state) {
	switch (*state) {
	case MAIN_MENU:
		mainMenu.Draw();
		break;
	case GAME_OVER:
		gameOverMenu.Draw();
		break;
	case GAME_WON:
		gameWonMenu.Draw();
		break;
	case CONTROLS_MENU:
		controlsMenu.Draw();

		DrawText("W  - Move Forward", 150, 200, 30, WHITE);
		DrawText("S  - Move Backward", 150, 250, 30, WHITE);
		DrawText("A  - Turn Left", 150, 300, 30, WHITE);
		DrawText("D  - Turn Right", 150, 350, 30, WHITE);

		static Texture2D escKey = { 0 };
		if (escKey.id == 0) {
			escKey = LoadTexture("images/ExitButton.png");
		}

		int escX = 150;
		int escY = 400;
		DrawTexture(escKey, escX, escY, WHITE);
		DrawText(" - Pause Game", escX + escKey.width + 20, escY + escKey.height / 4, 30, WHITE);
		
		static Texture2D mouseIcon = { 0 };
		if (mouseIcon.id == 0) {
			mouseIcon = LoadTexture("images/left_mouse.png"); 
		}

		int mouseX = 150;
		int mouseY = escY + escKey.height + 50; 
		DrawTextureEx(mouseIcon, { (float)mouseX, (float)mouseY }, 0.0f, 0.04f, WHITE);
		DrawText(" - Left Click to Attack", escX + escKey.width + 20, mouseY + escKey.height / 4, 30, WHITE);
		break;
	}
}

void GUI::drawHealthBar(float health, float maxHealth) {
	float healthPercentage = health / (maxHealth / 100.f);
	float width = 300.f * healthPercentage / 100.f;
	Rectangle healthBar = { GetScreenWidth() - 310.f, 10.f, width, 40.f };

	DrawRectangleRec(healthBar, GREEN);
	DrawRectangleLinesEx({ healthBar.x, healthBar.y, 300.f, healthBar.height }, 3.f, DARKGRAY);
}

void GUI::drawPauseMenu() {
	pauseMenu.Draw();
}
	
void GUI::Update(GAME_STATES* state) {
	switch (*state) {
	case MAIN_MENU:
		mainMenu.Update(state);
		break;
	case GAME_PAUSE:
		pauseMenu.Update(state);
		break;
	case CONTROLS_MENU:
		controlsMenu.Update(state);
		break;
	case GAME_OVER:
		gameOverMenu.Update(state);
		break;
	case GAME_WON:
		gameWonMenu.Update(state);
		break;
	}
}