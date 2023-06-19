#include "Player.hpp"

class Monster : public Character{
    protected:
        bool turret;

    public:
        Monster(int x = 2, int y = 3,int hp = 100, int atk = 10,int def = 10, int mode = 0, char look = 'A', bool tur = 0);     //costruttore
        void moveright(Map mappa);      //funzioni di movimento
        void moveleft(Map mappa);
        void moveup(Map mappa);
        void movedown(Map mappa);
        void move(Map& mappa, int x_p, int y_p);
        bool getTur();                  //ritorna il valore di turret
};

//codice per lista mostri
typedef struct mlist{
    Monster mon;
    int prev_x;
    int prev_y;
    mlist *next;
}* pmon;

//inserimento
pmon new_monster(pmon lista, Monster m);

//ricerca
pmon search_monster_by_xy(pmon lista_mostri, int x, int y);
