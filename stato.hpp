//in questa libreria sono definite le funzione utili a
//effettuare salvataggi di stato su appositi file di testo
#include <iostream>
#include <fstream>
#include "Player.hpp"

using namespace std;



int main() {
    ofstream outputFile;                            /* Dichiarazione di tipo */
    outputFile.open("file2.txt");                   /* Apertura del file */
    outputFile << "Prova di scrittura su file";
    outputFile.close();
    return 0;
}

void save_data(Player p){

}