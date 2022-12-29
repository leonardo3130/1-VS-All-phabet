#include "Character.hpp"

//costruttore
Character::Character(int x = 0, int y = 0, char look = '/', int hp = 1, int atk = 1, bool gun = false){
    this->x = x;
    this->y = y;
    this->look = look;
    this->hp = hp;
    this->atk = atk;

    //questo pezzo va pensato meglio
    this->gun = gun;
} 

//Considerando che le coordinate in alto a destra del terminale sono x=0, y=0
void Character::move(int new_x, int new_y=0, int mode = 0){
    //se la mode è 0 sposta le coordinate correnti a quelle nuove (default)
    if(mode == 0)
        (this->x) = new_x, (this->y) = new_y;
    
    //se la mode è 1 muove verso destra di tot "new_x" posizioni (va avanti)
    else if(mode == 1)
        (this->x)+=new_x;
    
    //se la mode è 2 muove verso sinistra di tot "new_x" posizioni (torna indietro)
    else if(mode == 2)
        (this->x)-=new_x;

    //se la mode è 3 muove verso sopra di tot "new_x" posizioni
    else if(mode == 3)
        (this->y)-=new_x;

    //se la mode è 3 muove verso sopra di tot "new_x" posizioni
    else if(mode == 4)
        (this->y)+=new_x;
}
