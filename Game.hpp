#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include <ncurses.h>


using namespace std;

class Game {
	private:
		//WINDOW *create_new_win(int h, int w, int y, int x); 
		void handleInput(int c, Map& map, Character& protagonist);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y);
		void update(Map& map, Character& protagonist, int prev_x, int prev_y);
	public:
		Game();
		void run();
		//bool isOver();
};
