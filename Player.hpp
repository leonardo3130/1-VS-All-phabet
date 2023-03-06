#include <iostream>
#include <cstring>

#include "Character.hpp"

class Player{
    protected:
        char nick[20];  //nome del player
        char psw[20];   //psw del player
        int monete;     //numero di monete del giocatore
        Character pers;

    public:
        // costruttore
        Player(char* nick, char* psw, int monete, Character pers);
        
};


//fare in modo che si possano salvare diversi player su file di testo organizzati in un archivio