#ifndef __ROOK_H__
#define __ROOK_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Rook: public Piece {
    protected:
        bool hasMoved = false;

    public:
        // ctor
        Rook(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

