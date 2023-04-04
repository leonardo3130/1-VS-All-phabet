#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <curses.h>

Game::Game() {}

void Game::run() {
	Map map(40,80);
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
	//game loop
	bool stop = false;
	while(!stop) 
	{
		char ch = getch();
		for(int i = 0 ; i < map.getHeight() ; i++)
		{    
			for(int j = 0 ; j < map.getWidth() ; j++)
			{
				mvwprintw(game_win, i, j, "%c",map.getMapChar(i, j));
				wrefresh(game_win);
			}
		}
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
				stop = true;
				break;
			
		}
		wrefresh(game_win);
		napms(100);
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

