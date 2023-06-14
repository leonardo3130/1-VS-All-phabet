#include "Game.hpp"

Game::Game(char filePath[], Player &p) { //oltre al filePath del livello bisognerà passare quello del file credentials con i suoi valori di hp, atk, def e numero di mostri (questo si vedrà) 
                                         //a inizio del livello in cui è morto 
                                         //all'inizio di ogni livello servirà quindi aggiornare il file credentials.txt
    ifstream file(filePath);
    int m_x, m_y, m_atk = 2 + (p.getCurrentLevel()), m_def = 2 + (p.getCurrentLevel()), m_mode, m_max_hp = 50 + (10 * (p.getCurrentLevel()-1));
    int t_max_hp = m_max_hp*5, t_hp;
    double m_hp;
    if (p.getCurrentLevel() == 1)
        m_atk += p.getAtk(), m_def += p.getDef();
    
    if(file){
        this->map = Map(filePath);
        this->n_mostri = 0;
        this->n_torri = 0;
        this->lista_mostri = NULL;

        //leggo la mappa da file e carico mostri e monete
        for(int i = 0 ; i < this->map.getHeight() ; i++){
            for(int j = 0 ; j < this->map.getWidth() ; j++){
                //mostri
                if(this->map.isMonster(j, i) && !this->map.isTurret(j,i)){
                    //Calcolo per la vita dei mostri
                    int character = 91.0 - (this->map.getMapChar(i, j));
                    m_hp = m_max_hp*( (double) character/26.0);

                    Monster mostro(j, i, m_hp, m_atk, m_def, rand()%4, this->map.getMapChar(i, j), 0);
                    this->lista_mostri = new_monster(this->lista_mostri, mostro);
                    this->map.setMapChar(i, j, ' ');
                    this->n_mostri++;
		        }
                //torre
                else if(this->map.isTurret(j,i)){
                    //calcolo vita torri
                    int character = 123.0 - (this->map.getMapChar(i, j));
                    t_hp = t_max_hp*( (double) character/26.0);

                    Monster mostro(j, i, t_hp, m_atk+5, m_def+5, rand()%4, this->map.getMapChar(i, j), 1);
                    this->lista_mostri = new_monster(this->lista_mostri, mostro);
                    this->map.setMapChar(i, j, ' ');
                    this->n_torri++;
                }
	        }
        }
        file.close();
    }else{
        if(p.getCurrentLevel() <= 12)
            this->n_mostri = 2 +(p.getCurrentLevel())*0.5;
        else
            this->n_mostri = 20;
        //stessa cosa del numero di mostri vale per le torri
        if(p.getCurrentLevel() <5)
            this->n_torri = 1;
        else if(p.getCurrentLevel() < 10)
            this->n_torri = 2;
        else
            this->n_torri = 3;

        (this->lista_mostri) = NULL;
        //eventuali cambiamenti per il numero di monete 
        this->map = Map(40, 80, p.getCurrentLevel());

        //generazione mostri non da file //////////////////
        //mostri
        for(int i=0; i< this->n_mostri; i++){
            m_x = rand()%(map.getWidth()-4)+2;
            m_y = rand()%(map.getHeight()-2)+1;

            if(map.isEmpty(m_x, m_y) && !map.isMoney(m_x, m_y) && !map.isMonster(m_x, m_y)) {
                Monster mostro(m_x, m_y, m_max_hp, m_atk, m_def, rand()%4, 'A', 0);
                this->lista_mostri = new_monster(this->lista_mostri, mostro);
            }
            else i--;
        }
        //torre
        for(int i=0;i< this->n_torri;i++){
            if(i == 0) {
                m_x = this->map.getWidth() / 2;
                m_y = this->map.getHeight() - 3;
            } else if(i == 1) {
                m_x = this->map.getWidth() / 2;
                m_y = 2;
            }
            else {
                m_x = this->map.getWidth() - 5;
                m_y = this->map.getHeight() / 2;
            }

            if(map.isEmpty(m_x, m_y) && !map.isMoney(m_x, m_y) && !map.isMonster(m_x, m_y)) {
                Monster mostro(m_x, m_y, t_max_hp, m_atk+5, m_def+5, rand()%4, 'a', 1);
                this->lista_mostri = new_monster(this->lista_mostri, mostro);
            }
        }
    }
};

int Game::run(Player &p) {
    //aggiorno credentials.txt (all'inizio per il numero dei mostri)
    srand(time(NULL));
    int esito = IN_GAME, m_max_hp = 50 + (10 * (p.getCurrentLevel()-1)),
                t_max_hp = m_max_hp*5;

    pbul lista_proiettili = NULL;
    keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

    //box mappa, statistiche e comandi
	WINDOW *game_win, *commands_win, *player_stats_win, *game_over_win;

	int starty = (LINES - 42) / 2;
    int startx = (COLS - 82) / 3;

	game_win = newwin(42, 82, starty, startx);
    player_stats_win = newwin(20, 30, starty, startx+82);
    game_over_win = newwin(3, 11, LINES/2 - 2, COLS/2 - 27);

	curs_set(0);
	refresh();

	for(int i = 0 ; i < this->map.getHeight() ; i++){
		for(int j = 0 ; j < this->map.getWidth() ; j++){
            mvwprintw(game_win, i, j, "%c", this->map.getMapChar(i, j));
            wrefresh(game_win);
		}
	}

    // game loop
	int prev_x, prev_y, c = 0, b = 0, d = 0, e = 0, f = 0, tmp_x, tmp_y, tmp_dir, tmp_ar;

    int bul_speed = 10;     //abbassare i valori per aumentare le velocità
    int mon_speed = 130;
    int m_shot_fr = 400;

    arnd around;
    pbul tmp_b = NULL, tmp_b2 = NULL;
    pmon tmp_m = NULL;

    p.setX_Y(3, 4);
	while(esito == IN_GAME || esito == WIN)
    {
        napms(5);

        //funzione per disegnare la window delle statistiche
        drawStats(player_stats_win, startx, starty, p);

        prev_x = p.getX();
		prev_y = p.getY();

        tmp_m = this->lista_mostri;
        while(tmp_m != NULL){
            tmp_m->prev_x = tmp_m->mon.getX();
            tmp_m->prev_y = tmp_m->mon.getY();
            tmp_m = tmp_m->next;
        }

        tmp_b = lista_proiettili;
        while(tmp_b != NULL){
            tmp_b->prev_x = tmp_b->bul.getX();
            tmp_b->prev_y = tmp_b->bul.getY();
            tmp_b = tmp_b->next;
        }

        // Input ///////////////////////////////////////////////////////////
		int ch = getch();
        fflush(stdin);

        lista_proiettili = handleInput(ch, map, p, lista_proiettili, around, esito);

        int monster_mode = 0;

        // Mostri ///////////////////////////////////////////////////////////
        if(c == mon_speed ) {
            pmon before = NULL;
            tmp_m = this->lista_mostri;
            while(tmp_m != NULL){
                if(tmp_m->mon.getTur()== 0){
                    tmp_m->mon.move(map, p.getX(), p.getY()); //movimento
                }

                if(tmp_m->mon.getHp() <= 0){    //controllo hp
                    p.takeMoney(3); // quando si uccide un mostro si prendono 3 monete

                    this -> n_mostri--;
                    map.setMapChar(tmp_m->prev_y, tmp_m->prev_x, ' ');
                    mvwprintw(game_win, tmp_m->prev_y, tmp_m->prev_x, " ");
                    wrefresh(game_win);
                    map.setMapChar(tmp_m->mon.getY(), tmp_m->mon.getX(), ' ');
                    mvwprintw(game_win, tmp_m->mon.getY(), tmp_m->mon.getX(), " ");
	                wrefresh(game_win);

                    if(tmp_m == this->lista_mostri)
                    {
                        pmon to_del = this->lista_mostri;
                        this->lista_mostri = this->lista_mostri->next;
                        tmp_m = this->lista_mostri;
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

        //sparo mostri ///////////////////////////////////////////////////////
        if(e == m_shot_fr){
            int b_mode;
            tmp_m = this->lista_mostri;
            while(tmp_m != NULL){
                if(p.getX() == tmp_m->mon.getX()){
                    if(p.getY() < tmp_m->mon.getY())
                        b_mode = 3;
                    else
                        b_mode = 1;

                    lista_proiettili = tmp_m->mon.fire(lista_proiettili, map, b_mode, 1);
                }
                else if(p.getY() == tmp_m->mon.getY()){
                    if(p.getX() < tmp_m->mon.getX())
                        b_mode = 2;
                    else
                        b_mode = 0;

                    lista_proiettili = tmp_m->mon.fire(lista_proiettili, map, b_mode, 1);
                }
                tmp_m = tmp_m->next;
            }
        }

        // Proiettili ////////////////////////////////////////////////////
        if(b == bul_speed){
            tmp_b = lista_proiettili;
            tmp_b2 = lista_proiettili;

            pbul p_before = NULL;
            while(tmp_b != NULL){
                int collision = tmp_b->bul.move_bul(map);
                if(collision != 0){

                    if(collision == 2){
                        if(this->lista_mostri != NULL)
                            p.incHP( -(lista_mostri->mon.getAtk() / p.getDef()) );
                        else p.incHP(-1);
                    }

                    else if(collision == 3){
                        pmon x = this->lista_mostri;
                        tmp_dir = tmp_b->bul.getDir();

                        if(tmp_dir == 0)        {  tmp_x = 1; tmp_y = 0;  }
                        else if(tmp_dir == 1)   {  tmp_x = 0; tmp_y = 1;  }
                        else if(tmp_dir == 2)   {  tmp_x = -1; tmp_y = 0; }
                        else if(tmp_dir == 3)   {  tmp_x = 0; tmp_y = -1; }

                        x = search_monster_by_xy(this->lista_mostri, (tmp_b->bul.getX()) + tmp_x, (tmp_b->bul.getY()) + tmp_y);

                        if(x!=NULL){
                            if(!this->map.isTurret(x->mon.getX(), x->mon.getY())){
                                x->mon.SetHp(p.fight(x->mon.getHp(), x->mon.getAtk(), x->mon.getDef()));
                                x->mon.setLook(91 - (int) ((x->mon.getHp() / m_max_hp) * 26.0));
                                if(x->mon.getLook() > 'Z') x->mon.setLook('Z');
                                x = x->next;
                            }else{
                                x->mon.SetHp(p.fight(x->mon.getHp(), x->mon.getAtk(), x->mon.getDef()));
                                x->mon.setLook(123 - (int) ((x->mon.getHp() / t_max_hp) * 26.0));
                                if(x->mon.getLook() > 'z') x->mon.setLook('z');
                                x = x->next;
                            }
                        }
                    }

                    map.setMapChar(tmp_b->bul.getY(), tmp_b->bul.getX(), ' ');
                    mvwprintw(game_win, tmp_b->bul.getY(), tmp_b->bul.getX(), " ");
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
            around = p.check_around(map);

            // fight /////////////////////////////////////////////////////////////////////////////
            pmon x = this->lista_mostri;

            for (int i = 0; i < 4; i++)
            {
                if(i == 0) {tmp_ar = around.right;  tmp_x = 1; tmp_y = 0;}
                else if(i == 1) {tmp_ar = around.under;  tmp_x = 0; tmp_y = 1;}
                else if(i == 2) {tmp_ar = around.left;   tmp_x = -1; tmp_y = 0;}
                else if(i == 3) {tmp_ar = around.above;  tmp_x = 0; tmp_y = -1;}

                if(tmp_ar == 1){    //se nella posizione intorno al player c'è un mostro
                    x = search_monster_by_xy(this->lista_mostri, (p.getX()) + tmp_x, (p.getY() + tmp_y));
                    if(x!=NULL){
                        if(!this->map.isTurret(x->mon.getX(), x->mon.getY())){
                            x->mon.SetHp(p.fight(x->mon.getHp(), x->mon.getAtk(), x->mon.getDef()));
                            x->mon.setLook(91 - (int) ((x->mon.getHp() / m_max_hp) * 26.0));
                            if(x->mon.getLook() > 'Z') x->mon.setLook('Z');
                            x = x->next;
                        }else{
                            x->mon.SetHp(p.fight(x->mon.getHp(), x->mon.getAtk(), x->mon.getDef()));
                            x->mon.setLook(123 - (int) ((x->mon.getHp() / t_max_hp) * 26.0));
                            if(x->mon.getLook() > 'z') x->mon.setLook('z');
                            x = x->next;
                        }
                    }
                }
            }
        }

        //update
        if(prev_y != p.getY() || prev_x != p.getX())
			update(map, p, prev_y, prev_x);
        monsterUpdate(map, this->lista_mostri); bulletUpdate(map, lista_proiettili);

        // Draw  //////////////////////////////////////////////////////////
        draw(game_win, map, p, prev_x, prev_y);wrefresh(game_win);

        if(c == mon_speed) {
            drawMonster(game_win, map, this->lista_mostri);
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
        map.setMapChar(0,0, '/');
        mvwprintw(game_win, 0, 0, "%c", map.getMapChar(0,0));

        if(esito != EXIT && esito != GO_TO_SHOP) {
            //se il protagonista muore
            if(p.getHp() <= 0.0)     esito = LOSE, p.SetHp(0.0), drawStats(player_stats_win, startx, starty, p);

            //se il protagonista raccoglie tutte le monete
            else if(this->map.getCoins() == 0)    esito = WIN;

            //il protagonista va al livello successivo
            if(this->map.getCoins() == 0 && (this->map).protagonistInNextPortal())    esito = GO_TO_NEXT;

            //il protagonista va al livello precedente
            if((this->map).protagonistInPrevPortal() && p.getCurrentLevel() != 1)   esito = GO_TO_PREV;
        }
	}
    this->map.clean();
    
    if(esito == LOSE){
        this->map.setMapChar(p.getY(), p.getX(), ' ');
        drawGameover(game_win, game_over_win), getch();
        //aggiorno credentials.txt 
    }
    else if(esito == GO_TO_NEXT)
        this->map.setMapChar(this->map.getHeight() - 3, this->map.getWidth() - 5, ' ');
    else if(esito == GO_TO_PREV)
        this->map.setMapChar(2, 4, ' ');
    else if(esito == GO_TO_SHOP)
        this->map.setMapChar(p.getY(), p.getX(), ' ');

    delwin(game_win);refresh();
    delete lista_proiettili;
    return esito;
}

pbul Game::handleInput(int c, Map& map, Player& giocatore, pbul bullet_list, arnd around, int& e) {
	if(c == ERR) {;/*no tasti premuti dall'utente*/}
	else {
		switch(c)
		{
			case KEY_UP:
                if(around.above == 2)
                {
                    giocatore.takeMoney(1);
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.moveup(map);
				break;

			case KEY_DOWN:
                if(around.under == 2)
                {
                    giocatore.takeMoney(1);
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.movedown(map);
				break;

			case KEY_LEFT:
                if(around.left == 2)
                {
                    giocatore.takeMoney(1);
                    map.setCoins(map.getCoins() - 1);
                }
				giocatore.moveleft(map);
				break;
			case KEY_RIGHT:

                if(around.right == 2)
                {
                    giocatore.takeMoney(1);
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
                break;
            case '1':
                e = GO_TO_SHOP;
                break;
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
        map.setMapChar(tmp3->bul.getY(), tmp3->bul.getX(), '*');
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
	    mvwprintw(win, tmp3->bul.getY(), tmp3->bul.getX(), "%c", '*');
        wrefresh(win);
        tmp3 = tmp3->next;
    }
}

void Game::drawStats(WINDOW *win, int x, int y, Player p){
    box(win, 0, 0);
    mvwprintw(win, 0, 4, "Stats di %s - Lv. %d", p.getNick(), p.getCurrentLevel());
    mvwprintw(win, 2, 3, " Monete : %d     ", p.getMoney());
    mvwprintw(win, 4, 3, "   Vita : %.2f     ", p.getHp());
    mvwprintw(win, 6, 3, "Attacco : %d     ", p.getAtk());
    mvwprintw(win, 8, 3, " Difesa : %d     ", p.getDef());

    if(this->n_mostri > 1)
        mvwprintw(win, 17, 2, "Mancano ancora %d mostri   ", this->n_mostri);
    else if(this->n_mostri == 1)
        mvwprintw(win, 17, 2, "Manca l'ultimo mostro!     ", this->n_mostri);
    else if(this->n_mostri == 0)
        mvwprintw(win, 17, 2, "Mostri eliminati!          ");

    if(this->map.getCoins() > 1)
        mvwprintw(win, 18, 2, "Mancano ancora %d monete   ", this->map.getCoins());
    else if(this->map.getCoins() == 1)
        mvwprintw(win, 18, 2, "Manca l'ultima moneta!     ", this->map.getCoins());
    else if(this->map.getCoins() == 0)
        mvwprintw(win, 18, 2, "Livello superato!       ");

    wrefresh(win);
}

void Game::drawGameover(WINDOW* game_win, WINDOW* game_over_win){
    box(game_over_win, 0, 0);
    mvwprintw(game_over_win, 1, 1, "Game Over");
    wrefresh(game_over_win);
    while(getchar() != 'r')
    {
        mvwprintw(game_over_win, 1, 1, "Game Over");
        wrefresh(game_over_win);
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

Map Game::getMap(){
    return this->map;
}

void Game::setMap(Map mappa){
    this->map = mappa;
}

pmon Game::getListaMostri(){
    return this->lista_mostri;
}

void Game::setListaMostri(pmon l){
    this->lista_mostri = l;
}

int Game::getNMostri(){
    return this->n_mostri;
}

void Game::setNMostri(int n){
    this->n_mostri = n;
}

void Game::game_exit(){
    char text[11];
    strcpy(text, "Goodbye...");
    clear();
    timed_print(text, 11, 100000, LINES/3, COLS/2 - 5);

    getch();
    endwin();
    exit(0);
}
