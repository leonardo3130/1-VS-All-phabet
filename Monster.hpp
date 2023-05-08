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
        Monster(int x = 2, int y = 3,int hp = 100, int atk = 10,int def = 10, int mode = 0, char look = 'A', int id = 0, int speed = 1, int shot_fr = 1);
        void move(Map& mappa, int x_p, int y_p);
        void moveright(Map mappa);
        void moveleft(Map mappa);
        void moveup(Map mappa);
        void movedown(Map mappa);
};


//codice per lista mostri
typedef struct mlist{
    Monster mon;
    int prev_x;
    int prev_y;
    mlist *next;
}* pmon;


pmon new_monster(pmon lista, Monster m);

pmon delete_monster(pmon p, int val_id);

pmon search_monster_by_xy(pmon lista_mostri, int x, int y);


