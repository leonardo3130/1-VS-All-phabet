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
    
    Monster mostro(5, 4, 0);
    mostro.x = 3;
    mostro.y = 4;
    mostro.hp = 10;
    mostro.atk = 10;
    mostro.def = 10;
    mostro.mode = 0;
    mostro.look = 'x';

    Player giocatore(nick, psw, 2);
	Map map(40,80);

    Bullet proiettile = Bullet(2, 5, 5, 0, 0, '*');
    

	//initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	WINDOW *game_win;

	int starty = (LINES - 40) / 2;
    int startx = (COLS - 80) / 2;

	game_win = newwin(42, 82, starty, startx);
	refresh();
	curs_set(0);
	refresh();
	for(int i = 0 ; i < map.getHeight() ; i++){
		for(int j = 0 ; j < map.getWidth() ; j++){
			mvwprintw(game_win, i, j, "%c",map.getMapChar(i, j));
			wrefresh(game_win);
		}
	}

	//game loop
	bool stop = false;
	//double time = 0.0;
	time_t previous_time = time(nullptr);
	time_t lag = time_t(0.0);
	time_t current, elapsed;

	int prev_x, prev_y, prev_x_mostro, prev_y_mostro, prev_x_bul, prev_y_bul;

	int const MS = 50;

    int monster_prob, monster_mode;
    int c = 0, b = 0;

	while(true) //condizione che andrà in base ad hp e altro
    {
		current = time(nullptr);
		elapsed = current - previous_time;
		previous_time = current;
		lag += elapsed;

		prev_x = protagonist.getX();
		prev_y = protagonist.getY();

		prev_x_mostro = mostro.x; //
		prev_y_mostro = mostro.y; //

        prev_x_bul = proiettile.x;
        prev_y_bul = proiettile.y;
        

		int ch = getch();
		handleInput(ch, map, protagonist, mostro, giocatore, proiettile);

        monster_prob = rand()%5;
        if(monster_prob == 1);
            monster_mode = rand()%4;      
        if(c == 900000) {
            mostro.move(map, giocatore, monster_mode);
        }
        if(b==20000){
            proiettile.move_bul(map, 0);
        }

		while(lag >= MS)
		{
            if(prev_y != protagonist.getY() || prev_x != protagonist.getX())
			    update(map, protagonist, prev_y, prev_x);
                monsterUpdate(map, mostro, prev_y_mostro, prev_x_mostro);
                bulletUpdate(map, proiettile, prev_y_bul, prev_x_bul);
            lag -= MS;
		}
        if(prev_y != protagonist.getY() || prev_x != protagonist.getX())
            draw(game_win, map, protagonist, prev_x, prev_y);
        
        
		//shooting
		//mostri
        if(c == 900000) {
            drawMonster(game_win, map, mostro, prev_x_mostro, prev_y_mostro);
            c = 0;
        }
        if(b==20000){
            drawBullet(game_win, map, proiettile, prev_x_bul, prev_y_bul);
            b=0;
        }
        b++;
        c++;
	}
	getch();
    endwin();
}

void Game::handleInput(int c, Map& map, Character& protagonist, Monster& mostro, Player& giocatore, Bullet& proiettile) {
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
                
                break;
			default:
				break;
		}
	}
}

void Game::update(Map& map, Character& protagonist, int prev_x, int prev_y) {
        map.setMapChar(prev_y, prev_x, ' ');
        map.setMapChar(protagonist.getY(), protagonist.getX(), protagonist.getLook());
}

void Game::monsterUpdate(Map &map, Monster& mostro, int prev_x_mostro, int prev_y_mostro){
    map.setMapChar(prev_y_mostro, prev_x_mostro, ' ');
    map.setMapChar(mostro.getY(), mostro.getX(), mostro.getLook());
}
void Game::bulletUpdate(Map &map, Bullet& proiettile, int prev_x_bul, int prev_y_bul){
    map.setMapChar(prev_y_bul, prev_x_bul, ' ');
    map.setMapChar(proiettile.y, proiettile.x, '*');
}
void Game::draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y) {
        mvwprintw(win, prev_y, prev_x, " ");
	    wrefresh(win);
	    mvwprintw(win, protagonist.getY(), protagonist.getX(), "%c",protagonist.getLook());
        wrefresh(win);
}

void Game::drawMonster(WINDOW* win, Map& map, Monster& mostro, int prev_x_mostro, int prev_y_mostro) {
    mvwprintw(win, prev_y_mostro, prev_x_mostro, " ");
	wrefresh(win);
	mvwprintw(win, mostro.getY(), mostro.getX(), "%c", mostro.getLook());
    wrefresh(win);
}
void Game::drawBullet(WINDOW* win, Map& map, Bullet& proiettile, int prev_x_bul, int prev_y_bul) {
    mvwprintw(win, prev_y_bul, prev_x_bul, " ");
	wrefresh(win);
	mvwprintw(win, proiettile.y, proiettile.x, "%c", '*');
    wrefresh(win);
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
    timed_print(text, 11, 50000, LINES/3, COLS/2 - 5);

    /*
        code for the backup
    */

    getch();
    endwin();
    exit(0);
}
