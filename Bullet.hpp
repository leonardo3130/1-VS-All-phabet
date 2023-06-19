#include "Map.hpp"

class Bullet{
    protected:
        int x;          //posizione di partenza 
        int y;          
        char look;      //aspetto del proiettile
        int dir;        //direzione proiettile
        bool from;      //0 sparato da player, 1 sparato da mostro

    public:
        Bullet(int x = 0, int y = 0, int dir = 0, char look = '*', bool from = 0);  
        int move_bul(Map& mappa);       //movimento del proiettile con relativi controlli   
        int getX();                     //ritorna la coordinata x
        int getY();                     //ritorna la coordinata y
        char getLook();                 //carattere del proiettile
        int getDir();                   //direzione del proiettile
        bool getFrom();                 //chi ha sparato il proiettile
};

//codice per lista proiettili
struct blist{
  Bullet bul;
  int prev_x;
  int prev_y;
  blist *next;
};
typedef blist *pbul;

//inserimento
pbul new_bullet(pbul lista, Bullet b);

//ricerca
pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y);