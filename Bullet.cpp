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
            collision = 1;
            //next_char = mappa.getMapChar((this->x)+1, this->y);
        }
    }
    else if(this->dir == 1 ){
        if(mappa.isempty(this->x, (this->y) + 1)==true){
            this->y+=1;
        }
        else{
            collision = 1;
            //next_char = mappa.getMapChar(this->x, (this->y)+1);
        }
        
    }
    else if(this->dir == 2 ){
        if(mappa.isempty((this->x) - 1, this->y)==true){
            this->x-=1;
        }
        else{
            collision = 1;
            //next_char = mappa.getMapChar((this->x)-1, this->y);
        }
    }    
    else if(this->dir == 3 ){
        if(mappa.isempty(this->x, (this->y) - 1)==true){
            this->y-=1;
        }
        else{
            collision = 1;
            //next_char = mappa.getMapChar(this->x, (this->y)-1);
        }
        
    }
    /*
    if(int(next_char) >= 65 && int(next_char) <= 90){
        collision = 3;
    }
    else if(next_char == '1'){
        collision = 2;
    }
    else{
        collision = 1;
    }*/
    /*
    if(next_char!=' '){
        collision = 1;
    }*/
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

pbul remove_bullet(pbul p, int x, int y, int dir){
	if(p == NULL)
        return(p);
	else if(p->bul.x == x && p->bul.y == y && p->bul.dir == dir)
        return(p->next);
	else{
		pbul p_before, head;
		bool found = false;
		head = p;
		while((p != NULL) && !found){
			if(p->bul.x == x && p->bul.y == y && p->bul.dir == dir)
        found = true ;
			else{
				p_before = p;
				p = p->next;
			}
		}
		if(found){
			p_before->next = p->next;
		}
		return(head);
	}
}
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
