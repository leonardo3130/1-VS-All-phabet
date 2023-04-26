#include <iostream>

#include "Bullet.hpp"
#include "Monster.hpp"
#include "Character.hpp"
#include "Map.hpp"


using namespace std;

int main(){
    pmon lista_mostri = NULL;
    int x = 2, y=3;
        for(int i=0; i<2; i++){
        Monster mostro(5,4, i);
        mostro.x = x;
        mostro.y = y;
        mostro.hp = 1;
        mostro.atk = 10;
        mostro.def = 1;
        mostro.mode = rand()%4;
        mostro.look = 'y';
        lista_mostri = new_monster(lista_mostri, mostro);   
        x++;
        y++;
    }
    pmon tmp =lista_mostri; 
    tmp = search_monster_by_xy(lista_mostri, 2, 3);

    cout<<lista_mostri->mon.x;
    cout<<tmp->mon.x;
}