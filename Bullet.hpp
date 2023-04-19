#pragma once
#include "Map.hpp"
#include <ncurses.h>


class Bullet{
    protected:
        char look;

    public:
        int x;          //posizione di partenza del poriettile
        int y;          //
        int dir;        //direzioen proiettile (corriponde alla mode del personaggio da cui viene sparato)
        Bullet(int x = 0, int y = 0, int dir = 0, char look = '.');
        //void delete_bullet();
        void move_bul(Map& mappa); 
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
pbul remove_bullet(pbul p, int x, int y, int dir);
pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y);
