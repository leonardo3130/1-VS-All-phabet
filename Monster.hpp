#pragma once 
#include <iostream>
#include "Character.hpp"
#include "Player.hpp"


class Monster : public Character{
    protected:


    public:
        int id; //codice univoco per ogni istanza
        int speed;  // velocita'
        int shot_fr; //ogni quanto spara
        Monster(int speed = 5, int shot_fr = 4, int id = 0);   //   :Character(x, y, mode, hp, atk, def, look);
        void fight(Map mappa, Player p);                //interazione tra mostro e player
        void fire_loop(Map mappa, int livello, int *global_id, pbul lista_p);         //continua a sparare finche' non muore
        void move(Map& mappa, Player& p, int& mode);                //si muove a caso
};

//codice per lista mostri
struct mlist{
  Monster mon;
  mlist *next;
};

typedef mlist* pmon;

pmon new_monster(pmon lista, Monster m);

pmon delete_monster(pmon p, int val_id);

pmon search_monster_by_xy(pmon lista_mostri, int x, int y);