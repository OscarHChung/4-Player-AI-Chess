#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Queen: public Piece {
    public:
        // ctor
        Queen(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

