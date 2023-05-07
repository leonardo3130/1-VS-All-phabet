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
ptr_livelli new_level(ptr_livelli l, int n){
	if(l == NULL) {
		l = new livello;
		l->next = NULL;
		l->prev = NULL;
		l->partita = Game();
		l->n_liv = n;
		return l;
	}
	else {
		ptr_livelli new_l = new livello;
		new_l->next = NULL;
		new_l->prev = l;
		new_l->partita = Game();
		new_l->n_liv = n;
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
		if(choice <= 1){
			protagonist.getCredentials(username, password);
		}
		switch(choice){
			case 0:
                correct_input = protagonist.login(username, password, curr_level);
                break;
            case 1:
                //creo la cartella per salvare i file di gioco del giocatore (rinominata col suo nome)
                //system(strcat(mkdir, username));
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


	//inizio game + messaggio iniziale (grafica)
	int esito_partita = 0;
	ptr_livelli gioco = new_level(gioco, Sessione->curr_level),
				head = gioco;

	do
	{
		Sessione->p.setX_Y(3, 4);
		esito_partita = (gioco->partita).run(Sessione);

		if(esito_partita == GO_TO_PREV){
			gioco = gioco->prev, (Sessione->curr_level)--;
		}
		else if(esito_partita == GO_TO_NEXT){
			if(gioco->next != NULL){
				gioco = gioco->next;
			}
			else{
				gioco = new_level(gioco, (Sessione->curr_level) + 1);
			}
			(Sessione->curr_level)++;
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
