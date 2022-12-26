class character{
  protected:
    int x;      //coordinata x
    int y;      //coordinata y
    char look;  //lettera usata per identificare il personaggio
    int hp;     //numero totale di hp
    int atk;    //valore attacco (contatto)
    bool gun;   //il personaggio spara?
                //(no valore di difesa perchè ai mostri non serve: non comprano aramture)
  
  public:
    //costruttore
    character(int x = 0, int y = 0, char look = '/', int hp = 1, int atk = 1, bool gun = false);      
    
    //bool xy: true->asse x, false->asse y; int val: celle in una mossa
    void move(bool xy, int val = 1);  };
