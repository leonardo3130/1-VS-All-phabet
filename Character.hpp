#include "Bullet.hpp"

class Character{
  protected:
    int x;        //coordinata x
    int y;        //coordinata y
    double hp;    //healt points
    int atk;      //attacco (contatto)
    int def;      //difesa
    char look;    //lettera usata per identificare il personaggio

  public:
    Character();          //costruttore di default
    Character(char look); //costruttore
    Character(int x, int y, double hp, int atk, int def, char look); //costruttore
    void setX_Y(int x0, int y0);                                    //setta il valore delle due coordinate
    void moveright(Map mappa);                                      //muove a dx
    void moveleft(Map mappa);                                       //muove a sx
    void moveup(Map mappa);                                         //muove su
    void movedown(Map mappa);                                       //muove giu
    pbul fire(pbul ls_proiettili, Map& map, int dir, bool from);    //funzione spara
    int getX();                                                     //ritorna valore della coordinata x
    int getY();                                                     //ritorna valore della coordinata y
    void SetHp(double hp);                                          //setta la vita
    double getHp();                                                 //ottiene la vita
    void incHP(double n);                                           //aumento della vita
    int getAtk();                                                   //ritorna valore di attacco
    void incAtk(int n);                                             //aumenta il valore di attacco
    int getDef();                                                   //ritorna valore di difesa
    void incDef(int n);                                             //aumenta il valore di difesa
    char getLook();                                                 //ritorna il carattere che rappresenta il Character
    void setLook(char look);                                        //imposta il carattere che rappresenta il Character
};
