#pragma once
#include "Map.hpp"
#include "Bullet.hpp"


class Character{
  protected:


  public:
    int x;      //coordinata x
    int y;      //coordinata y
    float hp;     //healt points
    int atk;      //attacco (contatto)
    int def;      //difesa

    int mode;   //direzione del personaggio, corrisponde all'ultima funzione di movimento invocata su di esso (right 0, down 1, left 2, up 3)
    char look;  //lettera usata per identificare il personaggio
    Character();
    Character(char look); //costruttore
    Character(int x, int y, float hp, int atk, int def, int mode, char look); //costruttore
    void moveright(Map mappa);  //muove a dx
    void moveleft(Map mappa);   //muove a sx
    void moveup(Map mappa);     //muove su
    void movedown(Map mappa);   //muove giu
    void move_to(Map mappa, int new_x, int new_y); //new_x/new_y = coordinate nuova posizione 
    pbul fire(pbul ls_proiettili, Map& map, int dir, bool from);   //funzione spara 
    int coin_check(Map& m); //ritorna -1 se non ci sono monete intorno, 0 dx, 1 sotto, 2 sx, 3 sopra
    void SetHp(int hp);
    int getHp();
    int getDef();
    int getAtk();
    int getX();
    int getY();
    char getLook();
};
