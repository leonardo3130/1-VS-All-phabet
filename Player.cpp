#include "Player.hpp"
#include <cstring>

//costruttore
Player::Player(char nick[], char look = 'S', int hp = 10, int def = 2, int atk = 2) {
    strcpy(this->nick, nick);
    this->look = look;
    this->hp = hp;
    this->def = def;
    this->atk = atk;
};


void Player::setHp(int new_hp){
    this->hp = new_hp;
}

int Player::getHp(){
    return this->hp;
};
