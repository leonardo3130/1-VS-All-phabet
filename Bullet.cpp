#include <ncurses.h>

//#include "Bullet.hpp"

Bullet::Bullet(double speed, int x, int y, int dir, int id, char look){
    this->speed = speed; //velocita' del proiettile
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look; 
    this->id = id; //codice identificativo univoco per ogni istanza
}

void Bullet::shot(Map mappa, Player giocatore, pmon lista_mostri){ 

    int bul_delay = 100 / this->speed; //100 millisecondi / velocità : più è alta la velocità, minore è il delay di movimento del proiettile

    if(this->dir == 0){
        while(mappa.is_empty(this->x + 1, this->y) == true){ 
            napms(bul_delay);
            this->x += 1; //proiettile sparato a destra
        }
        if(mappa.getMapChar(this->x + 1, this->y) == giocatore->look){
            giocatore.hp -= 1; //se colpisce il player, questo perde una vita
        }
        else if(int(mappa.getMapChar(this->x + 1, this->y))>65 && int(mappa.getMapChar(this->x + 1, this->y))<90){ //se colpisce un mostro, si ricerca il mostro in quella posizione e questo perde una vita
            pmon mostro = search_monster_by_xy(lista_mostri, this->x + 1, this->y);
            mostro->mon.hp -= 1; 
        }
    }
    else if(this->dir == 2){
        while(mappa.is_empty(this->x - 1, this->y) == true){
            napms(bul_delay);
            this->x -= 1; //proiettile sparato a sinistra
        }
        if(mappa.getMapChar(this->x - 1, this->y) == giocatore->look){
            giocatore.hp -= 1; 
        }
        else if(int(mappa.getMapChar(this->x - 1, this->y))>65 && int(mappa.getMapChar(this->x - 1, this->y))<90){
            pmon mostro = search_monster_by_xy(lista_mostri, this->x - 1, this->y);
            mostro->mon.hp -= 1;
        }
    }
    else if(this->dir == 3){
        while(mappa.is_empty(this->x, this->y + 1) == true){
            napms(bul_delay);
            this->y += 1; //proiettile sparato in alto
        }
        if(mappa.getMapChar(this->x, this->y + 1) == giocatore->look){
            giocatore.hp -= 1; 
        }
        else if(int(mappa.getMapChar(this->x , this->y + 1))>65 && int(mappa.getMapChar(this->x , this->y + 1))<90){
            pmon mostro = search_monster_by_xy(lista_mostri, this->x , this->y + 1);
            mostro->mon.hp -= 1;
        }
    }
    else if(this->dir == 1){
        while(mappa.is_empty(this->x, this->y - 1) == true){
            napms(bul_delay);
            this->y -= 1; //proiettile sparato in basso
        }
        if(mappa.getMapChar(this->x, this->y - 1) == giocatore->look){
            giocatore.hp -= 1; 
        }
        else if(int(mappa.getMapChar(this->x , this->y - 1))>65 && int(mappa.getMapChar(this->x + 1, this->y - 1))<90){
            pmon mostro = search_monster_by_xy(lista_mostri, this->x + 1, this->y - 1); 
            mostro->mon.hp -= 1;
        }
    }
}

