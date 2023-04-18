#include <ncurses.h>
#include "Bullet.hpp"

Bullet::Bullet(double speed, int x, int y, int dir, int id, char look){
    this->speed = speed; //velocita' del proiettile
    this->x = x; //posizione di partenza del proiettile
    this->y = y;
    if(dir>=0 && dir<=3){ this->dir = dir; } else{ this->dir = 0; }
    this->look = look; 
    this->id = id; //codice identificativo univoco per ogni istanza
}



void Bullet::move_bul(Map& mappa, int dir){
//m_mode determina la direzione di spostamento: come per l'attributo mode di Character 0=right  1=down  2=left  3=up
    this->dir = dir;
    if(this->dir == 0  &&  mappa.isempty(this->x + 1, this->y)==true){
        this->x+=1;
    }
    else if(this->dir == 1  &&  mappa.isempty(this->x, this->y + 1)==true){
        this->y+=1;
    }
    else if(this->dir == 2  &&  mappa.isempty(this->x - 1, this->y)==true){
        this->x-=1;
    }    
    else if(this->dir == 3  &&  mappa.isempty(this->x, this->y - 1)==true){
        this->y-=1;
    }
    else{
        this->~Bullet();  //viene chiamato il distruttore sull'oggetto (il distruttore c'è di default, non è da dichiarare)
    }
}
/*
    int bul_delay = 100 / this->speed; //100 millisecondi / velocità : più è alta la velocità, minore è il delay di movimento del proiettile

    if(this->dir == 0){
        while(mappa.isempty(this->x + 1, this->y) == true){ 
            napms(bul_delay);
            this->x += 1; //proiettile sparato a destra
        }
    }
    else if(this->dir == 2){
        while(mappa.isempty(this->x - 1, this->y) == true){
            napms(bul_delay);
            this->x -= 1; //proiettile sparato a sinistra
        }
    }
    else if(this->dir == 3){
        while(mappa.isempty(this->x, this->y + 1) == true){
            napms(bul_delay);
            this->y += 1; //proiettile sparato in alto
        }
    }
    else if(this->dir == 1){
        while(mappa.isempty(this->x, this->y - 1) == true){
            napms(bul_delay);
            this->y -= 1; //proiettile sparato in basso
        }
    }
}*/

//codice lista proiettile
pbul new_bullet(pbul lista, Bullet b){
  pbul tmp = new blist;
  tmp->bul = b;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pbul remove_bullet(pbul p, int val_id){
	if(p == NULL)
        return(p);
	else if(p->bul.id == val_id)
        return(p->next);
	else{
		pbul p_before, head;
		bool found = false;
		head = p;
		while((p != NULL) && !found){
			if(p->bul.id == val_id)
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