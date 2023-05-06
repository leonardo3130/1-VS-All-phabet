#include "Player.hpp"

Player::Player(){}

Player::Player(char* nick, char* psw, int m, char l) : Character(l){
    strcpy(this->nick, nick);
    strcpy(this->psw, psw);
    this->money = m;
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

//funzione per creare un nuovo account
bool Player::signIn(char *psw, char *filename){
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
bool Player::login(char *user, char *psw, char *filename){
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
