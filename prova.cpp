#include <iostream>

#include "Bullet.hpp"

using namespace std;

int main(){
    pbul lista = NULL;
    Bullet bul(6, 7, 0, '*');
    lista = new_bullet(lista, bul);

    pbul tmp = lista;
        while(tmp != NULL){
        cout<<"o";
        tmp->prev_x = tmp->bul.x;
        tmp->prev_y = tmp->bul.y;
        tmp = tmp->next;
    }
    //lista = remove_bullet(lista, 6, 7, 0);
    pbul tmp1= lista;

    
    while(tmp1 != NULL){
        tmp1->bul.x += 1;
        tmp1->bul.y += 1;
        tmp1 = tmp1->next;
    }
    
    pbul tmp3 = lista;
    
    while(tmp3 != NULL){
        cout<<"c"<<endl;
        cout<<tmp3->prev_x<<endl<<tmp3->bul.x<<endl;
        tmp3 = tmp3->next;    
    }


    pbul tmp2 = lista, tmp_e = lista, tmp_s = lista;
    pbul lista_nera = NULL; //priettili da eliminare;
    
    while(tmp2 != NULL){
        bool collision = 0;
        collision = 1; //tmp2->bul.move_bul(map); //collision per riciclare i controlli che vengono eseguiti in move_bul
        if(collision == 1){
            lista_nera = new_bullet(lista_nera, tmp2->bul);
            cout<<lista_nera->bul.x;
        }
        tmp2 = tmp2->next;
    }
    
    while(lista_nera != NULL){
        while(tmp_e != NULL){
            cout<<"f"<<endl;
            if( lista_nera->bul.x == tmp_e->bul.x &&
                lista_nera->bul.y == tmp_e->bul.y &&
                lista_nera->bul.dir == tmp_e->bul.dir   ){
                    cout<<"x"<<endl;
                    tmp_s = remove_bullet(tmp_e, tmp_e->bul.x, tmp_e->bul.y, tmp_e->bul.dir);
            }
            tmp_e = tmp_e->next;
        }
        lista_nera = lista_nera->next;
    }
    while(lista_nera!=NULL){
        cout<<"y"<<endl;
        lista_nera = lista_nera->next;
    }
    lista = tmp_s;
    pbul tmperino = lista;
    while (tmperino!=NULL){
        cout<<"t"<<endl;
        tmperino = tmperino->next;
    }
    //delete lista_nera;





    

}