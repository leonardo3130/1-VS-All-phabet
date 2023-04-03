#include <iostream>
#include "Map.hpp"

using namespace std;

class Character{
  protected:
    int x;      //coordinata x
    int y;      //coordinata y
    int hp;     //numero totale di hp
    int atk;    //valore attacco (contatto)
    int def;    //valore di difesa
    char look;  //lettera usata per identificare il personaggio

  public:
    Character();
    Character(char look); //costruttore
    Character(int x, int y, int hp, int atk, int def, char look); //costruttore
    void moveright(Map mappa);
    void moveleft(Map mappa);
    void moveup(Map mappa);
    void movedown(Map mappa);
    void move_to(Map mappa, int new_x, int new_y=0) //new_x/new_y = coordinate nuova posizione 
    void fire(int dir, int b_speed, Map mappa); //funzione spara dir = direzione (0,1,2,3); b_speed = velocità del proiettile
    void SetHp(int hp);
    int getHp();
    int getDef();
    int getAtk();
};



