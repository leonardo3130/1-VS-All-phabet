#include "character.hpp"

Character::Charater(int x = 0, int y = 0, char look = "/", int hp = 1, int atk = 1, bool gun = false){  //costruttore
    this->x = x;
    this->y = y;
    this->look = look;
    this->hp = hp;
    this->atk = atk;
    this->gun = gun;
}

Character::move(bool xy = true, int val = 1){   //bool xy: true->asse x, false->asse y; int val: celle in una mossa
      if(xy == false){                   //muove su/giu
          this->y += val; 
      }
      else if(xy == true){               //muove dx/sx
          this->x += val; 
      }
    }
};
