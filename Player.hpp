#pragma once
#include <iostream>
#include <cstring>
#include "Character.hpp"


class Player : public Character{
    protected:
        char nick[20];  //nome del player
        char psw[20];   //psw del player
        int money;     //numero di monete del giocatore

    public:
        Player(char* nick, char* psw, int monete, char l);
        char* getNick();
        int getMoney();
        void takeMoney(int value);
};
