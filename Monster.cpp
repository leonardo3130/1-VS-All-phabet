#include <iostream>
#include <ncurses.h>
#include <cmath>

#include "Monster.hpp"

using namespace std;

//costruttore
Monster::Monster(int speed, int shot_fr, int id):Character(x, y, mode, hp, atk, def, look) {
    this->speed = speed;
    this->shot_fr = shot_fr;
    this->id = id;
};


//contatto con player: i mostri perdono hp in base all' atk del player e al prorpio def, e viceversa
void Monster::fight(Map mappa, Player pl){ 
    this->hp -= 1*(pl.pers.atk)/(this->def);
    pl.pers.hp -= 1*(this->def)/(pl.pers.def);
}


void Monster::fire_loop(Map mappa, int livello){

    int m_bullet_speed = 1 * (livello / 3); //liv 3 vel = 1, liv 6 vel = 2 ..... 

    while(this->hp>0){
        this->fire(m_bullet_speed, mappa);
        napms(100 * this->shot_fr);
    }

}

void Monster::move(Map mappa, Player pl){
    srand(time(NULL));

    this->mode= rand()%4; //m_mode determina la direzione di spostamento: come per l'attributo mode di Character 0=right  1=down  2=left  3=up

    while(this->hp>0){
        if(this->mode == 0){
            while(mappa.isempty(this->x + 1, this->y)==true){
                moveright(mappa);
                napms(500/this->speed); //cambiare parametro per variare la velocita' 
            }

            if(int(mappa.getMapChar(this->x + 1, this->y)) == 1){ //verifica se il carattere incontrato e' il player
                fight(mappa, pl);
            }

            do{     
                this->mode = rand()%4;      //viene scelta una nuova direzione diversa da quella precedente
            }while(this->mode == 0);
        }

        else if(this->mode == 1){
            while(mappa.isempty(this->x, this->y+1)==true){
                movedown(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x, this->y+1))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 1);
        }

        else if(this->mode == 2){
            while(mappa.isempty(this->x - 1, this->y)==true){
                moveleft(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x - 1, this->y))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 2);
        }

        else if(this->mode == 3){
            while(mappa.isempty(this->x, this->y-1)==true){
                moveup(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x, this->y-1))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 3);
        }
    }
}