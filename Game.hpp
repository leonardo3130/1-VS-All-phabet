#include "Monster.hpp"

#define NUM_COLORS 8

#define EXIT -3
#define IN_GAME 0
#define WIN 1
#define LOSE -1
#define GO_TO_NEXT 2
#define GO_TO_PREV -2
#define GO_TO_SHOP 3

using namespace std;

class Game {
	private:
		pbul handleInput(int c, Map& map, Player& giocatore, pbul bul_list, arnd around, int& e);
		void draw(WINDOW* win, Map& map, Character& protagonist, int prev_x, int prev_y);
		void drawMonster(WINDOW* win, Map& map, pmon monster_list);
		void bulletUpdate(Map &map, pbul bul_list);
		void update(Map& map, Character& protagonist, int prev_y, int prev_x) ;
		void monsterUpdate(Map &map, pmon monster_list);
		void drawBullet(WINDOW *win, Map &map, pbul bul_list);
		void drawStats(WINDOW *win, int x, int y, Player p);
		void drawGameover(WINDOW *win, WINDOW *game_over_win);
		void drawCommands(WINDOW *win);

		Map map;
		int n_mostri, n_torri;
		pmon lista_mostri;

	public:
		Game(char filePath[] = NULL, int atk=0, int def=0 ,int livello=1);
		int run(Player &p);
		Map getMap();
		void setMap(Map mappa);
		pmon getListaMostri();
		void setListaMostri(pmon l);
		int getNMostri();
		void setNMostri(int n);
};
