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
                Map(int h = 40, int w = 80);
                char getMapChar(int y, int x);
                void setMapChar(int y, int x, char c);
                int getWidth();
                int getHeight();
                int getCoins();
                void setCoins(int coins);
		void readMap(int level, char* nickPlayer);
		void writeMap(int level, char* nickPlayer);
                bool is_inside(int x, int y);   //dice se la cella (x,y) e' nella mappa
                bool isempty(int x, int y);     //dice se la cella (x,y) e' vuota
                bool ismoney(int x, int y);
                bool isportale(int x, int y);
                bool freeWay(int x1, int y1, int x2, int y2);
                bool protagonistInNextPortal();
                bool protagonistInPrevPortal();
};

