#include <ctime>
#include <cstring>
#include <fstream>

#define MAX_H 40
#define MAX_W 80

class Map {
        protected:
                int height;                                     //altezza mappa
                int width;                                      //larghezza mappa
                char matrix[MAX_H][MAX_W];                      //mappa sotto forma di matrice
                int coins = 5;                                  //numero di monete generate nella mappa
        public:
                Map(int h = 40, int w = 80, int l = 1);         //costruttore 
                Map(char *filename);                            //costruttore da file

                char getMapChar(int y, int x);                  //ottiene il carattere alla posizione (x,y)
                void setMapChar(int y, int x, char c);          //setta il carattere alla posizione (x,y)
                int getWidth();                                 //ritorna la larghezza della mappa
                int getHeight();                                //ritorna l'altezza della mappa
                int getCoins();                                 //ritorna il numero di monete rimanenti
                void setCoins(int coins);                       //setta il numero di monete rimanenti
		void readMap(char *filePath);                   //lettura mappa da file
		void writeMap(int level, char *nickPlayer);     //scrittura mappa da file
                bool isEmpty(int x, int y);                     //dice se la cella (x,y) è vuota, proiettile o moneta
                bool isMoney(int x, int y);                     //dice se la cella (x,y) è una moneta
                bool isMonster(int x, int y);                   //dice se la cella (x,y) è un mostro
                bool isTurret(int x, int y);                    //dice se la cella (x,y) è una torretta
                bool isPortal(int x, int y);                    //dice se la cella (x,y) è un portale
                bool isInside(int x, int y);                    //dice se la cella (x,y) è nel range dei possibili valori
                void clean();                                   //al momento del salvataggio della mappa rimuove i proiettili dalla mappa
                bool protagonistInNextPortal();                 //controlla che il player sia nel portale per andare al livello successivo
                bool protagonistInPrevPortal();                 //controlla che il player sia nel portale per andare al livello precedente
};
