#include <ncurses.h>
#include <cmath>
#include "Monster.hpp"
#include "Player.hpp"

//costruttore
Monster::Monster(int speed, int shot_fr, int id):Character(x, y, mode, hp, atk, def, look) {
    this->speed = speed;
    this->shot_fr = shot_fr;
    this->id = id;
};


//contatto con player: i mostri perdono hp in base all' atk del player e al prorpio def, e viceversa
void Monster::fight(Map mappa, Player pl){ 
    this->hp -= 1*(pl.atk)/(this->def);
    pl.hp -= 1*(this->def)/(pl.def);
}


void Monster::fire_loop(Map mappa, int livello, int *global_id, pbul lista_p){

    int m_bullet_speed = 1 * (livello / 3); //liv 3 vel = 1, liv 6 vel = 2 ..... 

    while(this->hp>0){
        this->fire(m_bullet_speed, mappa, global_id, lista_p);
        napms(100 * this->shot_fr);
    }

}

void Monster::move(Map mappa, Player pl){
    srand(time(NULL));

    this->mode= rand()%4; //m_mode determina la direzione di spostamento: come per l'attributo mode di Character 0=right  1=down  2=left  3=up

    while(this->hp>0){
        if(this->mode == 0){
            while(mappa.isempty(this->x + 1, this->y)==true){
                moveright(mappa);
                napms(500/this->speed); //cambiare parametro per variare la velocita' 
            }

            if(int(mappa.getMapChar(this->x + 1, this->y)) == 1){ //verifica se il carattere incontrato e' il player
                fight(mappa, pl);
            }

            do{     
                this->mode = rand()%4;      //viene scelta una nuova direzione diversa da quella precedente
            }while(this->mode == 0);
        }

        else if(this->mode == 1){
            while(mappa.isempty(this->x, this->y+1)==true){
                movedown(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x, this->y+1))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 1);
        }

        else if(this->mode == 2){
            while(mappa.isempty(this->x - 1, this->y)==true){
                moveleft(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x - 1, this->y))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 2);
        }

        else if(this->mode == 3){
            while(mappa.isempty(this->x, this->y-1)==true){
                moveup(mappa);
                napms(500/this->speed);
            }

            if(int(mappa.getMapChar(this->x, this->y-1))==1){
                fight(mappa, pl);
            }

            do{
                this->mode = rand()%4;
            }while(this->mode == 3);
        }
    }
}

pmon new_monster(pmon lista, Monster m){
  pmon tmp = new mlist;
  tmp->mon = m;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pmon delete_monster(pmon p, int val_id){
	if (p == NULL)
        return(p);
	else if (p->mon.id == val_id)
        return(p->next);
	else{
		pmon p_before, head;
		bool found = false;
		head = p;
		while((p != NULL) && !found){
			if(p->mon.id == val_id)
        found = true;
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

pmon search_monster_by_xy(pmon lista_mostri, int x, int y){
        pmon tmp = lista_mostri;
        bool found = false;
        while(!found && tmp != NULL){
                if(tmp->mon.x == x && tmp->mon.y == y){
                        found = true;
                }
                else
                        tmp = tmp->next;
        }
        return tmp;
}