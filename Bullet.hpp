#include "Map.hpp"
#include <ncurses.h>

class Bullet{
    protected:
        double speed;   //velocità: 1 corrisponde al movimento di una cella al secondo, la formula dell'intervallo di movimento è (1 sec) / (speed)
        
        char look;

    public:
        int x;          //posizione di partenza del poriettile
        int y;          //
        int dir;        //direzioen proiettile (corriponde alla mode del personaggio da cui viene sparato)
        int id; ///codice identificativo univoco per ogni istanza
        Bullet(double speed = 1, int x = 0, int y = 0, int dir = 0,  int *id = 0, char look = '.');
        void shot(Map mappa); 
};

//codice per lista proiettili
struct blist{
  Bullet bul;
  blist *next;
};

typedef blist *pbul;

pbul new_bullet(pbul lista, Bullet b){
  pbul tmp = new blist;
  tmp->bul = b;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pbul delete_bullet(pbul p, int val_id){
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