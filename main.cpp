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
ptr_livelli new_level(ptr_livelli l, p_session Sessione){
	if(l == NULL) {
		l = new livello;
		l->next = NULL;
		l->prev = NULL;
		l->partita = Game(Sessione);
		l->n_liv = Sessione->curr_level;
		return l;
	}
	else {
		ptr_livelli new_l = new livello;
		l->next = new_l;
		new_l->next = NULL;
		new_l->prev = l;
		new_l->partita = Game(Sessione);
		new_l->n_liv = Sessione->curr_level;
		return new_l;
	}
}

int main(){
	srand(time(NULL));

	// Inizializzazione della libreria ncurses
	initscr();cbreak();noecho();

	Player protagonist;
	bool correct_input = false;
	int choice = protagonist.choice_menu();//0;		//significa che il player esiste già, quindi deve solo prendere le statistiche
	char username[20], password[20];
	int curr_level;

	while(!correct_input){
		if(choice <= 1)		protagonist.getCredentials(username, password);
		switch(choice){
			case 0:
                correct_input = protagonist.login(username, password, curr_level);
                break;
            case 1:
                //creo la cartella per salvare i file di gioco del giocatore (rinominata col suo nome)
                correct_input = protagonist.signIn(username, password);
				curr_level = 1;
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

	protagonist.setCredentials(username, password);
	p_session Sessione = new Session;
	Sessione->p = protagonist;
	Sessione->curr_level = curr_level;

	//inizio game
	int esito_partita = 0;
	ptr_livelli gioco = NULL, head;

	if(choice == 0){
		ifstream file;
		gioco = NULL;
		bool open = true;
		int level_counter = 1;
		int backup_level = Sessione->curr_level;

		do{
			char filePath[50] , str[10];
			strcpy(filePath, "Archivio/");
			sprintf(str, "%d", level_counter);

			//genera la path del file da aprire:
			//Esempio Path nel caso giochi il player:"Andrea" e voglia salvare il livello n:
			// filePath = "Archivio/Andrea/Leveln.txt"
			strcat(filePath, Sessione->p.getNick());
			strcat(filePath, "/Level");
			strcat(filePath, str);
			strcat(filePath, ".txt");
			//file.open(filePath, ios::in);
			ifstream file(filePath);

			//se il file è aperto correttamente
			if(file) {
				Sessione->curr_level = level_counter;
				gioco = new_level(gioco, Sessione);
				file.close();
			} else	open = false;

			if(Sessione->curr_level == 1)	head = gioco;

			level_counter++;

		}while(open);

		Sessione->curr_level = backup_level;
		int i = 1;
		ptr_livelli tmp = head;

		//ciclo per cercare il livello corrente
		while(i < Sessione->curr_level){
			tmp = tmp -> next;
			i++;
		}

		gioco = tmp;
	}else{
		gioco = new_level(gioco, Sessione);
		head = gioco;
	}

	do
	{
		p_session sessione_backup = new Session;
		sessione_backup->p = Sessione->p;
		sessione_backup->curr_level = Sessione->curr_level;

		ptr_livelli gioco_backup = new livello;
		gioco_backup->n_liv = gioco->n_liv;
		gioco_backup->partita = gioco->partita;
		gioco_backup->next = gioco->next;
		gioco_backup->prev = gioco->prev;

		Sessione->p.setX_Y(3, 4);
		Map mappa_backup = gioco->partita.getMap();
		int n_mostri_backup = gioco->partita.getNMostri();
		mlist lista_mostri_backup = *(gioco->partita.getListaMostri());

		//inzio del game
		esito_partita = (gioco->partita).run(Sessione);

		if(esito_partita == GO_TO_PREV)
			gioco = gioco->prev, (Sessione->curr_level)--;

		else if(esito_partita == GO_TO_NEXT){
			(Sessione->curr_level)++;

			if(gioco->next != NULL)
				gioco = gioco->next;
			else
				gioco = new_level(gioco, Sessione);

		}else if(esito_partita == LOSE){
			//in caso carico i backup
			Sessione->p          = sessione_backup->p;
			Sessione->curr_level = sessione_backup->curr_level;
			Sessione->p.SetHp(20.0);

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
		mappa.writeMap(tmp->n_liv, Sessione->p.getNick());
		tmp = tmp->prev;
	}

	tmp = gioco;
	while (tmp != NULL){
		Map mappa = tmp->partita.getMap();
		mappa.writeMap(tmp->n_liv, Sessione->p.getNick());
		tmp = tmp->next;
	}

	//salvo statistiche player
	Sessione->p.saveStats(Sessione->curr_level);

	clear();
	endwin();
	return 0;
}
