#include "Map.hpp"

using namespace std;

Map::Map(int h, int w, int level) {
  // controlli errori di input
  if (abs(h) > MAX_H)
    this->height = MAX_H;
  else
    this->height = abs(h);
  if (abs(w) > MAX_W)
    this->width = MAX_W;
  else
    this->width = abs(w);

  this->coins = 5 + (level / 2);

  // caratteri per i bordi della mappa
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width - 1; j++) {
      if (i == 0 || i == this->height - 1) {
        this->matrix[i][j] = '/';
        this->matrix[i][j + 1] = '/';
      } else if (j == this->width - 2) {
        this->matrix[i][j] = '/'; // bordi laterali
        this->matrix[i][j + 1] = '/';
      } else if (j == 1) {
        this->matrix[i][j] = '/'; // bordi laterali
        this->matrix[i][j - 1] = '/';
      } else
        this->matrix[i][j] = ' '; // spazi interni;
    }
  }

  // costruzione casuale mura interne alla mappa
  int walls = (this->width + this->height); // numero di muri
  int len = (walls / 8); // aumentare il denominatore per ottenere più sequenze
                         // di muri ma più brevi
  int orientation = rand() % 2;

  while (walls - len > len) {
    int add[2] = {1, -1};
    int y, x, prev_y, prev_x;
    int tmp = len;
    if (orientation)
      orientation = 0;
    else
      orientation = 1;
    while (tmp > 0) {
      // generazione posizione primo muro
      if (tmp == len) {
        do {
          y = rand() % (this->height - 10) + 5;
          x = rand() % (this->width - 10) + 5;
        } while (this->matrix[y][x] != ' ');
      } else // generazione posizione mura successive
      {
        int add_y, add_x;
        int max = 8; // diminuire per avere ancora più sequenza di mura, ma più
                     // brevi e in posizioni random
        int count = 0;
        do {
          if (count < max) {
            add_y = add[rand() % 2]; // -1 o 1
            add_x = add[rand() % 2]; // -1 o 1

            // controlli per decidere le prossime cordinate
            if (orientation) {
              y = prev_y;
              x = prev_x + add_x;
            } else {
              y = prev_y + add_y;
              x = prev_x;
            }

            // controlli per evitare di uscire dalla mappa o di andare sui bordi
            if (y <= 5 || y >= this->height - 6) {
              y = rand() % (this->height - 10) + 5;
              x = rand() % (this->width - 10) + 5;
            } else if (x <= 5 || x >= this->width - 6) {
              y = rand() % (this->height - 10) + 5;
              x = rand() % (this->width - 10) + 5;
            }
            count++;
          } else {
            y = rand() % (this->height - 10) + 5;
            x = rand() % (this->width - 10) + 5;
          }
        } while (this->matrix[y][x] != ' ');
      }

      this->matrix[y][x] = '/';
      this->matrix[y][x + 1] = '/';

      prev_y = y;
      prev_x = x;

      tmp--;
    }
    walls -= len;
  }
  // pulizia mappa
  for (int i = 1; i < this->height - 1; i++) {
    for (int j = 2; j < this->width - 2; j++) {
      if (this->matrix[i][j] == '/' && this->matrix[i][j + 1] == '/' &&
          this->matrix[i - 1][j - 1] == ' ' && this->matrix[i - 1][j] == ' ' &&
          this->matrix[i - 1][j + 1] == ' ' &&
          this->matrix[i - 1][j + 2] == ' ' && this->matrix[i][j - 2] == ' ' &&
          this->matrix[i][j - 1] == ' ' && this->matrix[i][j + 2] == ' ' &&
          this->matrix[i + 1][j - 1] == ' ' && this->matrix[i + 1][j] == ' ' &&
          this->matrix[i + 1][j + 1] == ' ' &&
          this->matrix[i + 1][j + 2] == ' ') {
        this->matrix[i][j] = ' ';
        this->matrix[i][j + 1] = ' ';
      }
    }
  }

  // aggiunta portale livello precedente
  this->matrix[2][3] = '[';
  this->matrix[2][5] = ']';
  // aggiunta portale livello successvo
  this->matrix[this->height - 3][this->width - 6] = '[';
  this->matrix[this->height - 3][this->width - 4] = ']';

  // aggiunta monete alle mappa
  int tmp_coins = this->coins;
  int coin_x, coin_y;

  while (tmp_coins > 0) {
    coin_y = rand() % (this->height - 2) + 1;
    coin_x = rand() % (this->width - 4) + 2;
    if (this->matrix[coin_y][coin_x] == ' ' &&
        this->matrix[coin_y][coin_x - 1] != '[' && coin_y != 2 &&
        coin_y != this->height - 3 && coin_x != this->width - 5) {
      this->matrix[coin_y][coin_x] = '@';
      tmp_coins--;
    }
  }
}

Map::Map(char *filename) {
  this->coins = 0;
  // setto la matrice da file
  this->readMap(filename);
}

char Map::getMapChar(int y, int x) { return this->matrix[y][x]; }

bool Map::isInside(int x, int y) {
  return (this->width - 3 >= x && x >= 2 && this->height - 2 >= y && y >= 1);
}

void Map::setMapChar(int y, int x, char c) {
  if (isInside(x, y) && (this->matrix[y][x] != '/'))
    this->matrix[y][x] = c;
}

int Map::getWidth() { return this->width; }

int Map::getHeight() { return this->height; }

bool Map::protagonistInNextPortal() {
  return this->matrix[this->height - 3][this->width - 5] == '1';
}

bool Map::protagonistInPrevPortal() { return this->matrix[2][4] == '1'; }

void Map::readMap(char *filePath) {
  // Apri il file in modalità lettura
  ifstream infile(filePath);
  this->height = 40;
  this->width = 80;

  // legge la matrice
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {

      infile >> this->matrix[i][j];

      if (this->matrix[i][j] == '#')
        this->matrix[i][j] = ' ';

      else if (this->isMoney(j, i))
        (this->coins)++;
    }
  }

  // Chiudi il file
  infile.close();
}

void Map::writeMap(int level, char *nickPlayer) {
  char filePath[50], str[10];
  strcpy(filePath, "Archivio/");
  sprintf(str, "%d", level);

  // genera la path del file da aprire:
  // Esempio Path nel caso giochi il player:"Andrea" e voglia salvare il livello
  // n:
  //  filePath = "Archivio/Andrea/Leveln.txt"
  strcat(filePath, nickPlayer);
  strcat(filePath, "/Level");
  strcat(filePath, str);
  strcat(filePath, ".txt");

  // Apri il file in modalità scrittura
  ofstream outfile(filePath);

  // Scrivi la matrice in filePath
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      if (this->matrix[i][j] == ' ' || this->matrix[i][j] == '1')
        this->matrix[i][j] = '#';

      outfile << this->matrix[i][j];
    }
    outfile << '\n';
  }

  // Chiude il file
  outfile.close();
}

bool Map::isEmpty(int x, int y) {
  return (this->matrix[y][x] == ' ' || this->matrix[y][x] == '@' ||
          this->matrix[y][x] == '*');
}

bool Map::isMoney(int x, int y) { return (this->matrix[y][x] == '@'); }

bool Map::isMonster(int x, int y) {
  return (int(this->matrix[y][x]) >= int('A') &&
          int(this->matrix[y][x]) <= int('Z')) ||
         (int(this->matrix[y][x]) >= int('a') &&
          int(this->matrix[y][x]) <= int('z'));
}

bool Map::isTurret(int x, int y) {
  return (int(this->matrix[y][x]) >= int('a') &&
          int(this->matrix[y][x]) <= int('z'));
}

bool Map::isPortal(int x, int y) {
  if (this->matrix[y][x] == '[' || this->matrix[y][x] == ']')
    return true;
  else
    return false;
}

int Map::getCoins() { return this->coins; }

void Map::setCoins(int coins) { this->coins = coins; }

// rimozione dei proiettili prima del salvataggio
void Map::clean() {
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width - 1; j++) {
      if (this->matrix[i][j] == '*')
        this->matrix[i][j] = ' ';
    }
  }
}
