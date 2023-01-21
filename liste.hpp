#include <iostream>
#include "Bullet.cpp"
#include "Bullet.hpp"
#include "Monster.cpp"
#include "Monster.hpp"
using namespace std;

//in questo file strutture lista e funzioni per tenere traccia di ogni mostro 
//e ogni proiettile presenti contemporaneamente nella mappa

// ! da inizializzare le liste nel main !

//codice per lista proiettili
struct bul_list{
  Bullet bul;
  bul_list *next;
}
typedef bul_list* pbul;

pbul new_bullet(pblu lista, Bullet b){
  pbul tmp = new bul_list;
  tmp->bul = b;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pbul delete_bullet(pbul p, int val_id){
	if(p == NULL) 
        return(p);
	else if(p->val == e) 
        return(p->next);
	else{
		pbul p_before, head;
		bool found = false;
		head = p;
		while((p != NULL) && !found){
			if(p->bul.id == val_id)  //da controllare se la sintassi "p->bul.id" è giusta
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


//codice per lista mostri
struct monst_list{
  Monster mon;
  monst_list *next;
}
typedef monst_list* pmon;

pmon new_monster(pblu lista, Monster m){
  pmon tmp = new monst_list;
  tmp->mon = m;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pmon delete_monster(pmon p, int val_id){
	if (p == NULL) 
        return(p);
	else if (p->val == e) 
        return(p->next);
	else{
		pmon p_before, head;
		bool found = false;
		head = p;
		while((p != NULL) && !found){
			if(p->mon.id == val_id)  //da controllare se la sintassi "p->mon.id" è giusta
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
