#include <ncurses.h>
#include "Bullet.hpp"

Bullet::Bullet(int x, int y, int dir, char look, bool from){
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look;
    this->from = from;
    }

int Bullet::move_bul(Map& mappa){
    int collision = 0;
    char next_char = ' ';
    if(this->dir == 0 ){
        if(mappa.isEmpty((this->x) + 1, this->y) && !mappa.isMoney((this->x) + 1, this->y)){
            this->x+=1;
        }
        else if((mappa.isMoney((this->x) + 1, this->y) || (mappa.isMonster((this->x) + 1, this->y) && this->from)) && mappa.isEmpty((this->x) + 2, this->y)){
            this->x+=2;
        }
        else if((mappa.isMoney((this->x) + 1, this->y) || (mappa.isMonster((this->x) + 1, this->y) && this->from)) && !mappa.isEmpty((this->x) + 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x)+2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x)+1);
        }
    }
    else if(this->dir == 1 ){
        if(mappa.isEmpty(this->x, (this->y) + 1) && !mappa.isMoney(this->x, (this->y) + 1)){
            this->y += 1;
        }
        else if((mappa.isMoney(this->x, (this->y) + 1) || (mappa.isMonster(this->x, (this->y) + 1) && this->from)) && mappa.isEmpty(this->x, (this->y) + 2)){
            this->y += 2;
        }
        else if((mappa.isMoney(this->x, (this->y) + 1) || (mappa.isMonster(this->x, (this->y) + 1) && this->from)) && !mappa.isEmpty(this->x, (this->y) + 2)){
            next_char = mappa.getMapChar((this->y) + 2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y) + 1, this->x);
        }
    }
    else if(this->dir == 2 ){
        if(mappa.isEmpty((this->x) - 1, this->y) && !mappa.isMoney((this->x) - 1, this->y)){
            this->x -= 1;
        }
        else if((mappa.isMoney((this->x) - 1, this->y) || (mappa.isMonster((this->x) - 1, this->y)) && this->from) && mappa.isEmpty((this->x) - 2, this->y)){
            this->x -= 2;
        }
        else if((mappa.isMoney((this->x) - 1, this->y) || (mappa.isMonster((this->x) - 1, this->y)) && this->from) && !mappa.isEmpty((this->x) - 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x) - 2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x) - 1);
        }
    }
    else if(this->dir == 3 ){
        if(mappa.isEmpty(this->x, (this->y) - 1) && !mappa.isMoney(this->x, (this->y) - 1)){
            this->y -= 1;
        }
        else if((mappa.isMoney(this->x, (this->y)-1) || (mappa.isMonster(this->x, (this->y)-1) && this->from)) && mappa.isEmpty(this->x, (this->y) - 2)){
            this->y -= 2;
        }
        else if((mappa.isMoney(this->x, (this->y) - 1)|| (mappa.isMonster(this->x, (this->y)-1) && this->from)) && !mappa.isEmpty(this->x, (this->y) - 2)){
            next_char = mappa.getMapChar((this->y)-2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y)-1, this->x);
        }
    }

    if(next_char == '/' || next_char == '[' || next_char == ']')
        collision = 1;

    else if(next_char >= 'A' && next_char <= 'Z'){
        if(this->from == 0)
            collision = 3;
        else
            collision = 1;
    }
    else if(next_char == '1')
        collision = 2;

    return(collision);
}

int Bullet::getX(){
    return this->x;
}
int Bullet::getY(){
    return this->y;
}
char Bullet::getLook(){
    return this->look;
}
int Bullet::getDir(){
    return this->dir;
}
bool Bullet::getFrom(){
    return this->from;
}

//codice lista proiettile
pbul new_bullet(pbul lista, Bullet b){
  pbul tmp = new blist;
  tmp->bul = b;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pbul search_bullet_by_xy(pbul lista_proiettili, int x, int y){
        pbul tmp = lista_proiettili;
        bool found = false;
        while(!found && tmp != NULL){
            if(tmp->bul.getX() == x && tmp->bul.getY() == y){
                found = true;
            }
            else
                tmp = tmp->next;
        }
        return tmp;
}
