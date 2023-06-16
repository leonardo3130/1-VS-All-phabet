#pragma once
#include <iostream>
#include <cstring>
#include "Character.hpp"
#include "Monster.hpp"
using namespace std;

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
        Player(char* nick, char* psw, char look);
        double fight(double m_hp, bool tur);                //interazione tra mostro e player
        char* getNick();
        int getMoney();
        void pay(int p);
        void takeMoney(int value);
        arnd check_around(Map &m);  //ritorna una struct con 4 interi che dicono cosa si trova nelle 4 posizioni intorno al player: 0 vuoto, 1 mostro, 2 moneta
        int choice_menu();
        void getCredentials(char username[], char password[]);
        bool signIn(char *user, char *psw);
        bool login(char *user, char *psw);
        void saveStats();
        void setCurrentLevel(int l);
        int getCurrentLevel();
        void incScore(int score);
        int getScore();
        void setScore(int score);
};
