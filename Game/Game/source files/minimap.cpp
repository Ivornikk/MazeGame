#include "../headers/minimap.h"

MiniMap::MiniMap(int** mazeTemp, int widthTemp, int heightTemp,
	 int finishXTemp, int finishYTemp) {
	mazeArr = mazeTemp;
	width = widthTemp;
	height = heightTemp;
	finishCellX = finishXTemp;
	finishCellY = finishYTemp;
	PlayerPos = { 1.f, 1.f };
	Image arrowImage = LoadImage("images/arrow.png");
	ImageResize(&arrowImage, 10, 10);
	playerArrow = LoadTextureFromImage(arrowImage);
	viewAngle = 0.f;
}

void MiniMap::Draw() {
	DrawRectangle(0, 0, 10 * width, 10 * height, BLACK);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == finishCellY && j == finishCellX)
				DrawRectangle(10 * j, 10 * i, 10, 10, GREEN);
			else if (mazeArr[i][j] == 0)
				DrawRectangle(10 * j, 10 * i, 10, 10, BLUE);
			else if (mazeArr[i][j] == 2)
				DrawRectangle(10 * j, 10 * i, 10, 10, PINK);
			if (i == ceil(PlayerPos.y) && j == ceil(PlayerPos.x)) {
				Rectangle source = {
					0, 0, (float)playerArrow.width, (float)playerArrow.height
				};
				Rectangle dest = {playerArrow.width * j + (playerArrow.width/2), (playerArrow.height * i) + (playerArrow.height/2), playerArrow.width, playerArrow.height};
				Vector2 origin = {dest.width / 2.f, dest.height / 2.f};

				DrawTexturePro(playerArrow, source, dest, origin, viewAngle, WHITE);
			}
		}
	}
}

void MiniMap::setPlayerPos(Vector2 pos) {
	PlayerPos = pos;
}

void MiniMap::setViewAngle(Vector3 cameraTarget, Vector3 cameraPosition) {
	Vector3 forward = Vector3Subtract(cameraTarget, cameraPosition);
	float angle = atan2(forward.x, forward.z);
	viewAngle = -angle * RAD2DEG + 90.f;
}

