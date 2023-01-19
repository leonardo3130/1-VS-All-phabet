#include <iostream>
#include <ctime>
#include "Character.hpp"
#include "Character.cpp"
#include "Player.hpp"
#include "Player.cpp"
#include "map.hpp"
using namespace std;

class Bullet{
    protected:
        double speed; //velocità: 1 corrisponde al movimento di una cella al secondo, la formula dell'intervallo di movimento è (1 sec) / (speed)
        int x; //posizione di partenza del poriettile
        int y;
        char look;
    public:
        Bullet(double speed = 1, Character personaggio, char look = '.'); 
        void shot(int mode = 1, Map Mappa, Player p); // !!! il metodo shot richiede "<<flush" quando si stampa la mappa, altrimenti non funziona il conteggio dei secondi pe rla velocità
}

