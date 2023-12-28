#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <string>
#include <vector>
#include "game.h"
#include "player.h"


class Player;

class Computer : public Player {
    protected:
        int level;
        std::vector<std::vector<Piece *>> &board;

        // private moves based on level
        void levelOneMove(Game &g);
        void levelTwoMove(Game &g);
        void levelThreeMove(Game &g);
        void levelFourMove(Game &g);

    public:
        // ctor
        Computer(char colour, float score, bool computer, int level, std::vector<std::vector<Piece *>> &board);
        void bestMove(Game &g) override;
};

#endif

