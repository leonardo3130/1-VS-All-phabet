#include "Character.hpp"

Character::Character() {} // costruttore di default

Character::Character(char look) {
  this->x = 3;
  this->y = 4;
  this->look = look;
  this->hp = 10.0;
  this->atk = 5;
  this->def = 5;
};

Character::Character(int x, int y, double hp, int atk, int def, char look) {
  this->x = x;
  this->y = y;
  this->look = look;
  this->hp = hp;
  this->atk = atk;
  this->def = def;
};

void Character::moveright(Map mappa) {
  if (mappa.isEmpty((this->x) + 1, this->y) == true &&
      mappa.isInside(this->x + 1, this->y) == true) {
    this->x += 1;
  }
}
void Character::moveleft(Map mappa) {
  if (mappa.isEmpty((this->x) - 1, this->y) == true &&
      mappa.isInside((this->x) - 1, this->y) == true) {
    this->x -= 1;
  }
}
void Character::moveup(Map mappa) {
  if (mappa.isEmpty(this->x, (this->y) - 1) == true &&
      mappa.isInside(this->x, (this->y) - 1) == true) {
    this->y -= 1;
  }
}
void Character::movedown(Map mappa) {
  if (mappa.isEmpty(this->x, (this->y) + 1) == true &&
      mappa.isInside(this->x, (this->y) + 1) == true) {
    this->y += 1;
  }
}

int global_blt_id = 0;        // da inizializzare nel main
pbul lista_proiettili = NULL; //  "   "

pbul Character::fire(pbul ls_proiettili, Map &map, int dir, bool from) {
  Bullet nuovo_proiettile;
  if (dir == 0 && map.isEmpty(this->x + 1, this->y) &&
      !map.isMoney(this->x + 1, this->y)) {
    nuovo_proiettile = Bullet(this->x + 1, this->y, dir, '*', from);
  } else if (dir == 1 && map.isEmpty(this->x, this->y + 1) &&
             !map.isMoney(this->x, this->y + 1)) {
    nuovo_proiettile = Bullet(this->x, this->y + 1, dir, '*', from);
  } else if (dir == 2 && map.isEmpty(this->x - 1, this->y) &&
             !map.isMoney(this->x - 1, this->y)) {
    nuovo_proiettile = Bullet(this->x - 1, this->y, dir, '*', from);
  } else if (dir == 3 && map.isEmpty(this->x, this->y - 1) &&
             !map.isMoney(this->x, this->y - 1)) {
    nuovo_proiettile = Bullet(this->x, this->y - 1, dir, '*', from);
  }

  ls_proiettili = new_bullet(ls_proiettili, nuovo_proiettile);
  return ls_proiettili;
}

void Character::SetHp(double hp) { this->hp = hp; }

void Character::incHP(double n) { this->hp += n; }

void Character::incAtk(int n) { this->atk += n; }

void Character::incDef(int n) { this->def += n; }

double Character::getHp() { return this->hp; };

int Character::getDef() { return this->def; }

int Character::getAtk() { return this->atk; }

int Character::getX() { return this->x; }

int Character::getY() { return this->y; }

void Character::setX_Y(int x0, int y0) { this->x = x0, this->y = y0; }

char Character::getLook() { return this->look; }

void Character::setLook(char look) { this->look = look; }
