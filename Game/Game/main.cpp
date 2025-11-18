#include "./headers/Game.h"

int main() {
	InitWindow(1920, 1040, "Maze game");	
	Game* game = new Game();
	game->Display();
}