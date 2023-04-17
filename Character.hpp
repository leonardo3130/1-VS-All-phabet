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
    void fire(double b_speed, Map mappa, int *global_id, pbul ls_proiettili);   //funzione spara  b_speed = velocita' del proiettile
    void SetHp(int hp);
    int getHp();
    int getDef();
    int getAtk();
    int getX();
    int getY();
    char getLook();
    void bullet_check(Map m, pbul lista_proiettili);
};