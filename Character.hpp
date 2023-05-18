#pragma once
#include "Map.hpp"
#include "Bullet.hpp"


class Character{
  protected:
    int x;      //coordinata x
    int y;      //coordinata y
    double hp;     //healt points
    int atk;      //attacco (contatto)
    int def;      //difesa
    int mode;   //direzione del personaggio, corrisponde all'ultima funzione di movimento invocata su di esso (right 0, down 1, left 2, up 3)
    char look;  //lettera usata per identificare il personaggio

  public:
    Character();
    Character(char look); //costruttore
    Character(int x, int y, double hp, int atk, int def, int mode, char look); //costruttore
    void setX_Y(int x0, int y0);
    void moveright(Map mappa);  //muove a dx
    void moveleft(Map mappa);   //muove a sx
    void moveup(Map mappa);     //muove su
    void movedown(Map mappa);   //muove giu
    void move_to(Map mappa, int new_x, int new_y); //new_x/new_y = coordinate nuova posizione
    pbul fire(pbul ls_proiettili, Map& map, int dir, bool from);   //funzione spara
    int getX();
    int getY();
    void SetHp(double hp);
    double getHp();
    void incHP(double n);
    int getAtk();
    void incAtk(int n);
    int getDef();
    void incDef(int n);
    int getMode();
    char getLook();
    void setLook(char look);
};
