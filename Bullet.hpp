#pragma once
#include "Map.hpp"
#include <ncurses.h>


class Bullet{
    protected:
        double speed;   //velocità: 1 corrisponde al movimento di una cella al secondo, la formula dell'intervallo di movimento è (1 sec) / (speed)
        
        char look;

    public:
        int x;          //posizione di partenza del poriettile
        int y;          //
        int dir;        //direzioen proiettile (corriponde alla mode del personaggio da cui viene sparato)
        int id; ///codice identificativo univoco per ogni istanza
        Bullet(double speed = 1, int x = 0, int y = 0, int dir = 0,  int id = 0, char look = '.');
        //void delete_bullet();
        void move_bul(Map& mappa, int dir); 
};

//codice per lista proiettili
struct blist{
  Bullet bul;
  int prev_x;
  int prev_y;
  blist *next;
};

typedef blist *pbul;

pbul new_bullet(pbul lista, Bullet b);
pbul remove_bullet(pbul p, int val_id);
pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y);