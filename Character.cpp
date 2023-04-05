#include <iostream>
#include "Character.hpp"


using namespace std;

Character::Character(){} //costruttore di default

Character::Character(char look){
    this->x = 1;
    this->y = 1;
    this->mode = 0;
    this->look = look;
    this->hp = 10;
    this->atk = 5;
    this->def = 5;
};

Character::Character(int x, int y, int hp, int atk, int def, int mode, char look){
    this->x = x;
    this->y = y;
    this->mode = mode;
    this->look = look;
    this->hp = hp;
    this->atk = atk;
    this->def = def;
};

bool is_inside(Map mappa, int x, int y){ //dice se la cella è dentro alla mappa
  if(mappa.getWidth() >= x && mappa.getHeight() >= y)
    return true;
  else
    return false;
}

bool isempty(Map m, int x, int y){ //dice se la cella è vuota
  if(m.getMapChar(y,x)==' ')
    return true;
  else
    return false;
}

void Character::SetHp(int hp){
    this->hp = hp;
}

int Character::getHp (){
    return this->hp;
};

int Character::getDef() {
    return this->def;
}

int Character::getAtk() {
    return this->atk;
}

void Character::moveright(Map mappa){
    if(isempty(mappa, (this->x)+1, this->y)==true && is_inside(mappa, this->x+1, this->y)==true){
        this->x += 1;
        this->mode = 0;
    }
            

}
void Character::moveleft(Map mappa){
    if(isempty(mappa, (this->x)-1, this->y)==true && is_inside(mappa, (this->x)-1, this->y)==true){
        this->x -= 1;
        this->mode = 2;
    }
}
void Character::moveup(Map mappa){
    if(isempty(mappa, this->x, (this->y)-1)==true && is_inside(mappa, this->x, (this->y)-1)==true){
        this->y -= 1;
        this->mode = 3;
    }
}
void Character::movedown(Map mappa){
    if(isempty(mappa, this->x, (this->y)+1)==true && is_inside(mappa, this->x, (this->y)+1)==true){
        this->y += 1;
        this->mode = 1;
    }
}

void Character::move_to(Map mappa, int new_x, int new_y){
    if(isempty(mappa, new_x, new_y)==true){
        this->x = new_x;
        this->y = new_y;
        this->mode = 0;
    }
}

int Character::getX() { return this->x; }
int Character::getY() { return this->y; }

char Character::getLook() { return this->look; }

int global_blt_id = 0; //da inizializzare nel main

/*void Character::fire(int b_speed, Map mappa){
    global_blt_id += 1; //ogni proiettile ha un id diverso: ogni volta che si chiama la funzione fire, viene incrementato

    int p_id = global_blt_id;
    Bullet()


}*/
