//gcc gioco.cpp -lncurses -o gioco

//#include <ncurses.h>
#include <iostream>
#include <fstream>

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




bool signIn(char *psw, char character, char *filename){
	bool isCorrect = false;

	ofstream credenziali;
	credenziali.open(filename);
	credenziali << psw << endl;
	credenziali << character << endl;

	Character c = Character(character);
	credenziali << c.getHp() << endl;
	credenziali << c.getDef() << endl;
	credenziali << c.getAtk() << endl;
	credenziali << 100 << endl;		//default money

	credenziali.close();
	isCorrect = true;

	return isCorrect;
}

bool login(char *psw, char *filename){
	ifstream input_file(filename);

	bool exists;
    if (input_file.is_open()) {

		//leggo la psw
        char line[256];
		input_file >> line;
        char var1[50];
		strcpy(var1, line);

		//se la psw è giusta
		if(strcmp(var1, psw) == 0)	{
			input_file >> line;
			char var2[50];
			strcpy(var2, line);

			input_file >> line;
			char var3[50];
			strcpy(var3, line);

			input_file >> line;
			char var4[50];
			strcpy(var4, line);

			input_file >> line;
			char var5[50];
			strcpy(var5, line);

			exists = true;
		}


    } else {
        // Il file non esiste
		exists = false;
        cout << "Giocatore non esistente.\n";
    }
	return exists;
}

int main(){
	//inizio Login o Creazione account
	bool correct_input = false;
	char scelta = ' ';

	char username[20] = "Tizio";
	char filename[31] = "Archivio/";
	char psw[20];
	char character;

	cout << "In qualsiasi momento permi E/e per uscire.\n";
	cout << "Benvenuto nel gioco premi \"L/l\" per loggarti o \"C/c\" per creare un account: ";
	do{
		cin >> scelta;
		if(scelta ==  'L' || scelta == 'l'){
			//login
			cout << "Username: ";
			cin >> username;
			strcat(filename, username);
			strcat(filename, "/credentials.txt");

			cout << "Password: ";
			cin >> psw;

			correct_input = login(psw, filename);
		}else if(scelta == 'C' || scelta == 'c'){
			//crea account
			cout << "Username: ";
			cin >> username;
			strcat(filename, username);
			strcat(filename, "/credentials.txt");

			cout << "Password: ";
			cin >> psw;

			cout << "Carattere da usare in game: ";
			cin >> character;

			correct_input = signIn(psw, character, filename);

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
