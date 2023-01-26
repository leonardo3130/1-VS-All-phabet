#include <iostream>

#include "Player.hpp"

using namespace std;

Player::Player(char nick[], int def) : Character(x, y, look, hp, atk, gun) {
    strcpy(this->nick, nick);
    this->def = def;
};

