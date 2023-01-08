#include "Player.hpp"
#include <cstring>

//costruttore
Player::Player(char nick[], int def = 2) {
    strcpy(this->nick, nick);
    this->def = def;
};


void Player::setHp(int new_hp){
    this->hp = new_hp;
}

int Player::getHp(){
    return this->hp;
};
