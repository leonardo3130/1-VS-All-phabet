#pragma once
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include <ncurses.h>

#define NUM_COLORS 8

#define EXIT -3
#define IN_GAME 0
#define WIN 1
#define LOSE -1
#define GO_TO_NEXT 2
#define GO_TO_PREV -2
#define GO_TO_SHOP 3

using namespace std;

class Game {
	private:
		//WINDOW *create_new_win(int h, int w, int y, int x);
		pbul handleInput(int c, Map& map, Player& giocatore, pbul bul_list, arnd around, int& e);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y);
		void drawMonster(WINDOW* win, Map& map, pmon monster_list);
		void bulletUpdate(Map &map, pbul bul_list);
		void update(Map& map, Character& protagonist, int prev_y, int prev_x) ;
		void monsterUpdate(Map &map, pmon monster_list);
		void drawBullet(WINDOW *win, Map &map, pbul bul_list);
		void drawStats(WINDOW *win, int x, int y, Player p);
		void drawGameover(WINDOW *win, WINDOW *game_over_win);

		Map map;
		int n_mostri;
		pmon lista_mostri;

	public:
		Game(char filePath[] = NULL, int level = 1);
		int run(Player &p);
		void timed_print(char *text, int text_len, int micro_seconds_delay, int l, int c);
		void init_message();
		void game_exit();
		Map getMap();
		void setMap(Map mappa);
		pmon getListaMostri();
		void setListaMostri(pmon l);
		int getNMostri();
		void setNMostri(int n);
};
