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
		void handleInput(int c, Map& map, Character& protagonist, Monster& mostro, Player& giocatore, Bullet& proiettile);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y);
		void drawMonster(WINDOW* win, Map& map, Monster& mostro, int prev_x_mostro, int prev_y_mostro);
		void bulletUpdate(Map &map, Bullet& proiettile, int prev_x_bul, int prev_y_bul);
		void update(Map& map, Character& protagonist, int prev_x, int prev_y) ;
		void monsterUpdate(Map &map, Monster& mostro, int prev_x_mostro, int prev_y_mostro);
		void drawBullet(WINDOW* win, Map& map, Bullet& proiettile, int prev_x_bul, int prev_y_bul);
	public:
		Game();
		void run();
		void timed_print(char *text, int text_len, int micro_seconds_delay, int l, int c);
		void init_message();
		void getCredentials(char* username, char* password);
		int choice_menu();
		void game_exit();
		void muovi_mostro(Map& mappa, Monster& m, Player& p);
		//bool isOver();
};
