#include "../headers/maze.h"
#include <cmath>

Maze::Maze(int x, int y) {
	width = x;
	height = y;
	maze = new int* [y];
	for (int i = 0; i < y; i++)
		maze[i] = new int[x];
	finishCell.x = width - 2;
	finishCell.y = height - 2;
}

int Maze::checkCell(int x, int y) {
	return maze[y][x];
}

void Maze::prepareMaze() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			maze[i][j] = 0;
		}
	}
	emptyCellsNum = 1;
	maze[1][1] = 1;
	emptyCells.clear();
	emptyCells.push_back({ 1, 1 });
}

// Returns true if the cell can break and false if it can't.
// The conditions are the following:
// 
// 1. The cell has to be inside of the maze's boundaries to break.
// 2. It must not already be cleared.
// 3. It must not connect too many open cells around it (3 or more).
bool Maze::testCell(int x, int y) {
	if (x == finishCell.x && y == finishCell.y) return true;
	else if (x < 1 || y < 1 || x > finishCell.x || y > finishCell.y || maze[y][x] == 1) return false;
	else if (maze[y - 1][x - 1] + maze[y - 1][x] + maze[y][x - 1] >= 3) return false;
	else if (maze[y - 1][x + 1] + maze[y - 1][x] + maze[y][x + 1] >= 3) return false;
	else if (maze[y + 1][x - 1] + maze[y + 1][x] + maze[y][x - 1] >= 3) return false;
	else if (maze[y + 1][x + 1] + maze[y + 1][x] + maze[y][x + 1] >= 3) return false;
	else return true;
}

// Algorithm that choses random empty cell and breaks its way in a random direction
void Maze::generateTree() {
	prepareMaze();

	while (maze[finishCell.y][finishCell.x] != 1) {
		int randomEmptyCellNum = rand() % emptyCellsNum;

		// Random direction of breaking a cell: 
		// 0 = Up, 1 = Right, 2 = Down, 3 = Left
		switch (rand() % 4) {
		case 0:
			if (testCell(emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y - 1) &&
				maze[emptyCells[randomEmptyCellNum].y - 2][emptyCells[randomEmptyCellNum].x] != 1) {
				maze[emptyCells[randomEmptyCellNum].y - 1][emptyCells[randomEmptyCellNum].x] = 1;
				if (testCell(emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y - 2)) {
					maze[emptyCells[randomEmptyCellNum].y - 2][emptyCells[randomEmptyCellNum].x] = 1;
					emptyCells.push_back({ emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y - 2 });
					emptyCellsNum++; 
				}
			}
			break;
		case 1:
			if (testCell(emptyCells[randomEmptyCellNum].x + 1, emptyCells[randomEmptyCellNum].y) &&
				maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x + 2] != 1) {
				maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x + 1] = 1;
				if (testCell(emptyCells[randomEmptyCellNum].x + 2, emptyCells[randomEmptyCellNum].y)) {
					maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x + 2] = 1;
					emptyCells.push_back({ emptyCells[randomEmptyCellNum].x + 2, emptyCells[randomEmptyCellNum].y });
					emptyCellsNum++;
				}
			}
			break;
		case 2:
			if (testCell(emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y + 1) &&
				maze[emptyCells[randomEmptyCellNum].y + 2][emptyCells[randomEmptyCellNum].x] != 1) {
				maze[emptyCells[randomEmptyCellNum].y + 1][emptyCells[randomEmptyCellNum].x] = 1;
				if (testCell(emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y + 2)) {
					maze[emptyCells[randomEmptyCellNum].y + 2][emptyCells[randomEmptyCellNum].x] = 1;
					emptyCells.push_back({ emptyCells[randomEmptyCellNum].x, emptyCells[randomEmptyCellNum].y + 2 });
					emptyCellsNum++;
				}
			}
			break;
		case 3:
			if (testCell(emptyCells[randomEmptyCellNum].x - 1, emptyCells[randomEmptyCellNum].y) &&
				maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x - 2] != 1) {
				maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x - 1] = 1;
				if (testCell(emptyCells[randomEmptyCellNum].x - 2, emptyCells[randomEmptyCellNum].y)) {
					maze[emptyCells[randomEmptyCellNum].y][emptyCells[randomEmptyCellNum].x - 2] = 1;
					emptyCells.push_back({ emptyCells[randomEmptyCellNum].x - 2, emptyCells[randomEmptyCellNum].y });
					emptyCellsNum++;
				}
			}
			break;
		}

		testForDeadEnd(randomEmptyCellNum);
	}
}

// If an empty cell is a dead end then it is removed from the vector of empty cells to optimize generation time.
// This way the number of cell that can be chosen is less which leads to faster generation.
void Maze::testForDeadEnd(int cellNum) {
	if (!testCell(emptyCells[cellNum].x, emptyCells[cellNum].y - 2) &&
		!testCell(emptyCells[cellNum].x, emptyCells[cellNum].y + 2) &&
		!testCell(emptyCells[cellNum].x - 2, emptyCells[cellNum].y) &&
		!testCell(emptyCells[cellNum].x + 2, emptyCells[cellNum].y)) {
		testIfNearFinish(cellNum);
		if (emptyCellsNum > 1) {
			emptyCells.erase(emptyCells.begin() + cellNum);
			emptyCellsNum--;
		}
	}
}
// If the maze has size of an odd number then the exit won't always be found automatically.
// Because of this it is cleared manually.
void Maze::testIfNearFinish(int cellNum) {
	if (abs(emptyCells[cellNum].y - finishCell.y) <= 2 && abs(emptyCells[cellNum].x - finishCell.x) <= 2) {
		for (int i = finishCell.y - 1; i <= finishCell.y; i++) {
			for (int j = finishCell.x - 1; j <= finishCell.x; j++) {
				maze[i][j] = 1;
			}
		}
	}
}

int Maze::getWidth() {
	return width;
}

int Maze::getHeight() {
	return height;
}

int** Maze::getArray() {
	return maze;
}

Cell Maze::getFinishCell() {
	return finishCell;
}
