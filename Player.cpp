#include <iostream>
#include "Player.hpp"

Player::Player(char* nick, char* psw, int m, Character pers){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
    this->pers = pers; 
    this->monete = m;
};




