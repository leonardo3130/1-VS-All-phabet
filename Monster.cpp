#include <ncurses.h>
#include <cmath>
#include "Monster.hpp"
#include <unistd.h>

//costruttore
//Monster::Monster(int x, int y, float hp, int atk, int def, int mode, char look, int speed = 5, int shot_fr = 4, int id = 0):Character(x, y, mode, hp, atk, def, look) {
//    this->speed = speed;
//    this->shot_fr = shot_fr;
//    this->id = id;
//};
Monster::Monster(int x, int y,int hp, int atk ,int def, int mode, char look, int id, int speed, int shot_fr) {
    this->x = x;
    this->y = y;
    this->mode = mode;
    this->look = look;
    this->hp = hp;
    this->atk = atk;
    this->def = def;
    this->id = id;
    this->speed = speed;
    this->shot_fr = shot_fr;
};


//contatto con player: i mostri perdono hp in base all' atk del player e al prorpio def, e viceversa
void Monster::moveright(Map mappa){
    if(!mappa.ismoney((this -> x) + 1, this -> y) && !mappa.ismonster((this -> x) + 2, this -> y))
        Character::moveright(mappa);
}
void Monster::moveleft(Map mappa){
    if(!mappa.ismoney((this -> x) - 1, this -> y) && !mappa.ismonster((this -> x) - 2, this -> y))
        Character::moveleft(mappa);
}
void Monster::moveup(Map mappa){
    if(!mappa.ismoney(this -> x, (this -> y) - 1) && !mappa.ismonster(this -> x, (this -> y) - 2))
        Character::moveup(mappa);
}
void Monster::movedown(Map mappa){
    if(!mappa.ismoney(this -> x, (this -> y) + 1) && !mappa.ismonster(this -> x, (this -> y) + 2))
        Character::movedown(mappa);
}


void Monster::move(Map& mappa, int x_p, int y_p){
//m_mode determina la direzione di spostamento: come per l'attributo mode di Character 0=right  1=down  2=left  3=up
    int mode;

    if(abs(this->x - x_p) < abs (this->y - y_p) && this->x != x_p){
        if(this->x < x_p ){
            this->moveright(mappa);
        }
        else {
            this->moveleft(mappa);
        }
    }
    else if(abs(this->x - x_p) > abs (this->y - y_p) && this->y != y_p){
        if(this->y < y_p){
            this->movedown(mappa);
        }
        else{
            this->moveup(mappa);
        }
    }
    else if(this->x == x_p && mappa.freeWay(this->x, x_p, this->y, y_p) == 0){
        //condizioni
        this->moveup(mappa);
    }
    else if(this->y == y_p && mappa.freeWay(this->x, x_p, this->y, y_p) == 0){
        //condizioni
        this->moveleft(mappa);
    }





    if(mode == 0){
        if(mappa.isempty(this->x + 1, this->y)==true){
            this->moveright(mappa);
        }
    }else if(mode == 1){
        if(mappa.isempty(this->x, this->y + 1)==true){
            this->movedown(mappa);
        }
    }else if(mode == 2){
        if(mappa.isempty(this->x - 1, this->y)==true){
            this->moveleft(mappa);
        }
    }else if(mode == 3){
        if(mappa.isempty(this->x, this->y - 1)==true){
            this->moveup(mappa);
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
            if(tmp->mon.x == x && tmp->mon.y == y)
                found = true;
            else
                tmp = tmp->next;
        }
        return tmp;
}
