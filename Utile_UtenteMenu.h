#ifndef UTILE_UTENTEMENU_H
#define UTILE_UTENTEMENU_H
#include "Utente.h"
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
int codiceFiscaleValido(const char *CF);
Lista prenotazioneAuto(Lista l, Utente u, AutoHashTB tabAuto) ;
void visualizzaAutoDisponibili(AutoHashTB ht) ;
void visualizzaPrenotazioniPerUtente(Lista l, const char *CF) ;
void visualizzaStorico();
Lista switchUtente(int scelta, Utente u, Lista l, AutoHashTB tabAuto);
int menuUtente();
void calcolaPrezziPrenotazioni(Lista prenotazioni, Utente u, AutoHashTB ht);

#endif //UTILE_UTENTEMENU_H
