#include "Character.hpp"
#include "Bullet.hpp"

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

Character::Character(int x, int y, float hp, int atk, int def, int mode, char look){
    this->x = x;
    this->y = y;
    this->mode = mode;
    this->look = look;
    this->hp = hp;
    this->atk = atk;
    this->def = def;
};

void Character::moveright(Map mappa){
    if(mappa.isempty((this->x)+1, this->y)==true && mappa.is_inside(this->x+1, this->y)==true){
        this->x += 1;
        this->mode = 0;
    }
}
void Character::moveleft(Map mappa){
    if(mappa.isempty((this->x)-1, this->y)==true && mappa.is_inside((this->x)-1, this->y)==true){
        this->x -= 1;
        this->mode = 2;
    }
}
void Character::moveup(Map mappa){
    if(mappa.isempty(this->x, (this->y)-1)==true && mappa.is_inside(this->x, (this->y)-1)==true){
        this->y -= 1;
        this->mode = 3;
    }
}
void Character::movedown(Map mappa){
    if(mappa.isempty(this->x, (this->y)+1)==true && mappa.is_inside(this->x, (this->y)+1)==true){
        this->y += 1;
        this->mode = 1;
    }
}

void Character::move_to(Map mappa, int new_x, int new_y){
    if(mappa.isempty(new_x, new_y)==true){
        this->x = new_x;
        this->y = new_y;
        this->mode = 0;
    }
}

int global_blt_id = 0;               //da inizializzare nel main
pbul lista_proiettili = NULL;        //  "   "

pbul Character::fire(pbul ls_proiettili, Map& map, int dir){
  Bullet nuovo_proiettile;
  if (dir == 0 && map.isempty(this-> x + 1, this->y)){
    nuovo_proiettile = Bullet(this->x + 1, this->y, dir, '*');
  }
  else if (dir == 1  && map.isempty(this-> x, this->y + 1)){
    nuovo_proiettile = Bullet(this->x, this->y + 1, dir, '*');
  }
  else if (dir == 2  && map.isempty(this-> x - 1, this->y)){
    nuovo_proiettile = Bullet(this->x - 1, this->y, dir, '*');
  }
  else if (dir == 3  && map.isempty(this-> x, this->y-1)){
    nuovo_proiettile = Bullet(this->x , this->y - 1, dir, '*');
  }

  ls_proiettili = new_bullet(ls_proiettili, nuovo_proiettile);
  return ls_proiettili;
}

void Character::SetHp(int hp){
    this->hp = hp;
}

int Character::getHp (){
    return this->hp;
};

int Character::getDef(){
    return this->def;
}

int Character::getAtk(){
    return this->atk;
}

int Character::getX(){ 
    return this->x; 
}

int Character::getY(){ 
    return this->y; 
}

char Character::getLook(){ 
    return this->look; 
}


//si controlla se nelle coordinate vicine è presente un proiettile, in tal caso si controlla se questo ha la direzione che va contro il personaggio, in tal caso il proiettile vien eliminato e il personaggio perde vita
void Character::bullet_check(Map m, pbul lista_proiettili){
  if( int(m.getMapChar(this->x-1, this->y)) == 42){
    pbul proiettile = search_bullet_by_xy(lista_proiettili, this->x-1, this->y);
    if(proiettile->bul.dir == 0){
      //lista_proiettili = remove_bullet(lista_proiettili, proiettile->bul.x, proiettile->bul.y, proiettile->bul.dir);
      this->hp =0;//-= 1/this->def;
    }
  }
  else if(int(m.getMapChar(this->x+1, this->y)) == 42){
    pbul proiettile = search_bullet_by_xy(lista_proiettili, this->x, this->y+1);
    if(proiettile->bul.dir == 2){
      //lista_proiettili = remove_bullet(lista_proiettili, proiettile->bul.x, proiettile->bul.y, proiettile->bul.dir);
      this->hp =0;//-= 1/this->def;
    }
  }
  else if(int(m.getMapChar(this->x, this->y-1)) == 42){
    pbul proiettile = search_bullet_by_xy(lista_proiettili, this->x, this->y-1);
    if(proiettile->bul.dir == 1){
      //lista_proiettili = remove_bullet(lista_proiettili, proiettile->bul.x, proiettile->bul.y, proiettile->bul.dir);
      this->hp =0;//-= 1/this->def;
    }    
  }
  else if(int(m.getMapChar(this->x, this->y+1)) == 42){
    pbul proiettile = search_bullet_by_xy(lista_proiettili, this->x, this->y+1);
    if(proiettile->bul.dir == 3){
      //lista_proiettili = remove_bullet(lista_proiettili, proiettile->bul.x, proiettile->bul.y, proiettile->bul.dir);        
      this->hp =0;//-= 1/this->def;
    }
  }
}
