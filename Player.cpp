#include "Player.hpp"
#include "Monster.hpp"

Player::Player(char* nick, char* psw, int m, char l) : Character(l){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
    this->money = m;
}

/*
pmon Player::fight(arnd around, pmon monster_list){
    if(around.right == )
    this->hp -= 1*(pl.atk)/(this->def);
    pl.hp -= 1*(this->def)/(pl.def);
}*/

arnd Player::check_around(Map& m){  
    arnd around;    //0 vuoto, 1 mostro, 2 moneta
    char x;

    x = m.getMapChar(this->y, (this->x) + 1);
    if(x == ' ')
        around.right = 0;
    else if(x >= 'A' && x <= 'Z')
        around.right = 1;
    else if(x == '@')
        around.right = 2;


    x =m.getMapChar((this->y) + 1, this->x);
    if(x == ' ')
        around.under = 0;
    else if(x >= 'A' && x <= 'Z')
        around.under = 1;
    else if(x == '@')
        around.under = 2;
    

    x = m.getMapChar(this->y, (this->x) - 1);
    if(x == ' ')
        around.left = 0;
    else if(x >= 'A' && x <= 'Z')
        around.left = 1;
    else if(x == '@')
        around.left = 2;


    x = m.getMapChar((this->y) - 1, this->x);
    if(x == ' ')
        around.above = 0;
    else if(x >= 'A' && x <= 'Z')
        around.above = 1;
    else if(x == '@')
        around.above = 2;


    return around;
}

char* Player::getNick(){
    return this->nick;
}

int Player::getMoney(){
    return this->money;
}

void Player::takeMoney(int value){
    this->money = money + value;
}

