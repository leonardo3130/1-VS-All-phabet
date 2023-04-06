#include <iostream>
#include "Character.hpp"
#include "Player.hpp"

using namespace std;

class Monster : public Character{
    protected:
        int speed;  // velocita'
        int shot_fr; //ogni quanto spara

    public:
        int id; //codice univoco per ogni istanza
        Monster(int speed = 5, int shot_fr = 4, int id = 0);   //   :Character(x, y, mode, hp, atk, def, look);
        void fight(Map mappa, Player p);                //interazione tra mostro e player
        void fire_loop(Map mappa, int livello);         //continua a sparare finche' non muore
        void move(Map mappa, Player pl);                //si muove a caso
};

//codice per lista mostri
struct mlist{
  Monster mon;
  mlist *next;
};

typedef mlist* pmon;

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
