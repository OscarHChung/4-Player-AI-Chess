#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include "game.h"

class Game;

class Player {
	char colour;
    float score;
    bool computer; // computer or human player
public:
	Player(char colour, float score, bool computer); // constructor for player
	char getColour(); 
    float getScore();
    void changeScore(float amount);
    bool isComputer();
    virtual void bestMove(Game &g);
    virtual ~Player(); // dtor for player
};

#endif
