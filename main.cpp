#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>

#include "Character.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Game.hpp"

#define NUM_COLORS 8
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
bool signIn(char *psw, char *filename){
	bool isCorrect = false;

	//scrivo nel file delle credenziali le informazioni degli utenti
	ofstream credenziali;
	credenziali.open(filename);
	credenziali << psw << endl;

	Character c = Character('1');
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
	bool exists;

    if (input_file.is_open()) {
		//leggo la psw
        char line[50];
		input_file >> line;

		//se la psw è giusta prendo le informazioni del player
		if(strcmp(line, psw) == 0)	{
			input_file >> hp;
			input_file >> atk;
			input_file >> def;
			input_file >> money;
			exists = true;

			//Character c = Character(100, 100, '1', hp, atk, def);
			//Player p = Player(user, psw, money, c);
		}else {
			//Password errata
            attron(COLOR_PAIR(COLOR_RED));
            mvprintw(LINES/2 + 3, COLS/2 - 14, "Wrong password!");
            attroff(COLOR_PAIR(COLOR_RED));
			exists = false;
		}

    } else {
        // Il file non esiste
        attron(COLOR_PAIR(COLOR_RED));
        mvprintw(LINES/2 + 3, COLS/2 - 14, "Wrong username!");
        attroff(COLOR_PAIR(COLOR_RED));
		exists = false;
    }
	return exists;
}


int main(){
	srand(time(NULL));

	// Inizializzazione della libreria ncurses
	initscr();cbreak();noecho();

	//inizio game + messaggio iniziale (grafica)
	Game game = Game();
	game.init_message();
	clear();

	//vedo se il giocatore desidera effetuare il login (0), registrarsi (1) o uscire (2)
	int choice = 1; //game.choice_menu();
	clear();

/*
	char username[20], password[20], filename[50], mkdir[50];
	strcpy(mkdir, "mkdir Archivio/");
	bool correct_input = false;

	//scrivo in filename la path per raggiungere le credenziali
	while(!correct_input){
		if(choice <= 1){
			game.getCredentials(username, password);
			strcpy(filename, "Archivio/");
			strcat(filename, username);
			strcat(filename, "/credentials.txt");
		}
		switch(choice){
			case 0:
                correct_input = login(username, password, filename);
                break;
            case 1:
                //creo la cartella per salvare i file di gioco del giocatore (rinominata col suo nome)
                system(strcat(mkdir, username));
                correct_input = signIn(password, filename);
                break;
            case 2:
                game.game_exit();
                break;
            default:
                break;

        }
	}
	*/

	if(choice <= 1){
		game.run();
	}
	return 0;
}
