#include "Character.hpp"
#include "Character.cpp"

class Player : public Character{
    protected:
        char nick[20];  //nome del player
        int def;        //valore difesa

    public:
        // costruttore
        Player(char nick[], int def = 2);

        //mancano metodi getter e setter
        void setHp(int new_hp);
        int getHp();
        
};
