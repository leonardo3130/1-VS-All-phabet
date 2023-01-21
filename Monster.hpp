#include "Character.hpp"
#include "Character.cpp"

class Monster : public Character{
    protected:
        int move_x; //di quando si muove in automatico a dx/sx
        int move_y; //  "                         "    su/giu
        int speed;  // ogni quanti referesh della mappa si muove
        int shot_fr; //ogni quanto spara
        int id;

    public:
        // costruttore
        Monster(int move_x = 1, int move_y = 0, int speed = 5, int shot_fr = 4, int id) : Character(x, y, '§', hp, atk, gun);  
};
