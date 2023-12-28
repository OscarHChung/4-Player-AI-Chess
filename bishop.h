#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Bishop: public Piece {
    public:
        // ctor
        Bishop(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

