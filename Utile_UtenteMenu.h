#ifndef UTILE_UTENTEMENU_H
#define UTILE_UTENTEMENU_H
#include "Utente.h"
#include "List_Prenotazione.h"
#include "HashTbAuto.h"

/* * Funzione: codiceFiscaleValido
 * ------------------------------
 * Parametri:
 * - `CF`: il codice fiscale da verificare.
 * ------------------------------
 * Precondizioni:
 * - `CF` deve essere una stringa non vuota di 16 caratteri.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se il codice fiscale è valido, 0 altrimenti.
 * ------------------------------
 * Side Effects:
 * Nessuno.
 */
int codiceFiscaleValido(const char *CF);

/* * Funzione: visualizzaAutoDisponibiliConParametri
 * ------------------------------
 * Parametri:
 * - `ht`: la tabella hash delle auto.
 * - `giornoInizio`: il giorno di inizio della prenotazione (1 = lunedì, ..., 7 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (1 = lunedì, ..., 7 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * ------------------------------
 * Precondizioni:
 * - `ht` deve essere una tabella hash valida contenente le auto disponibili.
 * ------------------------------
 * Side Effects:
 * - Stampa le auto disponibili in un formato tabellare in base ai parametri specificati.
 * ------------------------------
 */
void visualizzaAutoDisponibiliConParametri(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/* * Funzione: prenotazioneAuto
 * ------------------------------
 * Parametri:
 * - `l`: la lista delle prenotazioni.
 * - `tabAuto`: la tabella hash delle auto disponibili.
 * - `CF`: il codice fiscale dell'utente che prenota.
 * - `targa`: la targa dell'auto da prenotare.
 * - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine`: i parametri della prenotazione.
 * - `stato`: puntatore a un intero per indicare lo stato della prenotazione (0 = fallita, 1 = riuscita).
 * ------------------------------
 * Precondizioni:
 * - `CF` deve essere un codice fiscale valido.
 * - `targa` deve essere una targa valida di un'auto registrata nella tabella hash.
 * ------------------------------
 * Postcondizioni:
 * - Aggiunge una nuova prenotazione alla lista se i parametri sono validi e l'auto è disponibile.
 * Restituisce la lista aggiornata delle prenotazioni.
 */
Lista prenotazioneAuto(Lista l, AutoHashTB tabAuto, char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, int *stato);

/* * Funzione: inserimentoPrenotazione
 * ------------------------------
 * Parametri:
 * - `CF`: il codice fiscale dell'utente che prenota.
 * - `targa`: la targa dell'auto da prenotare.
 * - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine`: puntatori agli interi per i parametri della prenotazione.
 * - `u`: l'utente che sta effettuando la prenotazione.
 * ------------------------------
 * Precondizioni:
 * - `CF` deve essere un codice fiscale valido.
 * - `targa` deve essere una targa valida di un'auto registrata nella tabella hash.
 * ------------------------------
 * Postcondizioni:
 * - Chiede all'utente di inserire i parametri della prenotazione e li memorizza nei puntatori forniti.
 * Restituisce 1 se l'inserimento è riuscito, 0 altrimenti.
 */
int inserimentoPrenotazione(char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, Utente u);

/* * Funzione: visualizzaAutoDisponibili
 * ------------------------------
 * Parametri:
 * - `ht`: la tabella hash delle auto.
 * --------------------------------
 * Precondizioni:
 * - `ht` deve essere una tabella hash valida contenente le auto disponibili.
 * ------------------------------
 * Postcondizioni:
 * - Chiede all'utente di inserire i parametri per la visualizzazione delle auto disponibili
 * e chiama `visualizzaAutoDisponibiliConParametri` per mostrare le auto disponibili.
 * Restituisce le auto disponibili in un formato tabellare.
 * ------------------------------
 * Side Effects:
 * Stampa le auto disponibili sulla console in base ai parametri inseriti dall'utente.
 * ------------------------------
 */
void visualizzaAutoDisponibili(AutoHashTB ht) ;

/* * Funzione: visualizzaPrenotazioniPerUtente
 * ------------------------------
 * Parametri:
 * - `l`: la lista delle prenotazioni.
 * - `CF`: il codice fiscale dell'utente di cui visualizzare le prenotazioni.
 * ------------------------------
 * Precondizioni:
 * - `CF` deve essere un codice fiscale valido.
 * ------------------------------
 * Side Effects:
 * - Stampa le prenotazioni dell'utente specificato in un formato tabellare.
 */
void visualizzaPrenotazioniPerUtente(Lista l, const char *CF) ;

/* * Funzione: visualizzaStorico
 * ------------------------------
 * Parametri:
 * - Nessuno.
 * ------------------------------
 * Precondizioni:
 * - L'utente deve avere uno storico di prenotazioni.
 * ------------------------------
 * Side Effects:
 * - Stampa lo storico delle prenotazioni dell'utente in un formato tabellare.
 */
void visualizzaStorico();

/* * Funzione: switchUtente
 * ------------------------------
 * Parametri:
 * - `scelta`: la scelta dell'utente nel menu.
 * - `u`: l'utente che sta effettuando la prenotazione.
 * - `l`: la lista delle prenotazioni.
 * - `tabAuto`: la tabella hash delle auto disponibili.
 * ------------------------------
 * Precondizioni:
 * - `u` deve essere un utente valido.
 * ------------------------------
 * Postcondizioni:
 * - Gestisce le operazioni che l'utente può effettuare in base alla scelta selezionata.
 * Restituisce la lista aggiornata delle prenotazioni.
 */
Lista switchUtente(int scelta, Utente u, Lista l, AutoHashTB tabAuto);

/* * Funzione: menuUtente
 * ------------------------------
 * Parametri:
 * - Nessuno.
 * ------------------------------
 * Precondizioni:
 * - L'utente deve essere autenticato.
 * ------------------------------
 * Postcondizioni:
 * - Mostra il menu delle opzioni per l'utente e gestisce le scelte dell'utente.
 * Restituisce la scelta dell'utente.
 */
int menuUtente();

/* * FUnzione calcolaPrezziPrenotazioni
 * ------------------------------
 * Parametri:
 * - `prenotazioni`: la lista delle prenotazioni.
 * - `u`: l'utente di cui calcolare i prezzi.
 * - `ht`: la tabella hash delle auto disponibili.
 * ------------------------------
 * Precondizioni:
 * - `u` deve essere un utente valido.
 * ------------------------------
 * Postcondizioni:
 * - Calcola il totale dei prezzi delle prenotazioni dell'utente e lo restituisce.
 */
float calcolaPrezziPrenotazioni(Lista prenotazioni, Utente u, AutoHashTB ht);

/* * Funzione: calcolaPrezzoFinale
 * ------------------------------
 * Parametri:
 * - `a`: l'auto di cui calcolare il prezzo.
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * ------------------------------
 * Precondizioni:
 * - `a` deve essere un'auto valida.
 * ------------------------------
 * Postcondizioni:
 * - Calcola il prezzo finale della prenotazione dopo aver applicato gli sconti.
 * Restituisce il prezzo finale della prenotazione.
 */
float calcolaPrezzoFinale(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

#endif //UTILE_UTENTEMENU_H
