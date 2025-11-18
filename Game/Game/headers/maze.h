#pragma once

#include <vector>
#include <cmath>

struct Cell {
	int x;
	int y;
};

class Maze {
	int** maze;
	int width, height;

	std::vector<Cell> emptyCells;
	int emptyCellsNum;
	Cell finishCell;

public:
	Maze(int x=30, int y=30);
	int checkCell(int x, int y);
	void prepareMaze();
	bool testCell(int x, int y);
	void generateTree();
	void testForDeadEnd( int cellNum);
	void testIfNearFinish(int cellNum);
	int getWidth();
	int getHeight();
	int** getArray();
	Cell getFinishCell();
};