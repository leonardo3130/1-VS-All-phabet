#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <curses.h>

Game::Game() {};

void Game::run(Map& map) {
	Character protagonist(3, 3, 10, 5, 5, 0, '1');
	WINDOW *game_win;

	initscr();
         
    int starty = (LINES - 40) / 2;
    int startx = (COLS - 80) / 2;
	
	cbreak();
	noecho();
	nonl();

	
	keypad(stdscr, TRUE);
	game_win = create_new_win(map, 40, 80, starty, startx);
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
	while(true) 
	{
		int prev_x = protagonist.getX();
		int prev_y = protagonist.getY();
		char ch = getch();
		switch(ch)
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
		mvwprintw(game_win, protagonist.getY(), protagonist.getX(), "%c",protagonist.getLook());
		mvwprintw(game_win, prev_y, prev_x, " ");
		wrefresh(game_win);
		//napms(100);
	}
	getch();                                                                                                                                                       
    endwin();
}

WINDOW* Game::create_new_win(Map map, int h, int w, int y, int x)
{	WINDOW *local_win;

	local_win = newwin(h, w, y, x);
	//box(local_win, 0 , 0);		/* 0, 0 gives default characters 
	//				 * for the vertical and horizontal
	//				 * lines			*/
	
	return local_win;
} //newwin

