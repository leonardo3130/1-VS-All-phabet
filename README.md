## 1 vs All-phabet
Progetto di gruppo in cui viene implementato un gioco tramite la libreria ncurses;
Il player deve migliorare il suo punteggio passando al livello successivo, tuttavia per poterlo fare 
deve raccogliere tutte le monete. I nemici gli renderanno questa missione più difficile.
Quest'ultimi possono essere di 2 tipi:
- mostri: riconoscibili perché si muovono e sono rappresentati da una lettera maiscola;
- torrette: rappresentate da una lettera minuscola e incapaci di muoversi.
Il giocatore può infliggere danni alle torrette o ai mostri entrandovi in contatto o sprando ad essi.
Le torrette hanno molta più vita dei mostri, ma possono fare danni solo sparando, 
non tramite il contatto.

# Eseguire tramite Makefile
Makefile compila ed esegue il gioco  e poi cancella eseguibile (prima di consegnare va modificato)
```sh
make
```
# Rimozione Partite Salvate
Si utilizza il seguente comando del makefile: 
```sh
make reset
```
# Come si gioca
Il movimento avviene con le frecce direzioni, gli spari con i tasti w,a,s,d. 
Il tasto 1 è riservato all'apertura del livello market, q è il tasto per l'uscita dallo shop
e dal gioco, infine r serve per ricominciare una nuova partita dopo la morte.

# Sviluppatori
- Fiorelllino Andrea
- Silvestri Luca
- Po Leonardo

# Link Relazione del Progetto
```sh
https://docs.google.com/document/d/1qKrCzQvuM9lWxvQD8znN8tCQDLdZqcdMxinh7FZyy0o/edit?usp=sharing
```
