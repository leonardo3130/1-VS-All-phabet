#pragma once
#include <iostream>
#include <cstring>

#include "Character.hpp"


class Player : public Character{
    protected:
        char nick[20];  //nome del player
        char psw[20];   //psw del player
        int monete;     //numero di monete del giocatore

    public:
        Player(char* nick, char* psw, int monete);
};



//Player.cpp

//#include "Player.hpp"

Player::Player(char* nick, char* psw, int m):Character(x, y, mode, hp, atk, def, look){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw); 
    this->monete = m;
};
