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

	/*

		LOGIN O CREAZIONE ACCOUNT

	*/
					 //nick    psw
	Player protagonist("leo", "leo", 10, '1');

	p_session Sessione = new Session;
	Sessione->p = protagonist;
	Sessione->curr_level = 1;



	//inizio game + messaggio iniziale (grafica)
	int esito_partita = 0;
	int livello_corrente = 1;
	ptr_livelli head;
	ptr_livelli gioco = NULL;
	gioco = new_level(gioco, Sessione->curr_level);
	head = gioco;

	/*
	gioco->partita.run(gioco->n_liv);
	gioco = new_level(gioco, livello_corrente + 1);
	esito_partita = gioco->partita.run(gioco->n_liv);*/

	do
	{
		esito_partita = (gioco->partita).run(Sessione);
		if(esito_partita == GO_TO_PREV && Sessione->curr_level > 1){
			gioco = gioco->prev, (Sessione->curr_level)--;
		}else if(esito_partita == GO_TO_NEXT){
			if(gioco->next != NULL){
				gioco = gioco->next;
			}
			else{
				gioco = new_level(gioco, (Sessione->curr_level) + 1);
			}
			(Sessione->curr_level)++;
		}
	}
	while (esito_partita != LOSE);


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

	/*if(choice <= 1){
		game.run();
	}*/
	return 0;
}
