#include <iostream>
#include <sstream>
#include "pawn.h"

Pawn::Pawn(char colour, int row, int col, std::vector<std::vector<Piece *>> &board): Piece('p', colour, row, col, board) {}

bool Pawn::canMove(int endRow, int endCol) const {
    // ensure not remaining in same position
    if (row == endRow && col == endCol) {
        return false;
    }
    // ensure new position doesn't contain an allied piece
    if (board[endRow][endCol]->getColour() == getColour()) {
        return false;
    }

    // account for going up or down bc of colour
    int direction;
    if (getColour() == 'w') {
        direction = -1;
    }
    else {
        direction = 1;
    }

    // normal move 1
    if (row + direction == endRow && col == endCol && (board[row + direction][col]->getType() == 'e')) {
        return true;
    }
    // ADVANCED MOVE: INITIAL MOVE 2
    if (row + direction*2 == endRow && col == endCol && !hasMovedFunc()) {
        if ((board[row + direction][col]->getType() == 'e') &&
            (board[row + direction*2][col]->getType() == 'e')) {
            return true;
        }
    }
    // CAPTURE: DIAGONAL ATTACK
    if (row + direction == endRow && abs(endCol - col) == 1) {
        // check for enemy in end position
        if (board[endRow][endCol]->getType() != 'e') {
            return true;
        }
    }

     // ADVANCED MOVE: EN PASSANT --> This code block only defines the move. Game.cc checks if the move is actually available. 

    // White pawn en passanting black pawn
    if (row + direction == endRow && endRow == 2 && colour == 'w' && abs(endCol - col) == 1 && board[endRow][endCol]->getType() == 'e') {
            if (board[3][endCol]->getType() == 'p' && board[3][endCol]->getColour() == 'b') return true;
    }
    // Black pawn en passanting white pawn
    if (row + direction == endRow && endRow == 5 && colour == 'b' && abs(endCol - col) == 1 && board[endRow][endCol]->getType() == 'e') {
            if (board[4][endCol]->getType() == 'p' && board[4][endCol]->getColour() == 'w') return true;
    }
    
    
    // else the new position must be invalid for this specific piece
    return false;
}

