class Player{
    protected:
        char nick[20];  //nome del player
        char look;      //lettera usata per identificare il personaggio 
        int hp;         //numero totale di hp
        int def;        //valore difesa
        int atk;        //valore attacco
        int x;          //coordinata x
        int y;          //coordinata y

    public:
        // costruttore
        Player(char nick[], char look = 'S', int hp = 10, int def = 2, int atk = 2);

        //mancano metodi getter e setter
        void setHp(int new_hp);
        int getHp();
        
};