#include "Player.hpp"
#include <cstring>

//costruttore
Player::Player(char nick[], int def = 2) {
    strcpy(this->nick, nick);
    this->def = def;
    this->look = "@";
};

