#pragma once
#include <iostream>
#include "Character.hpp"
#include "Player.hpp"
#include <unistd.h>


class Monster : public Character{
    protected:


    public:
        int id; //codice univoco per ogni istanza
        int speed;  // velocita'
        int shot_fr; //ogni quanto spara
        Monster(int x = 5, int y = 3, int mode = 0, int hp = 10, int atk = 10, int def = 10, char  look = 'Y', int speed = 5, int shot_fr = 4, int id = 0);//:Character(x, y, mode, hp, atk, def, look);
        //void fire_loop(Map mappa, int livello, int global_id, pbul lista_p);         //continua a sparare finche' non muore
        void move(Map& mappa, int& mode);                //si muove a caso
};

//codice per lista mostri
struct mlist{
    Monster mon;
    int prev_x;
    int prev_y;
    mlist *next;
};

typedef struct mlist* pmon;

pmon new_monster(pmon lista, Monster m);

pmon delete_monster(pmon p, int val_id);

pmon search_monster_by_xy(pmon lista_mostri, int x, int y);
