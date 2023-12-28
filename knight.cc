#include <iostream>
#include <sstream>
#include "knight.h"

Knight::Knight(char colour, int row, int col, std::vector<std::vector<Piece *>> &board): Piece('n', colour, row, col, board) {}

bool Knight::canMove(int endRow, int endCol) const {
    // ensure not remaining in same position
    if (row == endRow && col == endCol) {
        return false;
    }
    // ensure new position doesn't contain an allied piece
    if (board[endRow][endCol]->getColour() == getColour()) {
        return false;
    }
    
    // set distances
    int rowDistance = abs(endRow - row);
    int colDistance = abs(endCol - col);

    // ensure correct movement pattern
    if ((rowDistance == 2 && colDistance == 1) ||
        (rowDistance == 1 && colDistance == 2)) {
        return true;
    }

    // else incorrect movement pattern
    return false;
}

