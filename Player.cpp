#include <iostream>
#include "Player.hpp"

Player::Player(char* nick, char* psw, int m, Character c){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
    this->pers = c; 
    this->monete = m;
};




