#include "Player.hpp"

Player::Player(char* nick, char* psw, int m):Character(x, y, mode, hp, atk, def, look){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw); 
    this->monete = m;
};