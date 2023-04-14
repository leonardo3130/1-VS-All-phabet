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