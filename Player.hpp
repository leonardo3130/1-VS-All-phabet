class Player{
    protected:
        char nick[20];  //nome del player
        int hp;         //numero totale di hp
        int def;        //valore difesa
        int atk;        //valore attacco

    public:
        Player(char nick[], int hp = 10, int def = 2, int atk = 2);

        //mancano metodi getter e setter
        void setHp(int new_hp);
        int getHp();
        
};