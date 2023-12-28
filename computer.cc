#include <string>
#include <vector>
#include "computer.h"
#include "player.h"
#include "game.h"


// private methods

void Computer::levelOneMove(Game &g) {
    // generate a completely random legal move
    srand(static_cast<unsigned int>(time(nullptr)));
    string cols = "abcdefgh";

    string randRow1 = std::to_string((rand() % 8) + 1);
    string randCol1 = cols.substr(rand() % 8, 1);
    string randTile1 = randCol1 + randRow1;

    string randRow2 = std::to_string((rand() % 8) + 1);
    string randCol2 = cols.substr(rand() % 8, 1);
    string randTile2 = randCol2 + randRow2;

    while(!g.move(randTile1, randTile2)) {
        randRow1 = std::to_string((rand() % 8) + 1);
        randCol1 = cols.substr(rand() % 8, 1);
        randTile1 = randCol1 + randRow1;

        randRow2 = std::to_string((rand() % 8) + 1);
        randCol2 = cols.substr(rand() % 8, 1);
        randTile2 = randCol2 + randRow2;
    }
}

void Computer::levelTwoMove(Game &g) {
    // get legal moves that are preferred by level 2
    std::vector<std::string> totalMoves = g.generateLegalMovesLevel2(getColour());
    int numTotalMoves = totalMoves.size();

    // do a level 1 move if there are no level 2 moves
    if (numTotalMoves == 0) {
        levelOneMove(g);
    }
    // perform a level 2 move
    else {
        // choose a completely random move from the given selection
        srand(static_cast<unsigned int>(time(nullptr)));
        string chosenMove = totalMoves[rand() % numTotalMoves];

        // convert chosenMove to tiles
        string randTile1 = chosenMove.substr(0, 2);
        string randTile2 = chosenMove.substr(2, 2);

        // make move
        g.move(randTile1, randTile2);
    }
}

void Computer::levelThreeMove(Game &g) {
    // get legal moves that are preferred by level 3
    std::vector<std::string> totalMoves = g.generateLegalMovesLevel3(getColour());
    int numTotalMoves = totalMoves.size();

    // do a level 2 move if no level 3 moves
    if (numTotalMoves == 0) {
        levelTwoMove(g);
    }
    // perform a level 3 move
    else {
        // choose a completely random move from the given selection
        srand(static_cast<unsigned int>(time(nullptr)));
        string chosenMove = totalMoves[rand() % numTotalMoves];

        // convert chosenMove to tiles
        string randTile1 = chosenMove.substr(0, 2);
        string randTile2 = chosenMove.substr(2, 2);

        // make move
        g.move(randTile1, randTile2);
    }
}

void Computer::levelFourMove(Game &g) {
    // get legal moves that are preferred by level 4
    std::vector<std::string> totalMoves = g.generateLegalMovesLevel4(getColour());
    int numTotalMoves = totalMoves.size();

    // do a level 3 move if there are no level 4 moves
    if (numTotalMoves == 0) {
        levelThreeMove(g);
    }
    // perform a level 4 move
    else {
        // choose a completely random move from the given selection
        srand(static_cast<unsigned int>(time(nullptr)));
        string chosenMove = totalMoves[rand() % numTotalMoves];

        // convert chosenMove to tiles
        string randTile1 = chosenMove.substr(0, 2);
        string randTile2 = chosenMove.substr(2, 2);

        // make move
        g.move(randTile1, randTile2);
    }
}



// public methods

// ctor
Computer::Computer(char colour, float score, bool computer, int level, std::vector<std::vector<Piece *>> &board): Player(colour, score, computer), level{level}, board{board} {}

void Computer::bestMove(Game &g) {

    if (level == 1) {
        levelOneMove(g);
    }
    else if (level == 2) {
        levelTwoMove(g);
    }
    else if (level == 3) {
        levelThreeMove(g);
    }
    else {
        levelFourMove(g);
    }
}

