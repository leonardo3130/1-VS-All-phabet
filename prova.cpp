#include <iostream>

#include "Bullet.hpp"

using namespace std;

int main(){
    pbul lista = NULL;
    Bullet bul(2, 3, 4, 0, 0, '*');
    lista = new_bullet(lista, bul);

    pbul tmp = lista;
        while(tmp != NULL){
        cout<<"ciao luca";
        tmp->prev_x = tmp->bul.x;
        tmp->prev_y = tmp->bul.y;
        tmp = tmp->next;
    }
        pbul tmp1= lista;
   
    while(tmp1 != NULL){
        tmp1->bul.x += 1;
        tmp1->bul.y += 1;
        tmp1 = tmp1->next;
    }
    
    pbul tmp2 = lista;
    
    while(tmp2 != NULL){
        cout<<"ciao mare"<<endl;
        cout<<tmp2->prev_x<<endl<<tmp2->bul.x<<endl;
        tmp2 = tmp2->next;    
    }



    

}