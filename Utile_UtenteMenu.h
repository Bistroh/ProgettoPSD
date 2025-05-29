#ifndef UTILE_UTENTEMENU_H
#define UTILE_UTENTEMENU_H
#include "Utente.h"
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
int codiceFiscaleValido(const char *CF);
void visualizzaAutoDisponibiliConParametri(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine);
Lista prenotazioneAuto(Lista l, AutoHashTB tabAuto, char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, int *stato);
int inserimentoPrenotazione(char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, Utente u);
void visualizzaAutoDisponibili(AutoHashTB ht) ;
void visualizzaPrenotazioniPerUtente(Lista l, const char *CF) ;
void visualizzaStorico();
Lista switchUtente(int scelta, Utente u, Lista l, AutoHashTB tabAuto);
int menuUtente();
float calcolaPrezziPrenotazioni(Lista prenotazioni, Utente u, AutoHashTB ht);
float calcolaPrezzoFinale(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

#endif //UTILE_UTENTEMENU_H
