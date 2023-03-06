//gcc gioco.cpp -lncurses -o gioco

//#include <ncurses.h>
#include <iostream>
#include "Map.hpp"
#include "Player.hpp"
using namespace std;

typedef struct livelli{
	int n;			//numero livello;
	Map mappa;		//matrice della mappa
	livelli *next;	//livello successivo
	livelli *prev;	//livello precedente
}* ptr_livelli;

struct Session{
	Player p;			//giocatore in gioco
	ptr_livelli liv;	//livelli affrontati 
};




bool signIn(){
	bool isCorrect = false;
	char usernames[20];
	char psw[20];

	


	return isCorrect;
}

int main()
{	

	//inizio Login o Creazione account
	bool correct_input = false;
	char scelta = ' '; 
	cout << "In qualsiasi momento permi E/e per uscire.\n";
	cout << "Benvenuto nel gioco premi \"L/l\" per loggarti o \"C/c\" per creare un account: ";
	do{
		cin >> scelta;
		if(scelta ==  'L' || scelta == 'l'){
			//login



			correct_input = true;
		}else if(scelta == 'C' || scelta == 'c'){
			//crea account



			correct_input = true;
		}else if(scelta == 'E' || scelta == 'e'){
			//termina partita
			exit(0);
		}else {
			cout << "Carattere errato. Premi \"L/l\" per loggarti o \"C/c\" per creare un account: ";
		}

	}while(!correct_input);

	/*
	initscr();			        // Start curses mode
	printw("Hello World !!!");	// Print Hello World
	refresh();			        // Print it on to the real screen
	getch();			        // Wait for user input
	endwin();			        // End curses mode

	*/

	return 0;

}
