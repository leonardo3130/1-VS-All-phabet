#include "Character.hpp"
#include <ncurses.h>
#include <unistd.h>
using namespace std;

#define NUM_COLORS 8

//struct di interi necessaria a identificare ciò che si trova intorno al player
struct arnd{
    int right;
    int under;
    int left;
    int above;
};

class Player : public Character{
    protected:
        char nick[20];      //nome del player
        char psw[20];       //psw del player
        int money;          //numero di monete del giocatore
        int current_level;  //livello corrente in cui si trova il player
        int score;          //score del player
    public:
        Player();
        Player(char* nick, char* psw, char look);               //costruttore
        double fight(double m_hp, bool tur);                    //interazione tra mostro e player
        char* getNick();                                        //ritorna l'attributo nick di player
        int getMoney();                                         //ritorna l'attributo monete di player
        void pay(int p);                                        //decrementa il valore delle monete di p
        void takeMoney(int value);                              //incrementa il valore delle monete di value
        arnd check_around(Map &m);                              //ritorna una struct con 4 interi che dicono cosa si trova nelle 4 posizioni intorno al player: 0 vuoto, 1 mostro, 2 moneta
        int choice_menu();                                      //menu iniziale che ritorna se il player vuole effettuare il login, sign in o uscire dal gioco
        void getCredentials(char username[], char password[]);  //chiede all'utente di inserire username e password
        bool signIn(char *user, char *psw);                     //metoto per creare un nuovo account
        bool login(char *user, char *psw);                      //metodo per accedere ad un account già esistente
        void saveStats();                                       //salva su file le statistiche del player
        void setCurrentLevel(int l);                            //metodo che setta il livello alla quale si trova il player
        int getCurrentLevel();                                  //ritorna l'attributo current_level di player
        void incScore(int score);                               //incrementa lo score del player del valore dato
        int getScore();                                         //ritorna l'attributo score del player
        void setScore(int score);                               //setta il valore dell'attributo Score in player
};
