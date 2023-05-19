#pragma once
#include <cmath>
#include <ctime>
#include <fstream>

#define MAX_H 40
#define MAX_W 80

class Map {
        protected:
                int height;
                int width;
                char matrix[MAX_H][MAX_W];
                int coins = 5;
        public:
                Map(int h = 40, int w = 80, int l = 1);
                Map(char *filename);

                char getMapChar(int y, int x);
                void setMapChar(int y, int x, char c);
                int getWidth();
                int getHeight();
                int getCoins();
                void setCoins(int coins);
		void readMap(char *filePath);
		void writeMap(int level, char *nickPlayer);
                bool is_inside(int x, int y);   //dice se la cella (x,y) e' nella mappa
                bool isEmpty(int x, int y);     //dice se la cella (x,y) e' vuota
                bool isMoney(int x, int y);
                bool isMonster(int x, int y);
                bool isPortal(int x, int y);
                bool freeWay(int x1, int y1, int x2, int y2);
                void clean();
                bool protagonistInNextPortal();
                bool protagonistInPrevPortal();
};
