#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include <ncurses.h>


using namespace std;

class Game {
	private:
		WINDOW *create_new_win(Map map, int h, int w, int y, int x); 
	public:
		Game();
		void run();
		//bool isOver();
};
