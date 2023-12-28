#include <iostream>
#include <sstream>
#include "empty.h"

Empty::Empty(int row, int col, std::vector<std::vector<Piece *>> &board): Piece('e', 'e', row, col, board) {}

// empty pieces cannot move
bool Empty::canMove(int endRow, int endCol) const { return false; }

