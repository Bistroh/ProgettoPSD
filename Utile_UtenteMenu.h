#ifndef UTILE_UTENTEMENU_H
#define UTILE_UTENTEMENU_H
#include "Utente.h"
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
int codiceFiscaleValido(const char *CF);
List prenotazioneAuto(List l, Utente u, AutoHashTable tabAuto) ;
void visualizzaAutoDisponibili(AutoHashTable ht) ;
void visualizzaPrenotazioniPerUtente(List l, const char *CF) ;
void visualizzaStorico();
List switchUtente(int scelta, Utente u, List l, AutoHashTable tabAuto);
int menuUtente();

#endif //UTILE_UTENTEMENU_H
