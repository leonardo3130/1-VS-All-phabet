
//gcc gioco.cpp -lncurses -o gioco

#include <ncurses.h>
#include <iostream>

using namespace std;

int main()
{	
	initscr();			        /* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			        /* Print it on to the real screen */
	getch();			        /* Wait for user input */
	endwin();			        /* End curses mode		  */

	return 0;
}
