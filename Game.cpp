#include <iostream>
#include <ctime>
#include <curses.h>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Game.hpp"

Game::Game() {};

void Game::run() {

	Character protagonist(3,3,10,10,10,0,'1');
	Map map(40,80);

	initscr(); cbreak(); noecho();keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	WINDOW *game_win;

	int starty = (LINES - 40) / 2;
    int startx = (COLS - 80) / 2;

	game_win = newwin(42, 82, starty, startx);
	refresh();
	curs_set(0);
	refresh();
	for(int i = 0 ; i < map.getHeight() ; i++)
	{    
		for(int j = 0 ; j < map.getWidth() ; j++)
		{
			mvwprintw(game_win, i, j, "%c",map.getMapChar(i, j));
			wrefresh(game_win);
		}
	}

	//game loop
	bool stop = false;
	//double time = 0.0;
	time_t previous_time = time(nullptr);
	time_t lag = time_t(0.0);
	time_t current, elapsed;
	int prev_x, prev_y; 
	int const MS = 100;
	while(true) //condizione che andrà in base ad hp e altro
	{
		current = time(nullptr);
		elapsed = current - previous_time;
		previous_time = current;
		lag += elapsed;

		prev_x = protagonist.getX();
		prev_y = protagonist.getY();

		int ch = getch();
		handleInput(ch, map, protagonist);
		while(lag >= MS)
		{
			update(map, protagonist, prev_y, prev_x);
			lag -= MS;
		}
		draw(game_win, map, protagonist, prev_x, prev_y);
		//shooting
		//mostri
	}        
	getch();                                                                                                                                            
    endwin();
}

void Game::handleInput(int c, Map& map, Character& protagonist) {
	if(c == ERR) {;/*no tasti premuti dall'utente*/}
	else {
		switch(c)
		{
			case KEY_UP:
				protagonist.moveup(map);
				break;
			case KEY_DOWN:
				protagonist.movedown(map);
				break;
			case KEY_LEFT:
				protagonist.moveleft(map);
				break;
			case KEY_RIGHT: 
				protagonist.moveright(map);
				break;
			default:
				break;
		}
	}
}

void Game::update(Map& map, Character& protagonist, int prev_x, int prev_y) {
	map.setMapChar(prev_y, prev_x, ' ');
	map.setMapChar(protagonist.getY(), protagonist.getX(), protagonist.getLook());
}

void Game::draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y) {
	mvwprintw(win, prev_y, prev_x, " ");
	wrefresh(win);
	mvwprintw(win, protagonist.getY(), protagonist.getX(), "%c",protagonist.getLook());
	wrefresh(win);
}
