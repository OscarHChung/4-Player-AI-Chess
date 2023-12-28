#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"

class Piece;

class TextDisplay {
    std::vector<std::vector<char>> td; // the actual text display
    const int boardSize = 8; // size of the chess board
public:
    TextDisplay();
    void tdNotify(char colour, char pieceLetter, int row, int col); // updates the text display of the chess board
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
