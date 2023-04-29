#pragma once
#include <iostream>
#include <cstring>
#include "Character.hpp"

struct arnd{
    int right;
    int under;
    int left;
    int above;
};

class Player : public Character{
    protected:
        char nick[20];  //nome del player
        char psw[20];   //psw del player
        

    public:
        int money;     //numero di monete del giocatore
        Player(char* nick, char* psw, int monete, char l);
        //void fight(arnd around, pmon monster_list);                //interazione tra mostro e player
        char* getNick();
        int getMoney();
        void takeMoney(int value);
        arnd check_around(Map& m);  //ritorna una struct con 4 interi che dicono cosa si trova nelle 4 posizioni intorno al player: 0 vuoto, 1 mostro, 2 moneta
};



