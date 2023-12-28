#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>
#include <vector>
using namespace std;

class Piece {
    protected:
        char type;
        char colour;
        int row;
        int col;
        std::vector<std::vector<Piece *>> &board;
        bool hasMoved;

    public:
        // creating an empty piece
        Piece(int row, int col, std::vector<std::vector<Piece *>> &board);

        // creating a non-empty piece
        Piece(char type, char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // get fields
        char getType() const;
        char getColour() const;
        int getRow() const;
        int getCol() const;

        // set fields
        void setRow(int newRow);
        void setCol(int newCol);

        // Rook, King, Pawn functions
        bool hasMovedFunc() const;
        void moved();

        // virtuals
        virtual bool canMove(int endRow, int endCol) const = 0;
        virtual ~Piece();
};

#endif

