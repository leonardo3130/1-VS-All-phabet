#include <cmath>
#include <ctime>

#define MAX_H 40
#define MAX_W 80
#pragma once 

class Map {
        protected:
                int height;
                int width;
                char matrix[MAX_H][MAX_W];
        public:
                Map(int h, int w);
                char getMapChar(int y, int x);
                int getWidth();
                int getHeight();
};

