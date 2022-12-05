#include "Player.hpp"

//costruttore
Player::Player(char nick[], int hp = 10, int def = 2, int atk = 2) {
    strcpy(this.nick, nick);
    this->hp = hp;
    this->def = def;
    this->atk = atk;
};



void Player::setHp(int new_hp);
int Player::getHp(){return this.hp;}