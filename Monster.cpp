#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <cmath>

#include "Monster.hpp"

using namespace std;

//costruttore
Monster::Monster(int speed, int shot_fr, int id) : Character(x, y, '§', hp, atk, gun) {
    this->speed = speed;
    this->shot_fr = shot_fr;
    this->id = id;
};


//in caso di contatto i mostri perdono hp in base al valore di attacco del player e al prorpio valore di difesa, e viceversa
void Monster::fight(Map mappa, Player pl){ 
    this->hp -= 1*(pl.pers.atk)/(this->def);
    pl.pers.hp -= 1*(this->def)/(pl.pers.def);
}

void fire_loop(Map mappa){

    int m_bullet_speed = 1; //da cambiare in base al livello

    while(this->hp>0){
        fire(m_bullet_speed, mappa);
        napms(100 * this->shot_fr);
    }

}

void Monster::move_rand(Map mappa, Player pl){
    srand(time(NULL));
    int m_mode = rand()%4;

    while(this->hp>0){
        if(m_mode == 0){
            while(mappa.isempty(this->x + 1, this->y)==true){
                moveright(mappa);
                napms(100/this->speed); //cambiare parametro per variare la velocità
                
            }
            char c = mappa.getMapChar(this->x + 1, this->y);
            if(int(c)==1)
                fight(mappa, pl);
            do{
                m_mode = rand()%4;
            }while(m_mode == 0)
        }

        else if(m_mode == 1){
            while(mappa.isempty(this->x, this->y+1)==true){
                movedown(mappa);
                napms(100/this->speed);
            }
            char c = mappa.getMapChar(this->x, this->y+1);
            if(int(c)==1)
                fight(mappa, pl);
            do{
                m_mode = rand()%4;
            }while(m_mode == 1)
        }

        else if(m_mode == 2){
            while(mappa.isempty(this->x - 1, this->y)==true){
                moveleft(mappa);
                napms(100/this->speed);
            }
            char c = mappa.getMapChar(this->x - 1, this->y);
            if(int(c)==1)
                fight(mappa, pl);
            do{
                m_mode = rand()%4;
            }while(m_mode == 2)
        }

        else if(m_mode == 3){
            while(mappa.isempty(this->x, this->y-1)==true){
                moveup(mappa);
                napms(100/this->speed);
            }
            char c = mappa.getMapChar(this->x, this->y-1);
            if(int(c)==1)
                fight(mappa, pl);
            do{
                m_mode = rand()%4;
            }while(m_mode == 3)
        }
    }
}

void Monster::move(bool dir, Map mappa, Player p){

}





////////////////////////////////////////////////
//
//
////////////////////////////////
//
//        |1|       |H|
//
//                          |L|
//
////////////////////////////////////////////////