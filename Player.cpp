#include "Player.hpp"
#include <cstring>

Player::Player(char nick[], int def) : Character(x, y, look, hp, atk, gun) {
    strcpy(this->nick, nick);
    this->def = def;
};

