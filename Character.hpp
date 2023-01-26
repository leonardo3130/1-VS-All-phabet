#include <iostream>

#include "Map.hpp"
#include "Bullet.hpp"

using namespace std;



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
    Character(int x = 0, int y = 0, char look = 'x', int hp = 1, int atk = 1, bool gun = false); //costruttore
    void move(int new_x, int new_y=0, int mode = 0); //funzione muovi   new_x/new_y = coordinate nuova posizione     mode = direzione (0,1,2,3)
    void fire(int dir, int b_speed, Map mappa); //funzione spara    dir = direzione (0,1,2,3); b_speed = velocità del proiettile
    void SetHp(int hp);
    int getHp();
};





bool is_inside(Map mappa, int x, int y){ //dice se la cella è dentro alla mappa
  if(mappa.getWidth()>=x && mappa.getHeight()>=y)
    return true;
  else
    return false;
}