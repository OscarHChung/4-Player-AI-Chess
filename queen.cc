#include <iostream>
#include <sstream>
#include "queen.h"

Queen::Queen(char colour, int row, int col, std::vector<std::vector<Piece *>> &board): Piece('q', colour, row, col, board) {}

bool Queen::canMove(int endRow, int endCol) const {
    // ensure not remaining in same position
    if (row == endRow && col == endCol) {
        return false;
    }
    // ensure new position doesn't contain an allied piece
    if (board[endRow][endCol]->getColour() == getColour()) {
        return false;
    }
    
    // moving vertically
    if (col == endCol) {
        // set distances + directions
        int rowDistance = endRow - row;
        int rowDirection = 1;
        if (rowDistance < 0) {
            rowDirection = -1;
        }

        // ensure clear path
        for (int i = 1; i < abs(rowDistance); ++i) {
            if (board[row + i*rowDirection][col]->getType() != 'e') {
                return false;
            }
        }

        return true;
    }

    // moving horizontally
    if (row == endRow) {
        // set distances + directions
        int colDistance = endCol - col;
        int colDirection = 1;
        if (colDistance < 0) {
            colDirection = -1;
        }

        // ensure clear path
        for (int i = 1; i < abs(colDistance); ++i) {
            if (board[row][col  + i*colDirection]->getType() != 'e') {
                return false;
            }
        }

        return true;
    }

    // moving diagonally
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

    if (abs(rowDistance) == abs(colDistance)) {
        for (int i = 1; i < abs(rowDistance); ++i) {
            if (board[row + i*rowDirection][col + i*colDirection]->getType() != 'e') {
                return false;
            }
        }

        // path is clear
        return true;
    }

    // else the piece doesn't move to a valid spot
    return false;
}

