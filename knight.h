#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Knight: public Piece {
    public:
        // ctor
        Knight(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

