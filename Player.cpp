#include "Player.hpp"

Player::Player(char* nick, char* psw, int m, char l) : Character(l){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
    this->money = m;
}

char* Player::getNick(){
    return this->nick;
}

int Player::getMoney(){
    return this->money;
}


