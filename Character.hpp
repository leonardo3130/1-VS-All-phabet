#include "Map.hpp"

class Character{
  protected:
    int x;      //coordinata x
    int y;      //coordinata y
    char look;  //lettera usata per identificare il personaggio
    int hp;     //numero totale di hp
    int atk;    //valore attacco (contatto)
    bool gun;   //il personaggio spara?
                //(no valore di difesa perchè ai mostri non serve: non comprano aramture)

  public:
    //costruttore
    Character(int x = 0, int y = 0, char look = '/', int hp = 1, int atk = 1, bool gun = false);

    
    void move(int new_x, int new_y=0, int mode = 0);
};

bool is_empty(Map mappa, int x, int y){ //dice se la cella è vuota
  if(mappa.getMapChar(y,x)==" ")
    return true;
  else
    return false;
}

bool is_inside(Map mappa, int x, int y){ //dice se la cella è dentro alla mappa
  if(mappa.getWidth()>=x && mappa.getHeight()>=y)
    return true;
  else
    return false;
}

