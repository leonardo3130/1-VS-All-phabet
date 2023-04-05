#include <iostream>
#include "Character.hpp"


using namespace std;

class Monster : public Character{
    protected:
        int speed;  // velocità
        int shot_fr; //ogni quanto spara

    public:
        int id; //codice univoco per ogni istanza
        Monster(int move_x = 1, int move_y = 0, int speed = 5, int shot_fr = 4, int id) : Character(x, y, '&', hp, atk, gun);
        void fight(Map mappa, Player p);
        void fire_loop(Map mappa);
        void move_rand(Map mappa, Player p);       //quando incontra un muro, il mostro sceglie una direzione random
        void move(bool dir, Map mappa, Player p);    //il mostro si muove in verticale o in orizzontale
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
