#ifndef __PAWN_H__
#define __PAWN_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Pawn: public Piece {
    protected:
        bool hasMoved = false;

    public:
        // ctor
        Pawn(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

