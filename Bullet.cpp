#include <ncurses.h>
#include "Bullet.hpp"

Bullet::Bullet(int x, int y, int dir, char look){
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look;
    }



int Bullet::move_bul(Map& mappa){
    int collision = 0;
    char next_char = ' ';
    if(this->dir == 0 ){
        if(mappa.isempty((this->x) + 1, this->y)==true){
            this->x+=1;
        }
        else{
            next_char = mappa.getMapChar(this->y, (this->x)+1);
        }
    }
    else if(this->dir == 1 ){
        if(mappa.isempty(this->x, (this->y) + 1)==true){
            this->y+=1;
        }
        else{
            next_char = mappa.getMapChar((this->y)+1, this->x);
        }

    }
    else if(this->dir == 2 ){
        if(mappa.isempty((this->x) - 1, this->y)==true){
            this->x-=1;
        }
        else{
            next_char = mappa.getMapChar(this->y, (this->x)-1);
        }
    }
    else if(this->dir == 3 ){
        if(mappa.isempty(this->x, (this->y) - 1)==true){
            this->y-=1;
        }
        else{
            next_char = mappa.getMapChar((this->y)-1, this->x);
        }

    }

    if(next_char=='/'){
        collision = 1;
    }
    else if(next_char >= 'A' && next_char <= 'Z'){
        collision = 3;
    }
    else if(next_char == '1'){
        collision = 2;
    }

    return(collision);
}


//codice lista proiettile
pbul new_bullet(pbul lista, Bullet b){
  pbul tmp = new blist;
  tmp->bul = b;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

///////////////////////////////////////////////         da cancellare
pbul remove_bullet(pbul p, pbul p_before, pbul bul_list){
    
    if(p == bul_list){
        bul_list = bul_list->next;
        p = bul_list;
    }
    else{
        p_before->next = p->next;
        p = p->next;
    }
    return bul_list;
}
////////////////////////////////////////////////////////////////

pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y){
        pbul tmp = lista_proiettili;
        bool found = false;
        while(!found && tmp != NULL){
            if(tmp->bul.x == x && tmp->bul.y == y){
                found = true;
            }
            else
                tmp = tmp->next;
        }
        return tmp;
}
