#include <string>
#include "game.h"
#include "player.h"


Player::Player(char colour, float score, bool computer): colour{colour}, score{score}, computer{computer} {}

char Player::getColour() {
    return colour;
}

float Player::getScore() {
    return score;
}

void Player::changeScore(float amount) {
    score += amount;
}

bool Player::isComputer() {
    return computer;
}

void Player::bestMove(Game &g) {}

Player::~Player() {}

