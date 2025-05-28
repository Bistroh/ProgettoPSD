#ifndef UTENTE_H
#define UTENTE_H
#include "Coda_StoricoUtente.h"

typedef struct s_utente *Utente;

Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password,char *telefono);
char *ottieniCF(Utente utente);
char *ottieniNome(Utente utente);
char *ottieniCognome(Utente utente);
char *ottieniEmail(Utente utente);
char *ottieniTelefono(Utente utente);
char *ottieniPassword(Utente utente);
void stampaUtente(Utente u);
Coda ottieniStorico(Utente u);
void distruggiUtente(Utente u);

#endif //UTENTE_H


