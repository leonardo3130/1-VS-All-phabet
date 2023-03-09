#include <iostream>

#include "Character.hpp"
<<<<<<< HEAD
#include "monster.hpp"
=======

//#include "Monster.hpp"
>>>>>>> 98e5406f92e26feb9900f7915123d1e06b5d2604

using namespace std;

class Monster : public Character{
    protected:
        int move_x; //di quando si muove in automatico a dx/sx
        int move_y; //  "                         "    su/giu
        int speed;  // ogni quanti referesh della mappa si muove
        int shot_fr; //ogni quanto spara
        
    public:
        int id; //codice identificativo univoco per ogni istanza
        Monster(int move_x = 1, int move_y = 0, int speed = 5, int shot_fr = 4, int id) : Character(x, y, '&', hp, atk, gun);  
};

//codice per lista mostri
struct mlist{
  Monster mon;
  monst_list *next;
};

typedef mlist* pmon;

pmon new_monster(pblu lista, Monster m){
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