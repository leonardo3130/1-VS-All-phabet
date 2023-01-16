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
        double speed; //velocità in secondi (ogni quanti secondi il proiettile si muove di una cella)
        int x; //posizione di partenza del poriettile
        int y;
        char look;
    public:
        Bullet(double s = 0.3, int x, int y, char look = '.');
        Shot(int mode = 1, Map Mappa, Player p);
}

