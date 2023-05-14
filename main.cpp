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

typedef struct livello{
	int n_liv;		// numero livello;
	Game partita;	// partita
	livello *next;	// livello successivo
	livello *prev;	// livello precedente
}* ptr_livelli;


//crea un nuovo livello e ritorna il puntatore a quest'ultimo
ptr_livelli new_level(ptr_livelli l, Player p){
	char filePath[50] , str[10];
	strcpy(filePath, "Archivio/");
	sprintf(str, "%d", p.getCurrentLevel() );

	//genera la path del file da aprire:
	//Esempio Path nel caso giochi il player:"Andrea" e voglia salvare il livello n:
	// filePath = "Archivio/Andrea/Leveln.txt"
	strcat(filePath, p.getNick());
	strcat(filePath, "/Level");
	strcat(filePath, str);
	strcat(filePath, ".txt");

	if(l == NULL) {
		l = new livello;
		l->next = NULL;
		l->prev = NULL;
		l->partita = Game(filePath, p.getCurrentLevel());

		l->n_liv = p.getCurrentLevel();
		return l;
	}
	else {
		ptr_livelli new_l = new livello;
		l->next = new_l;
		new_l->next = NULL;
		new_l->prev = l;
		new_l->partita = Game(filePath, p.getCurrentLevel());
		new_l->n_liv = p.getCurrentLevel();
		return new_l;
	}
}

void shop(Player &p){
	clear();
	WINDOW *shop;

	int starty = (LINES - 42) / 2, startx = (COLS - 82) / 2, highlights = 0, choice = 0;
	int prezzi[3] = {5, 5, 5};

	shop = newwin(42, 82, starty, startx);
	box(shop, 0, 0);
	refresh();
    wrefresh(shop);


	mvwprintw(shop, 16, 20, "  //\\\\");
	mvwprintw(shop, 17, 20, "  |- |");
	mvwprintw(shop, 18, 20, "  |- |");
	mvwprintw(shop, 19, 20, "  |- |");
	mvwprintw(shop, 20, 20, "  |  |");
	mvwprintw(shop, 21, 20, "__|__|__");
	mvwprintw(shop, 22, 20, "\\_\\<>/_/");
	mvwprintw(shop, 23, 20, "   ||");

	mvwprintw(shop, 16, 35, " _____________");
	mvwprintw(shop, 17, 35, "|             |");
	mvwprintw(shop, 18, 35, "|     DEF     |");
	mvwprintw(shop, 19, 35, "|             |");
	mvwprintw(shop, 20, 35, " |           |");
	mvwprintw(shop, 21, 35, "  |         |");
	mvwprintw(shop, 22, 35, "   |       |");
	mvwprintw(shop, 23, 35, "    |_____|");

	mvwprintw(shop, 16, 55, " ___    ___");
	mvwprintw(shop, 17, 55, "/   \\  /   \\");
	mvwprintw(shop, 18, 55, "\\    \\/    /");
	mvwprintw(shop, 19, 55, " \\        /");
	mvwprintw(shop, 20, 55, "  \\  HP  /");
	mvwprintw(shop, 21, 55, "   \\    /");
	mvwprintw(shop, 22, 55, "    \\  /");
	mvwprintw(shop, 23, 55, "     \\/");

	keypad(shop, true);
	while (choice != 'q'){
		mvwprintw(shop, 2, 60, " Monete : %d     ", p.getMoney());
		mvwprintw(shop, 4, 60, "   Vita : %.*f     ", p.getHp(), 2);
		mvwprintw(shop, 6, 60, "Attacco : %d     ", p.getAtk());
		mvwprintw(shop, 8, 60, " Difesa : %d     ", p.getDef());

		if(highlights == 0) wattron(shop, A_REVERSE);
			mvwprintw(shop, 27, 21, "+2 ATK");
        if(highlights == 0) wattroff(shop, A_REVERSE);
		mvwprintw(shop, 28, 23, "%d @", prezzi[highlights]);

        if(highlights == 1) wattron(shop, A_REVERSE);
			mvwprintw(shop, 27, 40, "+2 DEF");
        if(highlights == 1) wattroff(shop, A_REVERSE);
		mvwprintw(shop, 28, 42, "%d @", prezzi[highlights]);

        if(highlights ==2)  wattron(shop, A_REVERSE);
			mvwprintw(shop, 27, 59, "+5 HP");
        if(highlights ==2)  wattroff(shop, A_REVERSE);
		mvwprintw(shop, 28, 61, "%d @", prezzi[highlights]);

        choice = wgetch(shop);
        switch (choice)
        {
        case KEY_LEFT:
            highlights--;
            if(highlights == -1)	highlights = 0;
            break;
        case KEY_RIGHT:
            highlights++;
            if(highlights == 3)		highlights = 2;
            break;
		case 10:
			if(p.getMoney() >= prezzi[highlights])
			{
				p.pay(prezzi[highlights]);

				if(highlights == 0)			p.incAtk(2);
				else if(highlights == 1)	p.incDef(2);
				else if(highlights == 2)	p.incHP(5);
			}
			break;
        default:
            break;
        }
		clear();
    }

}

int main(){
	srand(time(NULL));

	// Inizializzazione della libreria ncurses
	initscr();cbreak();noecho();

	// Impostazione dei colori
	start_color(); for (int i = 1; i <= NUM_COLORS; i++) 	init_pair(i, i, COLOR_BLACK);

	Player protagonist;
	bool correct_input = false;
	int choice = protagonist.choice_menu();//0;		//significa che il player esiste già, quindi deve solo prendere le statistiche
	char username[20], password[20];

	while(!correct_input){
		if(choice <= 1)		protagonist.getCredentials(username, password);
		switch(choice){
			case 0:
                correct_input = protagonist.login(username, password);
                break;
            case 1:
                //creo la cartella per salvare i file di gioco del giocatore (rinominata col suo nome)
                correct_input = protagonist.signIn(username, password);
                break;
            case 2:
                clear();
				endwin();
				exit(0);
                break;
            default:
                break;

        }
	}


	//inizio game
	int esito_partita = 0;
	ptr_livelli gioco = NULL, head = NULL;



	if(choice == 0){
		bool open = true;
		int backup_level = protagonist.getCurrentLevel();
		protagonist.setCurrentLevel(1);

		do{
			char filePath[50] , str[10];
			strcpy(filePath, "Archivio/");
			sprintf(str, "%d", protagonist.getCurrentLevel());

			//genera la path del file da aprire:
			//Esempio Path nel caso giochi il player:"Andrea" e voglia salvare il livello n:
			// filePath = "Archivio/Andrea/Leveln.txt"
			strcat(filePath, protagonist.getNick());
			strcat(filePath, "/Level");
			strcat(filePath, str);
			strcat(filePath, ".txt");
			ifstream file(filePath);

			//se il file è aperto correttamente
			if(file) {
				gioco = new_level(gioco, protagonist);
				file.close();
			} else	open = false;

			if(protagonist.getCurrentLevel() == 1)	head = gioco;
			protagonist.setCurrentLevel(protagonist.getCurrentLevel() + 1);

		}while(open);

		protagonist.setCurrentLevel(backup_level);

		int i = 1;
		ptr_livelli tmp = head;

		//ciclo per cercare il livello corrente
		while(i < protagonist.getCurrentLevel()){
			tmp = tmp -> next;
			i++;
		}

		gioco = tmp;
	}else{
		gioco = new_level(gioco, protagonist);
		head = gioco;
	}

	do
	{
		Player backup_p = protagonist;

		ptr_livelli gioco_backup = new livello;
		gioco_backup->n_liv = gioco->n_liv;
		gioco_backup->partita = gioco->partita;
		gioco_backup->next = gioco->next;
		gioco_backup->prev = gioco->prev;

		protagonist.setX_Y(3, 4);
		Map mappa_backup = gioco->partita.getMap();
		int n_mostri_backup = gioco->partita.getNMostri();
		mlist lista_mostri_backup = *(gioco->partita.getListaMostri());

		//inzio del game
		esito_partita = (gioco->partita).run(protagonist);

		if(esito_partita == GO_TO_PREV)
			gioco = gioco->prev, protagonist.setCurrentLevel(protagonist.getCurrentLevel() - 1);

		else if(esito_partita == GO_TO_NEXT){
			protagonist.setCurrentLevel(protagonist.getCurrentLevel() + 1);

			if(gioco->next != NULL)
				gioco = gioco->next;
			else
				gioco = new_level(gioco, protagonist);

		}else if(esito_partita == GO_TO_SHOP){
			shop(protagonist);
		}else if(esito_partita == LOSE){
			//in caso carico i backup
			protagonist = backup_p;
			protagonist.SetHp(20.0);

			gioco->n_liv   =  gioco_backup->n_liv;
			gioco->partita =  gioco_backup->partita;
			gioco->next    =  gioco_backup->next;
			gioco->prev    =  gioco_backup->prev;
		}

	}
	while (esito_partita != EXIT);

	//inizio salvataggio livelli
	ptr_livelli tmp = gioco;
	while (tmp != NULL){
		Map mappa = tmp->partita.getMap();
		mappa.writeMap(tmp->n_liv, protagonist.getNick());
		tmp = tmp->prev;
	}

	tmp = gioco;
	while (tmp != NULL){
		Map mappa = tmp->partita.getMap();
		mappa.writeMap(tmp->n_liv, protagonist.getNick());
		tmp = tmp->next;
	}

	//salvo statistiche player
	protagonist.saveStats();

	clear();
	endwin();
	return 0;
}
