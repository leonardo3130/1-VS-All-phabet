#pragma once
#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include <ncurses.h>

using namespace std;

class Game {
	private:
		//WINDOW *create_new_win(int h, int w, int y, int x);
		void handleInput(int c, Map& map, Character& protagonist, Monster& mostro, Player& giocatore);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y, Monster& mostro, int prev_x_mostro, int prev_y_mostro);
		void update(Map& map, Character& protagonist, int prev_x, int prev_y, Monster& mostro, int prev_x_mostro, int prev_y_mostro) ;
	public:
		Game();
		void run();
		void timed_print(char *text, int text_len, int micro_seconds_delay, int l, int c);
		void init_message();
		void getCredentials(char* username, char* password);
		int choice_menu();
		void game_exit();
		//bool isOver();
};
