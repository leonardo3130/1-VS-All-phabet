#include <iostream>
#include <ncurses.h>

#include "Bullet.hpp"

using namespace std;

Bullet::Bullet(double speed, int x, int y, int dir, int id, char look){
    this->speed = speed; //velocità del proiettile
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look; 
    this->id = id; //codice identificativo univoco per ogni istanza
}

void Bullet::shot(Map mappa, Player giocatore){ 

    int bul_delay = 100 / this->speed; //100 millisecondi / velocità : più è alta la velocità, minore è il delay di movimento del proiettile

    if(this->dir == 0){
        while(is_empty(this->x + 1, this->y) == true){ 
            napms(bul_delay);
            this->x += 1
        }
        if(mappa.getMapChar(this->x + 1, this->y) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(this->dir == 2){
        while(is_empty(this->x - 1, this->y) == true){
            napms(bul_delay);
            this->x -= 1; //proiettile sparato a sinistra
        }
        if(mappa.getMapChar(this->x - 1, this->y) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(this->dir == 3){
        while(is_empty(this->x, this->y + 1) == true){
            napms(bul_delay);
            this->y += 1; //proiettile sparato in alto
        }
        if(mappa.getMapChar(this->x, this->y + 1) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
    else if(this->dir == 1){
        while(is_empty(this->x, this->y - 1) == true){
            napms(bul_delay);
            this->y -= 1; //proiettile sparato in basso
        }
        if(mappa.getMapChar(this->x, this->y - 1) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
    }
}

