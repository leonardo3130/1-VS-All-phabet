#include <iostream>
#include "Character.hpp"


using namespace std;

bool isempty(Map mappa, int x, int y){ //dice se la cella è vuota
  if(mappa.getMapChar(y,x)==' ')
    return true;
  else
    return false;
}

Character::Character(int x, int y, char look, int hp, int atk, bool gun){
    this->x = x;
    this->y = y;
    this->look = look;
    this->hp = hp;
    this->atk = atk;
    this->gun = gun;
} 

void Character::SetHp(int hp){
    this->hp = hp;
}

int Character::getHp (){
    return this->hp;
};

Map m = Map(5, 5);

//Considerando che le coordinate in alto a destra del terminale sono x=0, y=0
void Character::move(int new_x, int new_y, int mode){
    //se la mode è 0 e la cella è vuota e nella mappa, sposta le coordinate correnti a quelle nuove (default)
    if(mode == 0)
        if(isempty(m, new_x, new_y)==true && is_inside(m, new_x, new_y)==true) 
            (this->x) = new_x, (this->y) = new_y;
    
    //se la mode è 1 e la cella è vuota e nella mappa,muove verso destra di tot "new_x" posizioni (va avanti)
    else if(mode == 1)
        if(isempty(m, this->x + new_x, this->y)==true && is_inside(m, this->x + new_x, this->y)==true)
            (this->x)+=new_x;
    
    //se la mode è 2 e la cella è vuota e nella mappa,muove verso sinistra di tot "new_x" posizioni (torna indietro)
    else if(mode == 2)
        if(isempty(m, this->x - new_x, this->y)==true && is_inside(m, this->x - new_x, this->y)==true)
            (this->x)-=new_x;

    //se la mode è 3 e la cella è vuota e nella mappa,muove verso sopra di tot "new_x" posizioni
    else if(mode == 3)
        if(isempty(m, this->x, this->y - new_y)==true && is_inside(m, this->x, this->y - new_y)==true)
            (this->y)-=new_y;

    //se la mode è 3 e la cella è vuota e nella mappa,muove verso sopra di tot "new_x" posizioni
    else if(mode == 4)
        if(isempty(m, this->x, this->y + new_y)==true && is_inside(m, this->x, this->y + new_y)==true)
            (this->y)+=new_y;
}

int global_blt_id = 0; //da inizializzare nel main

void Character::fire(int dir, int b_speed, Map mappa){
    if(this->gun){ 

        global_blt_id += 1; //ogni proiettile ha un id diverso: ogni volta che si chiama la funzione fire, viene incrementato
        
        int p_id = global_blt_id;

        Bullet new_b = Bullet(b_speed, this->x, this->y, p_id);
        pbul lista_bul = new_bullet(lista_bul, new_b); //lista_bul da inizializzare come variabile globale di tipo "pbul"
        //new_b.shot(dir, mappa, player);
    }
}