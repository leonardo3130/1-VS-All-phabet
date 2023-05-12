#include <ncurses.h>
#include "Bullet.hpp"

Bullet::Bullet(int x, int y, int dir, char look, bool from){
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look;
    this->from = from;
    }



/*int Bullet::move_bul(Map& mappa){
    int collision = 0;
    char next_char = ' ';
    if(this->dir == 0 ){
        if(mappa.isempty((this->x) + 1, this->y) && !mappa.ismoney((this->x) + 1, this->y)){
            this->x+=1;
        }
        else if(mappa.ismoney((this->x) + 1, this->y) && mappa.isempty((this->x) + 2, this->y)){
            this->x+=2;
        }
        else if(mappa.ismoney((this->x) + 1, this->y) && !mappa.isempty((this->x) + 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x)+2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x)+1);
        }
    }
    else if(this->dir == 1 ){
        if(mappa.isempty(this->x, (this->y) + 1) && !mappa.ismoney(this->x, (this->y) + 1)){
            this->y += 1;
        }
        else if(mappa.ismoney(this->x, (this->y) + 1) && mappa.isempty(this->x, (this->y) + 2)){
            this->y += 2;
        }
        else if(mappa.ismoney(this->x, (this->y) + 1) && !mappa.isempty(this->x, (this->y) + 2)){
            next_char = mappa.getMapChar((this->y) + 2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y) + 1, this->x);
        }
    }
    else if(this->dir == 2 ){
        if(mappa.isempty((this->x) - 1, this->y) && !mappa.ismoney((this->x) - 1, this->y)){
            this->x -= 1;
        }
        else if(mappa.ismoney((this->x) - 1, this->y) && mappa.isempty((this->x) - 2, this->y)){
            this->x -= 2;
        }
        else if(mappa.ismoney((this->x) - 1, this->y) && !mappa.isempty((this->x) - 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x) - 2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x) - 1);
        }
    }
    else if(this->dir == 3 ){
        if(mappa.isempty(this->x, (this->y) - 1) && !mappa.ismoney(this->x, (this->y) - 1)){
            this->y -= 1;
        }
        else if(mappa.ismoney(this->x, (this->y)-1) && mappa.isempty(this->x, (this->y) - 2)){
            this->y -= 2;
        }
        else if(mappa.ismoney(this->x, (this->y) - 1) && !mappa.isempty(this->x, (this->y) - 2)){
            next_char = mappa.getMapChar((this->y)-2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y)-1, this->x);
        }
    }

    if(next_char == '/' || next_char == '[' || next_char == ']'){
        collision = 1;
    }
    else if(next_char >= 'A' && next_char <= 'Z'){
        if(this->from == 0){
            collision = 3;
        }
        else{
            collision = 1;
        }

    }
    else if(next_char == '1'){
        collision = 2;
    }

    return(collision);
}*/

int Bullet::move_bul(Map& mappa){
    int collision = 0;
    char next_char = ' ';
    if(this->dir == 0 ){
        if(mappa.isempty((this->x) + 1, this->y) && !mappa.ismoney((this->x) + 1, this->y)){
            this->x+=1;
        }
        else if((mappa.ismoney((this->x) + 1, this->y) || (mappa.ismonster((this->x) + 1, this->y) && this->from)) && mappa.isempty((this->x) + 2, this->y)){
            this->x+=2;
        }
        else if((mappa.ismoney((this->x) + 1, this->y) || (mappa.ismonster((this->x) + 1, this->y) && this->from)) && !mappa.isempty((this->x) + 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x)+2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x)+1);
        }
    }
    else if(this->dir == 1 ){
        if(mappa.isempty(this->x, (this->y) + 1) && !mappa.ismoney(this->x, (this->y) + 1)){
            this->y += 1;
        }
        else if((mappa.ismoney(this->x, (this->y) + 1) || (mappa.ismonster(this->x, (this->y) + 1) && this->from)) && mappa.isempty(this->x, (this->y) + 2)){
            this->y += 2;
        }
        else if((mappa.ismoney(this->x, (this->y) + 1) || (mappa.ismonster(this->x, (this->y) + 1) && this->from)) && !mappa.isempty(this->x, (this->y) + 2)){
            next_char = mappa.getMapChar((this->y) + 2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y) + 1, this->x);
        }
    }
    else if(this->dir == 2 ){
        if(mappa.isempty((this->x) - 1, this->y) && !mappa.ismoney((this->x) - 1, this->y)){
            this->x -= 1;
        }
        else if((mappa.ismoney((this->x) - 1, this->y) || (mappa.ismonster((this->x) - 1, this->y)) && this->from) && mappa.isempty((this->x) - 2, this->y)){
            this->x -= 2;
        }
        else if((mappa.ismoney((this->x) - 1, this->y) || (mappa.ismonster((this->x) - 1, this->y)) && this->from) && !mappa.isempty((this->x) - 2, this->y)){
            next_char = mappa.getMapChar(this->y, (this->x) - 2);
        }
        else {
            next_char = mappa.getMapChar(this->y, (this->x) - 1);
        }
    }
    else if(this->dir == 3 ){
        if(mappa.isempty(this->x, (this->y) - 1) && !mappa.ismoney(this->x, (this->y) - 1)){
            this->y -= 1;
        }
        else if((mappa.ismoney(this->x, (this->y)-1) || (mappa.ismonster(this->x, (this->y)-1) && this->from)) && mappa.isempty(this->x, (this->y) - 2)){
            this->y -= 2;
        }
        else if((mappa.ismoney(this->x, (this->y) - 1)|| (mappa.ismonster(this->x, (this->y)-1) && this->from)) && !mappa.isempty(this->x, (this->y) - 2)){
            next_char = mappa.getMapChar((this->y)-2, this->x);
        }
        else{
            next_char = mappa.getMapChar((this->y)-1, this->x);
        }
    }

    if(next_char == '/' || next_char == '[' || next_char == ']'){
        collision = 1;
    }
    else if(next_char >= 'A' && next_char <= 'Z'){
        if(this->from == 0){
            collision = 3;
        }
        else{
            collision = 1;
        }

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
