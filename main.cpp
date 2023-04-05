//gcc gioco.cpp -lncurses -o gioco

//#include <ncurses.h>
#include <iostream>
#include <fstream>

#include "Map.hpp"
#include "Player.hpp"
#include "Game.hpp"

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

//funzione per creare un nuovo account
bool signIn(char *psw, char character, char *filename){
	bool isCorrect = false;

	//scrivo nel file delle credenziali le informazioni degli utenti
	ofstream credenziali;
	credenziali.open(filename);
	credenziali << psw << endl;
	credenziali << character << endl;

	Character c = Character(character);
	credenziali << c.getHp() << endl;
	credenziali << c.getAtk() << endl;
	credenziali << c.getDef() << endl;
	credenziali << 100 << endl;		//default money

	credenziali.close();
	isCorrect = true;
	return isCorrect;
}

//funzione per effettuare il login ad un account esistente
bool login(char *user, char *psw, char *filename){
	ifstream input_file(filename);
	int hp = 0, atk = 0, def = 0, money = 0;
	char ch;

	bool exists;
    if (input_file.is_open()) {
		//leggo la psw
        char line[50];
		input_file >> line;

		//se la psw è giusta prendo le informazioni del player
		if(strcmp(line, psw) == 0)	{

			input_file >> ch;
			input_file >> hp;
			input_file >> atk;
			input_file >> def;
			input_file >> money;
			exists = true;

			Character c = Character(100, 100, ch, hp, atk, 0, def);
			Player p = Player(user, psw, money, c);
		}else {
			cout << "Password errata.\n";
			exists = false;
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

	char username[20] = "Tizio";	//nome default

	char psw[20];
	char character;

	cout << "Benvenuto nel gioco premi: \n  -\"L/l\" per loggarti \n  -\"C/c\" per creare un account \n  -\"E/e\" per uscire \nScelta: ";
	cin >> scelta;
	do{
		char filename[31] = "Archivio/";
		if(scelta ==  'L' || scelta == 'l'){
			//login
			cout << "Username: ";
			cin >> username;
			strcat(filename, username);
			strcat(filename, "/credentials.txt");

			cout << filename <<" Password: ";
			cin >> psw;

			correct_input = login(username, psw, filename);
		}else if(scelta == 'C' || scelta == 'c'){
			//crea account
			cout << "Username: ";
			cin >> username;
			char mkdir[50] = "mkdir Archivio/";
			system(strcat(mkdir, username));
			strcat(filename, username);
			strcat(filename, "/credentials.txt");

			cout << filename <<" Password: ";
			cin >> psw;

			cout << "Carattere da usare in game: ";
			cin >> character;

			correct_input = signIn(psw, character, filename);

		}else if(scelta == 'E' || scelta == 'e'){
			//termina partita
			exit(0);
		}else {
			bool ctrl = false;
			while(scelta != 'E' && scelta != 'e' &&	 scelta != 'L' && scelta != 'l' && scelta != 'C' && scelta != 'c'){
				cout << "Carattere errato, ";
				cout << "premi: \n  -\"L/l\" per loggarti \n  -\"C/c\" per creare un account \n  -\"E/e\" per uscire \nScelta: ";
				cin >> scelta;
			}
		}

	}while(!correct_input);
	cout << "--Inizio partita (da fare)\n" ;
	//INIZIALIZZAZIONE LIVELLI +
	/*
	initscr();			        // Start curses mode
	printw("Hello World !!!");	// Print Hello World
	refresh();			        // Print it on to the real screen
	getch();			        // Wait for user input
	endwin();			        // End curses mode

	*/
	Game game = Game();
	game.run();
	return 0;
}
