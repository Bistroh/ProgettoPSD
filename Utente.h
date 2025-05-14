#ifndef UTENTE_H
#define UTENTE_H

typedef struct s_utente *Utente;

Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password,char *telefono);
char *getCF(Utente utente);
char *getNome(Utente utente);
char *getCognome(Utente utente);
char *getEmail(Utente utente);
char *getTelefono(Utente utente);
char *getPassword(Utente utente);
void stampaUtente(Utente u);
void distruggiUtente(Utente u);

#endif //UTENTE_H


