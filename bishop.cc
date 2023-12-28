#include <iostream>
#include <sstream>
#include "bishop.h"

Bishop::Bishop(char colour, int row, int col, std::vector<std::vector<Piece *>> &board): Piece('b', colour, row, col, board) {}

bool Bishop::canMove(int endRow, int endCol) const {
    // (endRow and endCol are automatically valid positions on board due to check in main.cc)
    // (check for moving causing check or checkmate in game.cc)
    // ensure not remaining in same position
    if (row == endRow && col == endCol) {
        return false;
    }
    // ensure new position doesn't contain an allied piece
    if (board[endRow][endCol]->getColour() == getColour()) {
        return false;
    }
    
    // set distances + directions
    int rowDistance = endRow - row;
    int colDistance = endCol - col;
    int rowDirection = 1;
    int colDirection = 1;
    if (rowDistance < 0) {
        rowDirection = -1;
    }
    if (colDistance < 0) {
        colDirection = -1;
    }

    // ensure diagonal movement
    if (abs(rowDistance) != abs(colDistance)) {
        return false;
    }

    // ensure clear path
    for (int i = 1; i < abs(rowDistance); ++i) {
        if (board[row + i*rowDirection][col + i*colDirection]->getType() != 'e') {
            return false;
        }
    }

    // else the new position must be valid since it passes everythings
    return true;
}

