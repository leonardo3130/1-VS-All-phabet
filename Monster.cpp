#include <iostream>
#include <cstring>

#include "Monster.hpp"

using namespace std;

//costruttore
Monster::Monster(int move_x, int move_y, int speed, int shot_fr, int id) : Character(x, y, '§', hp, atk, gun) {
    this->move_x = move_x;
    this->move_y = move_y;
    this->speed = speed;
    this->shot_fr = shot_fr;
    this->id = id;
};



