#include <iostream>
#include <ctime>
#include <curses.h>
#include "Game.hpp"
#include "Map.hpp"
#include <unistd.h>

Game::Game() {
    this->map = Map(40, 80);
    //aggiungere numero mostri + la lista dei mostri
};

int Game::run(p_session Sessione) {
    srand(time(NULL));
    int esito = IN_GAME;
    int numero_mostri = 4;

    pbul lista_proiettili = NULL;
    pmon lista_mostri = NULL;

    //generazione mostri //////////////////
    int m_x, m_y, m_atk, m_def, m_mode;
    int max_m_hp = 200;
    char m_look;
    for(int i=0; i<numero_mostri; i++){
        m_x = rand()%(map.getWidth()-4)+2;
        m_y = rand()%(map.getHeight()-2)+1;
        m_atk = 10;
        m_def = 1;
        m_mode = rand()%4;
        m_look = 'A';
        if(map.isempty(m_x, m_y)) {
            Monster mostro(m_x, m_y, max_m_hp, m_atk, m_def, m_mode, m_look, 5, 4, i);
            lista_mostri = new_monster(lista_mostri, mostro);
        }
        else i--;
    }

    keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

    //box mappa, statistiche e comandi
	WINDOW *game_win, *commands_win, *player_stats_win, *game_over_win;

	int starty = (LINES - 42) / 2;
    int startx = (COLS - 82) / 3;

	game_win = newwin(42, 82, starty, startx);
    player_stats_win = newwin(20, 30, starty, startx+82);
    game_over_win = newwin(3, 11, LINES/2, COLS/2 - 30);

	refresh();
	curs_set(0);
	refresh();

	for(int i = 0 ; i < this->map.getHeight() ; i++){
		for(int j = 0 ; j < this->map.getWidth() ; j++){
			mvwprintw(game_win, i, j, "%c", this->map.getMapChar(i, j));
			wrefresh(game_win);
		}
	}

    // game loop
	int prev_x, prev_y, c=0, b=0, d=0, e=0, f = 0;

    int bul_speed = 10;     //abbassare i valori per aumentare le velocità
    int mon_speed = 130;
    int m_shot_fr = 100;

    arnd around;
    pbul tmp_b = NULL, tmp_b2 = NULL;
    pmon tmp_m = NULL;

    Sessione->p.setX_Y(3, 4);
	while(esito == IN_GAME || esito == WIN)
    {
        napms(5);

        //funzione per disegnare la window delle statistiche
        drawStats(player_stats_win, startx, starty, Sessione);

        prev_x = Sessione->p.getX();
		prev_y = Sessione->p.getY();

        tmp_m = lista_mostri;
        while(tmp_m != NULL){
            tmp_m->prev_x = tmp_m->mon.x;
            tmp_m->prev_y = tmp_m->mon.y;
            tmp_m = tmp_m->next;
        }

        tmp_b = lista_proiettili;
        while(tmp_b != NULL){
            tmp_b->prev_x = tmp_b->bul.x;
            tmp_b->prev_y = tmp_b->bul.y;
            tmp_b = tmp_b->next;
        }

        /*
        if(map.freeWay(3, 20, 60, 20)== 1){
            game_exit();
        }*/

        // Input ///////////////////////////////////////////////////////////
		int ch = getch();

        lista_proiettili = handleInput(ch, map, lista_mostri, Sessione->p, lista_proiettili, around, esito);

        int monster_mode = 0;

        // Mostri ///////////////////////////////////////////////////////////
        if(c == mon_speed ) {
            pmon before = NULL;
            tmp_m = lista_mostri;
            while(tmp_m != NULL){
                tmp_m->mon.move(map, Sessione->p.x, Sessione->p.y); //movimento

                if(tmp_m->mon.hp <= 0){    //controllo hp
                    map.setMapChar(tmp_m->mon.y, tmp_m->mon.x, ' ');
                    mvwprintw(game_win, tmp_m->prev_y, tmp_m->prev_x, " ");
	                wrefresh(game_win);

                    if(tmp_m == lista_mostri)
                    {
                        pmon to_del = lista_mostri;
                        lista_mostri = lista_mostri->next;
                        tmp_m = lista_mostri;
                        delete to_del;
                    }
                    else{
                        pmon to_del = tmp_m;
                        before->next =tmp_m->next;
                        tmp_m = tmp_m->next;
                        delete to_del;
                    }
                }
                else{
                    before = tmp_m;
                    tmp_m = tmp_m->next;
                }
            }
        }


        // sparo mostri ///////////////////////////////////////////////////////
        if(e == m_shot_fr){
            int b_mode;
            tmp_m = lista_mostri;
            while(tmp_m != NULL){
                if(Sessione->p.x == tmp_m->mon.x){
                    if(Sessione->p.y < tmp_m->mon.y){
                        b_mode = 3;
                    }
                    else{
                        b_mode = 1;
                    }
                }
                else if(Sessione->p.y == tmp_m->mon.y){
                    if(Sessione->p.x < tmp_m->mon.x){
                        b_mode = 2;
                    }
                    else{
                        b_mode = 0;
                    }
                }
                lista_proiettili = tmp_m->mon.fire(lista_proiettili, map, b_mode, 1);
                tmp_m = tmp_m->next;
            }
        }


        // update monster look ///////////////////////////////////////
        if(f == 20){
            tmp_m = lista_mostri;
            while(tmp_m != NULL){
                tmp_m->mon.look = 90- ((25 * tmp_m->mon.hp) / max_m_hp);
                tmp_m = tmp_m->next;
            }
            monsterUpdate(map, lista_mostri);
        }

        // Proiettili ////////////////////////////////////////////////////
        if(b==bul_speed){
            tmp_b = lista_proiettili;
            tmp_b2 = lista_proiettili;

            pbul p_before = NULL;
            while(tmp_b != NULL){

                int collision = tmp_b->bul.move_bul(map);
                if(collision != 0){

                    if(collision == 2){
                        Sessione->p.hp -= 1;
                    }

                    else if(collision == 3){
                        pmon x = lista_mostri;
                        if(tmp_b->bul.dir == 0){
                            x = search_monster_by_xy(lista_mostri, (tmp_b->bul.x) + 1, (tmp_b->bul.y));
                        }
                        else if(tmp_b->bul.dir == 1){
                            x = search_monster_by_xy(lista_mostri, (tmp_b->bul.x), (tmp_b->bul.y) + 1);
                        }
                        else if(tmp_b->bul.dir == 2){
                            x = search_monster_by_xy(lista_mostri, (tmp_b->bul.x) - 1, (tmp_b->bul.y));
                        }
                        else if(tmp_b->bul.dir == 3){
                            x = search_monster_by_xy(lista_mostri, (tmp_b->bul.x), (tmp_b->bul.y) - 1);
                        }
                        if(x!=NULL){

                            x->mon.hp -= 5;
                        }
                    }

                    map.setMapChar(tmp_b->bul.y, tmp_b->bul.x, ' ');
                    mvwprintw(game_win, tmp_b->bul.y, tmp_b->bul.x, " ");
	                wrefresh(game_win);

                    //eliminazione proiettile
                    if(tmp_b == lista_proiettili)
                    {
                        pbul to_del = lista_proiettili;
                        lista_proiettili = lista_proiettili -> next;
                        tmp_b = lista_proiettili;
                        delete to_del;
                    }
                    else
                    {
                        pbul to_del = tmp_b;
                        p_before -> next = tmp_b -> next;
                        tmp_b = tmp_b -> next;
                        delete to_del;
                    }
                    /////////////////////////////
                }
                else
                {
                    p_before = tmp_b;
                    tmp_b = tmp_b->next;
                }
            }
        }

        if(d = 400){
            //controllo intorno a player
            around = Sessione->p.check_around(map);

            // fight /////////////////////////////////////////////////////////////////////////////
            //ho provato a mettere tutto in un metodo di player ma non si riesce per via di errori di inclusion
            pmon x = lista_mostri;
            if(around.right == 1){
                x = search_monster_by_xy(lista_mostri, (Sessione->p.x) + 1, (Sessione->p.y));
                if(x!=NULL){
                    x->mon.hp = Sessione->p.fight(x->mon.hp, x->mon.atk, x->mon.def);
                }
            }
            x = lista_mostri;
            if(around.under == 1){
                x = search_monster_by_xy(lista_mostri, (Sessione->p.x), (Sessione->p.y) + 1);
                if(x!=NULL){
                    x->mon.hp = Sessione->p.fight(x->mon.hp, x->mon.atk, x->mon.def);
                }
            }
            x = lista_mostri;
            if(around.left == 1){
                x = search_monster_by_xy(lista_mostri, (Sessione->p.x) - 1, (Sessione->p.y));
                if(x!=NULL){
                    x->mon.hp = Sessione->p.fight(x->mon.hp, x->mon.atk, x->mon.def);
                }
            }
            x = lista_mostri;
            if(around.above == 1){
                x = search_monster_by_xy(lista_mostri, (Sessione->p.x), (Sessione->p.y) - 1);
                if(x!=NULL){
                    x->mon.hp = Sessione->p.fight(x->mon.hp, x->mon.atk, x->mon.def);
                }
            }
        }

        //update
        if(prev_y != Sessione->p.getY() || prev_x != Sessione->p.getX())
			update(map, Sessione->p, prev_y, prev_x);
        monsterUpdate(map, lista_mostri); bulletUpdate(map, lista_proiettili);

        // Draw  //////////////////////////////////////////////////////////
        draw(game_win, map, Sessione->p, prev_x, prev_y);wrefresh(game_win);

        if(c == mon_speed) {
            drawMonster(game_win, map, lista_mostri);
            c = 0;
        }
        if(b == bul_speed){
            drawBullet(game_win, map, lista_proiettili);
            b = 0;
        }

        if(d == 400)            d = 0;
        if(e == m_shot_fr)      e = 0;
        if(f == 20)             f = 0;

        b++, c++, d++, e++, f++;

        if(esito != EXIT) {
            //se il protagonista muore
            if(Sessione->p.hp <= 0)     esito = LOSE;

            //se il protagonista raccoglie tutte le monete
            if(map.getCoins() == 0)    esito = WIN;

            //il protagonista va al livello successivo
            if(this->map.getCoins() == 0 && (this->map).protagonistInNextPortal())    esito = GO_TO_NEXT;

            //il protagonista va al livello precedente
            if((this->map).protagonistInPrevPortal() && Sessione->curr_level != 1)   esito = GO_TO_PREV;
        }
	}

    //if(esito != EXIT){
        if(esito == LOSE)
            drawGameover(game_win, game_over_win), getch();
        else if(esito == GO_TO_NEXT)
            this->map.setMapChar(this->map.getHeight() - 3, this->map.getWidth() - 5, ' ');
        else if(esito == GO_TO_PREV)
            this->map.setMapChar(2, 4, ' ');
    //}
    delwin(game_win);wrefresh(game_win);

    return esito;
}

pbul Game::handleInput(int c, Map& map, pmon lista_mostri, Player& giocatore, pbul bullet_list, arnd around, int& e) {
	if(c == ERR) {;/*no tasti premuti dall'utente*/}
	else {
		switch(c)
		{
			case KEY_UP:
                if(around.above == 2)
                {
                    giocatore.money += 1;
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.moveup(map);
				break;

			case KEY_DOWN:
                if(around.under == 2)
                {
                    giocatore.money += 1;
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.movedown(map);
				break;

			case KEY_LEFT:
                if(around.left == 2)
                {
                    giocatore.money += 1;
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.moveleft(map);
				break;
			case KEY_RIGHT:

                if(around.right == 2)
                {
                    giocatore.money += 1;
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.moveright(map);
				break;
            case 'd':
                bullet_list = giocatore.fire(bullet_list, map, 0, 0);
                break;
            case 's':
                bullet_list = giocatore.fire(bullet_list, map, 1, 0);
                break;
            case 'a':
                bullet_list = giocatore.fire(bullet_list, map, 2, 0);
                break;
            case 'w':
                bullet_list = giocatore.fire(bullet_list, map, 3, 0);
                break;
            case 'q':
                e = EXIT;
			default:
				break;
		}
	}
    return bullet_list;
}


void Game::update(Map& map, Character& protagonist, int prev_y, int prev_x) {
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

void Game::drawStats(WINDOW *win, int x, int y, p_session Sessione){
    box(win, 0, 0);
    mvwprintw(win, 0, 7, "Stats di %s", Sessione->p.getNick());
    mvwprintw(win, 2, 3, " Monete : %d     ", Sessione->p.getMoney());
    mvwprintw(win, 4, 3, "   Vita : %d     ", Sessione->p.getHp());
    mvwprintw(win, 6, 3, "Attacco : %d     ", Sessione->p.getAtk());
    mvwprintw(win, 8, 3, " Difesa : %d     ", Sessione->p.getDef());
    if(this->map.getCoins() > 1)
        mvwprintw(win, 18, 2, "Mancano ancora %d monete   ", this->map.getCoins());
    else if(this->map.getCoins() == 1)
        mvwprintw(win, 18, 2, "Dai, manca l'ultima moneta!", this->map.getCoins());
    else if(this->map.getCoins() == 0)
        mvwprintw(win, 18, 2, " Livello %d superato!       ", Sessione->curr_level);

    wrefresh(win);
}

void Game::drawGameover(WINDOW* game_win, WINDOW* game_over_win){
    //werase(game_win);
    //wrefresh(game_win);
    box(game_over_win, 0, 0);
    mvwprintw(game_over_win, 1, 1, "Game Over");
    wrefresh(game_over_win);
    getchar();
    game_exit();
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

Map Game::getMap(){
    return this->map;
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
