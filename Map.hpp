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
                Map(int h, int w);
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
};

