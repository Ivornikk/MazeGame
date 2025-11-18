#include "utils.h"

Vector2 GetCellCenter(Vector2 cell) {
	return { cell.x * 2 - 1, cell.y * 2 - 1 };
}
