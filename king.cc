#include <iostream>
#include <sstream>
#include "king.h"

King::King(char colour, int row, int col, std::vector<std::vector<Piece *>> &board): Piece('k', colour, row, col, board) {}

bool King::canMove(int endRow, int endCol) const {
    // ensure not remaining in same position
    if (row == endRow && col == endCol) {
        return false;
    }

    // if new position isn't allied
    if (board[endRow][endCol]->getColour() != getColour()) {
        // ensure only moving 1 square
        if (abs(endRow - row) <= 1 && abs(endCol - col) <= 1) {
            return true;
        }
    }

    // ADVANCED MOVE: CASTLING
    // set distances + directions
    int colDistance = endCol - col;
    int colDirection = 1;
    if (colDistance < 0) {
        colDirection = -1;
    }

    // ensure new position is two tile distance in the same row as the king
    if (endRow == row && abs(colDistance) == 2) {
        // ensure king hasn't moved this game
        if (!hasMovedFunc()) {
            // ensure rook hasn't moved this game
            // left allied rook
            if (colDirection < 0 && board[endRow][0]->hasMovedFunc() == false && board[endRow][0]->getType() == 'r' && board[endRow][0]->getColour() == getColour()) {
                // ensure clear path
                for (int i = 1; i < 4; ++i) {
                    if (board[row][col + i*colDirection]->getType() != 'e') {
                        return false;
                    }
                }

                // path is clear
                return true;
            }
            // right allied rook
            if (colDirection > 0 && board[endRow][7]->hasMovedFunc() == false && board[endRow][7]->getType() == 'r' && board[endRow][7]->getColour() == getColour()) {
                // ensure clear path
                for (int i = 1; i < 3; ++i) {
                    if (board[row][col + i*colDirection]->getType() != 'e') {
                        return false;
                    }
                }

                // path is clear
                return true;
            }
        }
    }

    // else invalid move
    return false;
}

