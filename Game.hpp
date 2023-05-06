#pragma once
#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include <ncurses.h>

#define NUM_COLORS 8

#define IN_GAME 0
#define WIN 1
#define LOSE -1
#define GO_TO_NEXT 2
#define GO_TO_PREV -2

using namespace std;

typedef struct Session{
	Player p;			//giocatore in gioco
	int curr_level;		//livello corrente in cui si trova il player
}* p_session;



class Game {
	private:
		//WINDOW *create_new_win(int h, int w, int y, int x);
		pbul handleInput(int c, Map& map, pmon lista_mostri,Player& giocatore, pbul bul_list, arnd around);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y);
		void drawMonster(WINDOW* win, Map& map, pmon monster_list);
		void bulletUpdate(Map &map, pbul bul_list);
		void update(Map& map, Character& protagonist, int prev_y, int prev_x) ;
		void monsterUpdate(Map &map, pmon monster_list);
		void drawBullet(WINDOW *win, Map &map, pbul bul_list);
		void drawStats(WINDOW *win, int x, int y, p_session Sessione);
		void drawGameover(WINDOW *win, WINDOW *game_over_win);
	protected:
		Map map;
	public:
		Game();
		int run(p_session Sessione);
		void timed_print(char *text, int text_len, int micro_seconds_delay, int l, int c);
		void init_message();
		void getCredentials(char* username, char* password);
		int choice_menu();
		void game_exit();
		//void muovi_mostro(Map& mappa, Monster& m, Player& p);
		//bool isOver();
};
