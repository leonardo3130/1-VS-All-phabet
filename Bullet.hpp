#include "Map.hpp"

class Bullet{
    protected:
        int x;          //posizione di partenza 
        int y;          //
        char look;
        int dir;        //direzioen proiettile
        bool from;      //0 sparato da player, 1 sparato da mostro

    public:
        Bullet(int x = 0, int y = 0, int dir = 0, char look = '.', bool from = 0);
        //void delete_bullet();
        int move_bul(Map& mappa); 
        int getX();
        int getY();
        char getLook();
        int getDir();
        bool getFrom();
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
pbul remove_bullet(pbul p, pbul p_before, pbul bul_list);
pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y);
