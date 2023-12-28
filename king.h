#ifndef __KING_H__
#define __KING_H__
#include <string>
#include <vector>
#include "piece.h"
using namespace std;

class King: public Piece {
    protected:
        bool hasMoved = false;

    public:
        // ctor
        King(char colour, int row, int col, std::vector<std::vector<Piece *>> &board);

        // override
        bool canMove(int endRow, int endCol) const override;
};

#endif

