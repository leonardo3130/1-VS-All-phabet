#include <cmath> 
#include <ctime>
#define MAX_H 40
#define MAX_W 80
class Map {
        protected:
                int height;
                int width;
                char matrix[MAX_H][MAX_W];
        public:	
		Map(int h, int w) {
			srand(time(0));
			
			//controlli errori di input
			if(abs(h) > MAX_H) this->height = MAX_H;
			else this->height = abs(h);
			if(abs(w) > MAX_W) this->width = MAX_W;
			else this->width = abs(w);
			
			//caratteri per i bordi della mappa
			for(int i = 0 ; i < this->height ; i++)
			{
				for(int j = 0 ; j < this->width ; j++)
				{
					if((i == 0 && j == 0) || (i == 0 && j == this->width - 1) || (i == this->height - 1 && j == 0) || (i == this->height - 1 && j == this->width - 1))
						this->matrix[i][j] = '.'; //angoli della mappa
					else if(i == 0 || i == this->height - 1) this->matrix[i][j] = '_'; //bordi sopra e sotto
					else if(j == 0 || j == this->width - 1) this->matrix[i][j] = '|'; //bordi laterali
					else this->matrix[i][j] = ' '; //spazi interni;
				}
			}

			//costruzione casuale mura interne alla mappa
			int walls = (this->width + this->height) * 3 / 2; 
			int len = (walls / 15);

			while(walls - len > 0)
			{
				int y, x, prev_y, prev_x, orientation;
				int tmp = len;
				orientation = rand() % 2;
				while(tmp > 0)
				{
					//generazione posizione primo muro
					if(tmp == len)
					{	
						do 
						{
							y = rand() % (this->height - 5) + 2;
							x = rand() % (this->width - 5) + 2;
						}while(this->matrix[y][x] != ' ');
					}
					else //generazione posizione mura successive 
					{
						int add_y, add_x;
						do
						{
							add_y = rand() % 3 - 1; // -1 o 0 o 1
							add_x = rand() % 3 - 1; // -1 o 0 o 1
							
							//controlli per decidere le prossime cordinate
							if(orientation) 
							{
								y = prev_y;
						       		x = prev_x + add_x;
							}
							else
							{
						        	y = prev_y + add_y;
						       		x = prev_x;
							}
							//controlli per evitare di uscire dalla mappa o di andare sui bordi
							if(x <= 0 || x >= this->width - 1 || y <= 0 || y >= this->height - 1)
							{
								y = rand() % (this->height - 5) + 2;
                                                        	x = rand() % (this->width - 5) + 2;
							}

						}while(this->matrix[y][x] != ' ');
					}

					//controlli per decidere come orientare: | _ 
					if(orientation) this->matrix[y][x] = '_';
					else this->matrix[y][x] = '|';
			
					prev_y = y;
					prev_x = x;
			
					tmp--;	
				}
				walls -= len;
			}
		}
		char getMapChar(int y, int x)
		{
			return this->matrix[y][x];
		}
		int getWidth()
		{
			return this->width;
		}
		int getHeight()
		{
			return this->height;
		}
};
