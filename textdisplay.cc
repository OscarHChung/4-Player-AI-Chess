#include "textdisplay.h"
#include <iostream>
#include <string>

using namespace std;

// constructor
TextDisplay::TextDisplay() {
    for (int i = 0; i < boardSize; i++) {
        vector<char> row;
        for (int j = 0; j < boardSize; j++) {
            row.emplace_back('_');
        }
        td.emplace_back(row);
    }
}

// destructor
TextDisplay::~TextDisplay() {}

// updates the text display of the chess board
void TextDisplay::tdNotify(char colour, char pieceLetter, int row, int col) {
    if (colour == 'w') {
        td[row][col] = pieceLetter - 32;
    }
    else if (colour == 'b') {
        td[row][col] = pieceLetter;
    }
    else { // if empty
        td[row][col] = '_';
    }
}

// displays the chess board
ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int rownum = 8;
    for (int row = 0; row < td.boardSize; row++) {
        cout << rownum << " "; // prints the row number
        rownum--;
        for (int col = 0; col < td.boardSize; col++) {
            if (col == td.boardSize - 1) {
                out << td.td[row][col] << endl;
            }
            else {
                out << td.td[row][col];
            }
        }
    }
    cout << endl;
    cout << "  abcdefgh" << endl; // prints the column letters
    return out;
}
