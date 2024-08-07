#include "Monster.hpp"
#include <cmath>
#include <ncurses.h>
#include <unistd.h>

Monster::Monster(int x, int y, int hp, int atk, int def, char look, bool tur)
    : Character(x, y, hp, atk, def, look) {
  this->turret = tur;
};

// metodi movimento modificati in modo che non si sovrappongano due mostri
void Monster::moveright(Map mappa) {
  if (!mappa.isMonster((this->x) + 2, this->y) &&
      !mappa.isMonster((this->x) + 1, (this->y) + 1) &&
      !mappa.isMonster((this->x) + 1, (this->y) - 1))
    Character::moveright(mappa);
}

void Monster::moveleft(Map mappa) {
  if (!mappa.isMonster((this->x) - 2, this->y) &&
      !mappa.isMonster((this->x) - 1, (this->y) + 1) &&
      !mappa.isMonster((this->x) - 1, (this->y) - 1))
    Character::moveleft(mappa);
}

void Monster::moveup(Map mappa) {
  if (!mappa.isMonster(this->x, (this->y) - 2) &&
      !mappa.isMonster((this->x) + 1, (this->y) - 1) &&
      !mappa.isMonster((this->x) - 1, (this->y) - 1))
    Character::moveup(mappa);
}

void Monster::movedown(Map mappa) {
  if (!mappa.isMonster(this->x, (this->y) + 2) &&
      !mappa.isMonster((this->x) + 1, (this->y) + 1) &&
      !mappa.isMonster((this->x) - 1, (this->y) + 1))
    Character::movedown(mappa);
}

void Monster::move(Map &mappa, int x_p, int y_p) {
  // mode determina la direzione di spostamento: 0=right  1=down  2=left  3=up
  int mode;

  if (abs(this->x - x_p) < abs(this->y - y_p) && this->x != x_p) {
    if (this->x < x_p)
      mode = 0;
    else
      mode = 2;
  } else if (abs(this->x - x_p) > abs(this->y - y_p) && this->y != y_p) {
    if (this->y < y_p)
      mode = 1;
    else
      mode = 3;
  } else if (this->x == x_p) {
    if (this->y < y_p)
      mode = 1;
    else
      mode = 3;
  } else if (this->y == y_p) {
    if (this->x < x_p)
      mode = 0;
    else
      mode = 2;
  }

  if (mode == 0) {
    if (mappa.isEmpty(this->x + 1, this->y) &&
        !mappa.isMoney(this->x + 1, this->y))
      this->moveright(mappa);
    else if (mappa.isEmpty(this->x, this->y - 1) &&
             !mappa.isMoney(this->x, this->y - 1))
      this->moveup(mappa);
  } else if (mode == 1) {
    if (mappa.isEmpty(this->x, this->y + 1) &&
        !mappa.isMoney(this->x, this->y + 1))
      this->movedown(mappa);
    else if (mappa.isEmpty(this->x + 1, this->y) &&
             !mappa.isMoney(this->x + 1, this->y))
      this->moveright(mappa);
  } else if (mode == 2) {
    if (mappa.isEmpty(this->x - 1, this->y) &&
        !mappa.isMoney(this->x - 1, this->y))
      this->moveleft(mappa);
    else if (mappa.isEmpty(this->x, this->y + 1) &&
             !mappa.isMoney(this->x, this->y + 1))
      this->movedown(mappa);
  } else if (mode == 3) {
    if (mappa.isEmpty(this->x, this->y - 1) &&
        !mappa.isMoney(this->x, this->y - 1))
      this->moveup(mappa);
    else if (mappa.isEmpty(this->x - 1, this->y) &&
             !mappa.isMoney(this->x - 1, this->y))
      this->moveleft(mappa);
  }
}

bool Monster::getTur() { return this->turret; }

pmon new_monster(pmon lista, Monster m) {
  pmon tmp = new mlist;
  tmp->mon = m;
  tmp->next = lista;
  lista = tmp;
  return lista;
}

pmon search_monster_by_xy(pmon lista_mostri, int x, int y) {
  pmon tmp = lista_mostri;
  bool found = false;
  while (!found && tmp != NULL) {
    if (tmp->mon.getX() == x && tmp->mon.getY() == y)
      found = true;
    else
      tmp = tmp->next;
  }
  return tmp;
}
