#include <iostream>
#include <ctime>
#include <cstdio>
#include "Character.hpp"
#include "Character.cpp"
#include "Player.hpp"
#include "Player.cpp"
#include "map.hpp"
using namespace std;

Bullet::Bullet(double speed, Character personaggio, char look){
    this->speed = speed; //velocità del proiettile
    this->look = look; 
    this->x = personaggio->x; //posizione di partenza del proiettile
    this->y = personaggio->y;
}

// !!! il metodo shot richiede "<<flush" quando si stampa la mappa, altrimenti non funziona il conteggio dei secondi pe rla velocità
Bullet::shot(int mode, Map mappa, Player giocatore){ 
    clock_t time_0 = clock();
    double delay = 1/(this->speed) * CLOCKS_PER_SEC;

    if(mode == 1){
        while(is_empty(this->x + 1, this->y) == true){ 
            while(clock() - time_0 < delay)
                this->x += 1; //proiettile sparato a destra
        }
        if(mappa.getMapChar(this->x + 1, this->y) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(mode == 2){
        while(is_empty(this->x - 1, this->y) == true){
            while(clock() - time_0 < delay)
                this->x -= 1; //proiettile sparato a sinistra
        }
        if(mappa.getMapChar(this->x - 1, this->y) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(mode == 3){
        while(is_empty(this->x, this->y - 1) == true){
            while(clock() - time_0 < delay)
                this->y -= 1; //proiettile sparato in alto
        }
        if(mappa.getMapChar(this->x, this->y - 1) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(mode == 4){
        while(is_empty(this->x, this->y + 1) == true){
            while(clock() - time_0 < delay)
                this->y += 1; //proiettile sparato in basso
        }
        if(mappa.getMapChar(this->x, this->y + 1) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
}