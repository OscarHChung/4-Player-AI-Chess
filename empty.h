#ifndef __EMPTY_H__
#define __EMPTY_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class Empty: public Piece {
    public:
        // ctor
        Empty(int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

