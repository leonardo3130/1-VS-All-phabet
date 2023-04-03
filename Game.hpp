#include <iostream>
#include <Map.hpp>
#include <Character.hpp>
#include <Player.hpp>

using namespace std;

class Game {
	protected:
		Map map;
		Character character;
	public:
		Game(Map m, Character c);
		void run(); //esecuzione gioco, grafica, game loop ecc...
}
