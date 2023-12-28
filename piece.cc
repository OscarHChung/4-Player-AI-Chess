#include <iostream>
#include <sstream>
#include "piece.h"

Piece::Piece(int row, int col, std::vector<std::vector<Piece *>> &board): row{row}, col{col}, board{board} {
    type = 'e';
    colour = 'e';
    hasMoved = false;
}

Piece::Piece(char type, char colour, int row, int col, std::vector<std::vector<Piece *>> &board): type{type}, colour{colour}, row{row}, col{col}, board{board} {
    hasMoved = false;
}

char Piece::getType() const {
    return type;
}

char Piece::getColour() const {
    return colour;
}

int Piece::getRow() const {
    return row;
}

int Piece::getCol() const {
    return col;
}

void Piece::setRow(int newRow) {
    row = newRow;
}

void Piece::setCol(int newCol) {
    col = newCol;
}

bool Piece::hasMovedFunc() const {
    return hasMoved;
}

void Piece::moved() {
    hasMoved = true;
}

Piece::~Piece() {}

