#include <iostream>
#include <ctime>
#include <cstdio>

#include <Map.hpp>
#include <player.hpp>


using namespace std;

class Bullet{
    protected:
        double speed;   //velocità: 1 corrisponde al movimento di una cella al secondo, la formula dell'intervallo di movimento è (1 sec) / (speed)
        int x;          //posizione di partenza del poriettile
        int y;          //
        int dir;        //direzioen proiettile (corriponde alla mode del personaggio da cui viene sparato)
        char look;

    public:
        int id; ///codice identificativo univoco per ogni istanza
        Bullet(double speed = 1, int x = 0, int y = 0, int dir = 0,  int id = 0, char look = '.');
        //void shot(int mode, Map mappa, Player p); // !!! il metodo shot richiede "<<flush" quando si stampa la mappa, altrimenti non funziona il conteggio dei secondi pe rla velocità
};

//codice per lista proiettili
typedef struct blist{
  Bullet bul;
  blist *next;
} *pbul;

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


