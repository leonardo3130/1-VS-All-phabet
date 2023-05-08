#include "Player.hpp"

Player::Player() : Character('1'){
}

Player::Player(char* nick, char* psw, char l='1') : Character(l){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
}


int Player::fight(int m_hp, int m_atk, int m_def){
    this->hp -= 0.005;  //1*(m_atk)/(this->def);
    m_hp -= 0.005;  //1*(this->def)/(m_def);
    return m_hp;
}

arnd Player::check_around(Map& m){
    arnd around;    //0 vuoto, 1 mostro, 2 moneta
    char x;

    x = m.getMapChar(this->y, (this->x) + 1);
    if(x == ' ')
        around.right = 0;
    else if(x >= 'A' && x <= 'Z')
        around.right = 1;
    else if(x == '@')
        around.right = 2;


    x =m.getMapChar((this->y) + 1, this->x);
    if(x == ' ')
        around.under = 0;
    else if(x >= 'A' && x <= 'Z')
        around.under = 1;
    else if(x == '@')
        around.under = 2;


    x = m.getMapChar(this->y, (this->x) - 1);
    if(x == ' ')
        around.left = 0;
    else if(x >= 'A' && x <= 'Z')
        around.left = 1;
    else if(x == '@')
        around.left = 2;


    x = m.getMapChar((this->y) - 1, this->x);
    if(x == ' ')
        around.above = 0;
    else if(x >= 'A' && x <= 'Z')
        around.above = 1;
    else if(x == '@')
        around.above = 2;


    return around;
}

char* Player::getNick(){
    return this->nick;
}

int Player::getMoney(){
    return this->money;
}

void Player::takeMoney(int value){
    this->money = money + value;
}

//menu per scegliere se effettuare login, sign in o uscire dal gioco
int Player::choice_menu() {
    int choice = 0;
    string choices[3] = {"Login", "Sign in", "Exit"};
    int highlights = 0;

    WINDOW *menu = newwin(50, 110 , LINES/2 -25, COLS/2 -55);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);

    keypad(menu, true);

    mvwprintw(menu, 4, 6, " ____                          _______  __  __                 __            __            __   ");
    mvwprintw(menu, 5, 6, "|_   |      .--.--..-----.    |   _   ||  ||  | ______ .-----.|  |--..---.-.|  |--..-----.|  |_ ");
    mvwprintw(menu, 6, 6, " _|  |_     |  |  ||__ --|    |       ||  ||  ||______||  _  ||     ||  _  ||  _  ||  -__||   _|");
    mvwprintw(menu, 7, 6, "|______|     \\___/ |_____|    |___|___||__||__|        |   __||__|__||___._||_____||_____||____|");
    mvwprintw(menu, 8, 6, "                                                       |__|                                     ");



    mvwprintw(menu, 16, 43, "  _              _");
    mvwprintw(menu, 17, 43, " | |   ___  __ _(_)_ _");
    mvwprintw(menu, 18, 43, " | |__/ _ \\/ _` | | '  \\");
    mvwprintw(menu, 19, 43, " |____\\___/\\__, |_|_||_|");
    mvwprintw(menu, 20, 43, "           |___/");







    while (choice != 10){
        for(int i=23; i< 26; i++){
            if(i-23 == highlights)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i, 55, choices[i-23].c_str());
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

//get credentials from the terminal
void Player::getCredentials(char username[], char password[]) {
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


//funzione per creare un nuovo account
bool Player::signIn(char *user, char *psw){
	bool isCorrect = false;
    char filename[50], mkdir[50];

    strcpy(mkdir, "mkdir Archivio/");
    system(strcat(mkdir, user));

    strcpy(filename, "Archivio/");
    strcat(filename, user);
    strcat(filename, "/credentials.txt");

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
bool Player::login(char *user, char *psw, int& curr_level){
    char filename[50];
    strcpy(filename, "Archivio/");
    strcat(filename, user);
    strcat(filename, "/credentials.txt");

	ifstream input_file(filename);
	bool exists;

    if (input_file.is_open()) {
		//leggo la psw
        char line[50];
		input_file >> line;

		//se la psw è giusta prendo le informazioni del player
		if(strcmp(line, psw) == 0)	{
			input_file >> this->hp;
			input_file >> this->atk;
			input_file >> this->def;
			input_file >> this->money;
            input_file >> curr_level;
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




void Player::saveStats(int curr_level){
    char filename[50];
    strcpy(filename, "Archivio/");
    strcat(filename, this->nick);
    strcat(filename, "/credentials.txt");

    ofstream credenziali;
	credenziali.open(filename);

	credenziali << this->psw << endl;
	credenziali << this->hp << endl;
	credenziali << this->atk << endl;
	credenziali << this->def << endl;
	credenziali << this->money << endl;
    credenziali << curr_level << endl;
	credenziali.close();
}

void Player::setCredentials(char *user, char *psw){
    strcpy(this->nick, user), strcpy(this->psw, psw);

}
