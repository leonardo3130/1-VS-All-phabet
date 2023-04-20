#include <iostream>
#include <ctime>
#include <curses.h>
#include "Game.hpp"
#include <unistd.h>

#define NUM_COLORS 8

Game::Game() {};

void Game::run() {
    srand(time(NULL));

    char* nick = "leo";
    char* psw = "leo";


	Character protagonist(3,3,10,10,10,0,'1');

    int numero_mostri = 6;

    Player giocatore(nick, psw, 2);
	Map map(40,80);


    pbul lista_proiettili = NULL;
    pmon lista_mostri = NULL;

    //Bullet proiettile(1, 5, 5, 0, '*');

    for(int i=0; i<numero_mostri; i++){
        Monster mostro(5,4, i);
        mostro.x = rand()%(map.getWidth()-2);
        mostro.y = rand()%(map.getHeight()-1);
        mostro.hp = 10;
        mostro.atk = 10;
        mostro.def = 10;
        mostro.mode = rand()%4;
        mostro.look = 'y';
        lista_mostri = new_monster(lista_mostri, mostro);   
    }

    //lista_proiettili = new_bullet(lista_proiettili, proiettile);


	//initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	WINDOW *game_win, *commands, *player_stats;

	int starty = (LINES - 42) / 2;
    int startx = (COLS - 82) / 2;

	game_win = newwin(42, 82, starty, startx);

    /*
    commands = newwin(18, 30, starty+84, startx+100);
    player_stats = newwin(20, 30, starty+84, startx+100);
    */

	refresh();
	curs_set(0);
	refresh();

    /*
    box(commands, 0, 0);
    box(player_stats, 0, 0);
    refresh();
    wrefresh(commands);
    wrefresh(player_stats);
    */
	for(int i = 0 ; i < map.getHeight() ; i++){
		for(int j = 0 ; j < map.getWidth() ; j++){
			mvwprintw(game_win, i, j, "%c",map.getMapChar(i, j));
			wrefresh(game_win);
		}
	}

	// game loop

	bool stop = false;
	//double time = 0.0;
	time_t previous_time = time(nullptr);
	time_t lag = time_t(0.0);
	time_t current, elapsed;

	int prev_x, prev_y, c=0, b=0;

    pbul tmp1 = NULL, tmp2 = NULL, tmp_erino = NULL;

    pmon tmp_m1 = NULL, tmp_m2 = NULL, tmp_m3 = NULL;

	int const MS = 50;

	while(true) //condizione che andrà in base ad hp e altro
    {
		current = time(nullptr);
		elapsed = current - previous_time;
		previous_time = current;
		lag += elapsed;


        prev_x = protagonist.getX();
		prev_y = protagonist.getY();

        tmp_m1 = lista_mostri;
        while(tmp_m1 != NULL){
            tmp_m1->prev_x = tmp_m1->mon.x;
            tmp_m1->prev_y = tmp_m1->mon.y;
            tmp_m1 = tmp_m1->next;
        }

        tmp1 = lista_proiettili;
        while(tmp1 != NULL){
            tmp1->prev_x = tmp1->bul.x;
            tmp1->prev_y = tmp1->bul.y;
            tmp1 = tmp1->next;
        }
        
        // Input ///////////////////////////////////////////////////////////
		int ch = getch();
		handleInput(ch, map, protagonist, lista_mostri, giocatore, lista_proiettili);
        int monster_mode = 0;


        // Mostri ///////////////////////////////////////////////////////////


        if(c == 900000) {
            tmp_m2 = lista_mostri;
            while(tmp_m2 != NULL){
                int monster_prob = rand()%5;
                int monster_mode;
                if(monster_prob == 1)
                    monster_mode = rand()%4;

                tmp_m2->mon.move(map, giocatore, monster_mode);
                lista_proiettili = tmp_m2->mon.fire(lista_proiettili);
                tmp_m2 = tmp_m2->next;
            }
        }
        
        
        // Proiettili ////////////////////////////////////////////////////
        if(b==30000){
            tmp2 = lista_proiettili;
            tmp_erino = lista_proiettili;
            
            pbul lista_nera = NULL; //priettili da eliminare;
            while(tmp2 != NULL){
                bool collision = 0;
                collision = tmp2->bul.move_bul(map); //collision per riciclare i controlli che vengono eseguiti in move_bul
                if(collision == 1){
                    lista_nera = new_bullet(lista_nera, tmp2->bul);
                }
                tmp2 = tmp2->next;
            }
            while(lista_nera != NULL){
                while(tmp_erino != NULL){
                    if( lista_nera->bul.x == tmp_erino->bul.x &&
                        lista_nera->bul.y == tmp_erino->bul.y &&
                        lista_nera->bul.dir == tmp_erino->bul.dir   ){
                            lista_proiettili = remove_bullet(lista_proiettili, tmp_erino->bul.x, tmp_erino->bul.y, tmp_erino->bul.dir);
                            map.setMapChar(tmp_erino->bul.y, tmp_erino->bul.x, ' ');
                            mvwprintw(game_win, tmp_erino->bul.y, tmp_erino->bul.x, " ");
	                        wrefresh(game_win);
                    }
                    tmp_erino = tmp_erino->next;
                }
                lista_nera = lista_nera->next;
            }
            delete lista_nera;
        }


        // Update  /////////////////////////////////////////////////////////
		while(lag >= MS)
		{
            if(prev_y != protagonist.getY() || prev_x != protagonist.getX())
			    update(map, protagonist, prev_y, prev_x);
                monsterUpdate(map, lista_mostri);
                bulletUpdate(map, lista_proiettili);
            lag -= MS;
		}


        // Draw  //////////////////////////////////////////////////////////
        if(prev_y != protagonist.getY() || prev_x != protagonist.getX()){
            draw(game_win, map, protagonist, prev_x, prev_y);
        }
        if(c == 900000) {
            drawMonster(game_win, map, lista_mostri);
            c = 0;
        }
        if(b==30000){
            drawBullet(game_win, map, lista_proiettili);
            b=0;
        }
        b++;
        c++;


	}
	getch();
    endwin();
}

void Game::handleInput(int c, Map& map, Character& protagonist, pmon lista_mostri, Player& giocatore, pbul bullet_list) {
	if(c == ERR) {;/*no tasti premuti dall'utente*/}
	else {
		switch(c)
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
            case KEY_BACKSPACE:
                bullet_list = protagonist.fire(bullet_list);
                break;
            case 'q':
                game_exit();
			default:
				break;
		}
	}
}

void Game::update(Map& map, Character& protagonist, int prev_x, int prev_y) {
        map.setMapChar(prev_y, prev_x, ' ');
        map.setMapChar(protagonist.getY(), protagonist.getX(), protagonist.getLook());
}

void Game::monsterUpdate(Map &map, pmon monster_list){
    pmon tmp = monster_list;
    while (tmp != NULL){
        map.setMapChar(tmp->prev_y, tmp->prev_x, ' ');
        map.setMapChar(tmp->mon.getY(), tmp->mon.getX(), tmp->mon.getLook());
        tmp = tmp->next;
    }
}
void Game::bulletUpdate(Map &map, pbul bul_list){
    pbul tmp3 = bul_list;
    while(tmp3 != NULL){
        map.setMapChar(tmp3->prev_y, tmp3->prev_x, ' ');
        map.setMapChar(tmp3->bul.y, tmp3->bul.x, '*');
        tmp3 = tmp3->next;
    }
}
void Game::draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y) {
        mvwprintw(win, prev_y, prev_x, " ");
	    wrefresh(win);
	    mvwprintw(win, protagonist.getY(), protagonist.getX(), "%c",protagonist.getLook());
        wrefresh(win);


}

void Game::drawMonster(WINDOW* win, Map& map, pmon monster_list) {
    pmon tmp = monster_list;
    while (tmp != NULL){
        mvwprintw(win, tmp->prev_y, tmp->prev_x, " ");
        wrefresh(win);
        mvwprintw(win, tmp->mon.getY(), tmp->mon.getX(), "%c", tmp->mon.getLook());
        wrefresh(win);
        tmp = tmp->next;
    }
}
void Game::drawBullet(WINDOW* win, Map& map, pbul bul_list) {
    pbul tmp3 = bul_list;
    while(tmp3 != NULL){
        mvwprintw(win, tmp3->prev_y, tmp3->prev_x, " ");
	    wrefresh(win);
	    mvwprintw(win, tmp3->bul.y, tmp3->bul.x, "%c", '*');
        wrefresh(win);
        tmp3 = tmp3->next;
    }
}

void Game::timed_print(char *text, int text_len, int micro_seconds_delay, int l, int c){
    // Impostazione dei colori
    start_color();

    for (int i = 1; i <= NUM_COLORS; i++) {
        init_pair(i, i, COLOR_BLACK);
    }

    // Impostazione dei colori per la scritta
    attron(COLOR_PAIR(1));

    for (int i = 0; i < text_len - 1; i++) {
        attron(COLOR_PAIR(rand() % NUM_COLORS + 1)); // Imposta un colore casuale
        mvprintw(l, c + i, "%c", text[i]);
        refresh();
        usleep(micro_seconds_delay); // Ritardo di 100 millisecondi
    }

    for (int i = 1; i <= NUM_COLORS; i++) {
        attroff(COLOR_PAIR(i));
    }
}

//messaggio iniziale
void Game::init_message(){
    // Animazioni
    char text[] = "Welcome in 1 vs (All)phabet.";
    timed_print(text, 29, 100000, LINES/3, COLS/2 - 14);

    strcpy(text, "Press any key...");
    timed_print(text, 17, 30000, LINES/3 + 1, COLS/2 - 8);

    // Attende la pressione di un tasto per chiudere la finestra
    getch();
}

//get credentials from the terminal
void Game::getCredentials(char* username, char* password) {
    // Crea il box verde
    attron(COLOR_PAIR(COLOR_GREEN));
    box(stdscr, 0, 0);

    mvprintw(LINES/2 - 4, COLS/2 - 14, "Please enter your credentials:");
    mvprintw(LINES/2 - 2, COLS/2 - 15, "Username: ");
    mvprintw(LINES/2, COLS/2 - 15, "Password: ");

    // Crea la finestra di input per l'username
    mvprintw(LINES/2 - 2, COLS/2 - 7, "[               ]");

    // Crea la finestra di input per la password
    mvprintw(LINES/2, COLS/2 - 7, "[               ]");
    attroff(COLOR_PAIR(COLOR_GREEN));

    // Sposta il cursore sulla finestra dell'username
    move(LINES/2 - 2, COLS/2 - 4);
    echo();
    getstr(username);

    // Sposta il cursore sulla finestra della password
    move(LINES/2, COLS/2 - 4);
    noecho();
    getstr(password);

    // Pulisco lo schermo
    clear();
}

//menu per scegliere se effettuare login, sign in o uscire dal gioco
int Game::choice_menu() {
    int choice = 0;
    string choices[3]={"Login", "Sign in", "Exit"};
    int highlights = 0;

    WINDOW *menu = newwin(6, 12 , LINES/2 -1, COLS/2 -2);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);

    keypad(menu, true);

    while (choice != 10){
        for(int i=0; i< 3; i++){
            if(i == highlights)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i+1, 1, choices[i].c_str());
            wattroff(menu, A_REVERSE);
        }
        choice = wgetch(menu);

        switch (choice)
        {
        case KEY_UP:
            highlights--;
            if(highlights == -1)
                highlights = 0;
            break;
        case KEY_DOWN:
            highlights++;
            if(highlights == 3)
                highlights = 2;
            break;

        default:
            break;
        }
    }

    return highlights;
}

void Game::game_exit(){
    char text[11];
    strcpy(text, "Goodbye...");
    clear();
    timed_print(text, 11, 100000, LINES/3, COLS/2 - 5);

    /*
        code for the backup
    */

    getch();
    endwin();
    exit(0);
}
