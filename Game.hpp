#include "Monster.hpp"

#define NUM_COLORS 8

// costanti ritornate da run() utili al main per gestire l'interazione col player
#define EXIT -3
#define IN_GAME 0
#define WIN 1
#define LOSE -1
#define GO_TO_NEXT 2
#define GO_TO_PREV -2
#define GO_TO_SHOP 3

using namespace std;

class Game {
	protected:
		pbul handleInput(int c, Map& map, Player& giocatore, pbul bul_list, arnd around, int& e);	//funzione che gestisce i controlli da tastiera
		void drawPlayer(WINDOW* win, Map& map, Player& protagonist, int prev_x, int prev_y);		//disegna il player
		void drawMonster(WINDOW* win, Map& map, pmon monster_list);									//disegna i mostri sulla mappa
		void bulletUpdate(Map &map, pbul bul_list);													//aggiorna la posizione dei proiettili
		void update(Map& map, Player& protagonist, int prev_y, int prev_x) ;						//aggiorna la mappa
		void monsterUpdate(Map &map, pmon monster_list);											//aggiorna la posizione dei mostri nella mappa
		void drawBullet(WINDOW *win, Map &map, pbul bul_list);										//disegna i proiettili
		void drawStats(WINDOW *win, int x, int y, Player p);										//disegna il box del gioco in alto a destra
		void drawGameover(WINDOW *win, WINDOW *game_over_win);										//disegna il box del game over	
		void drawCommands(WINDOW *win);																//disegna il box in cui vengono descritti tutti i comandi

		Map map;					//attributo della Mappa del game
		int n_mostri, n_torri;		//attributi del numero dei mostri e delle torrette
		pmon lista_mostri;			//lista dei mostri (contiene sia torrette che mostri classici)

	public:
		Game(char filePath[] = NULL, int atk=0, int def=0 ,int livello=1);		//costruttore del Game
		int run(Player &p);														//metodo che gestisce tutto il gioco in cui risiede il game loop
		Map getMap();															//ritorna l'attributo Map
		void setMap(Map mappa);													//setta l'attributo Map
		pmon getListaMostri();													//ritorna l'attributo della lista mostri
		void setListaMostri(pmon l);											//setta l'attributo della lista mostri
		int getNMostri();														//ritorna l'attributo del numero dei mostri 
		void setNMostri(int n);													//setta l'attributo del numero dei mostri 
};
