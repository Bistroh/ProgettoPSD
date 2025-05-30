#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

//
typedef struct s_prenotazione* Prenotazione;
#include <stdio.h>

/*
* Funzione: creaPrenotazione
* -----------------------------
* Parametri:
* - `CF`: il codice fiscale del cliente.
* - `targa`: la targa del veicolo prenotato.
* - `giornoInizio`: il giorno di inizio della prenotazione.
* - `giornoFine`: il giorno di fine della prenotazione.
* - `oraInizio`: l'ora di inizio della prenotazione.
* - `oraFine`: l'ora di fine della prenotazione.
* -----------------------------
* Precondizioni:
* - `CF` deve essere una stringa valida (non vuota).
* - `targa` deve essere una stringa valida (non vuota).
* - `giornoInizio` e `giornoFine` devono essere compresi tra 0 e 6 (dove 0 = Lunedì, 6 = Domenica).
* - `oraInizio` deve essere compreso tra 0 e 23.
* - `oraFine` deve essere compreso tra 1 e 24 (dove 24 indica la mezzanotte del giorno successivo).
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore a una nuova struttura `s_prenotazione` allocata dinamicamente,
*  * inizializzata con i valori forniti in input.
* -----------------------------
* Side Effects:
* la variabile struttura `Prenotazione` viene allocata dinamicamente in memoria.
* -----------------------------
 */
Prenotazione creaPrenotazione(char *CF, char *targa, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/*
* Funzione: ottieniIDPrenotazione
* -----------------------------
* Restituisce l'ID della prenotazione.
* * Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere l'ID.
* -----------------------------
* * Precondizioni:
* - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
* -----------------------------
* * Postcondizioni:
* - Restituisce l'ID della prenotazione.
* -----------------------------
 */
int ottieniIDPrenotazione(Prenotazione prenotazione);

/*
* Funzione: ottieniCFPrenotazione
* -----------------------------
* Restituisce il codice fiscale associato alla prenotazione.
* * Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere il codice fiscale.
* -----------------------------
* * Precondizioni:
* - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
* -----------------------------
* * Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta il codice fiscale della prenotazione.
* -----------------------------
* * Side Effects:
* Nessuno.
* -----------------------------
 */
char *ottieniCFPrenotazione(Prenotazione prenotazione);

/*
* Funzione: ottieniTargaPrenotazione
* -----------------------------
* Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere la targa.
* -----------------------------
* * Precondizioni:
* - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
* -----------------------------
* * Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta la targa del veicolo prenotato.
* -----------------------------
* * Side Effects:
* Nessuno.
* -----------------------------
 */
char *ottieniTargaPrenotazione(Prenotazione prenotazione);

/*
 * Funzione: stampaPrenotazione
 * -----------------------------
 * Parametri:
 * - `prenotazione`: puntatore alla prenotazione da stampare.
 * -----------------------------
 * Precondizioni:
 * - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * -----------------------------
 * Side Effects:
 * Stampa le informazioni della prenotazione sulla console.
 * -----------------------------
 */
void stampaPrenotazione(Prenotazione prenotazione);

/*
 * Funzione: stampaPrenotazioneSuFile
 * -----------------------------
 * Parametri:
 * - `prenotazione`: puntatore alla prenotazione da stampare.
 * - `fp`: puntatore al file in cui scrivere i dettagli della prenotazione.
 * -----------------------------
 * Precondizioni:
 * - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * - `fp` deve essere un file aperto in modalità scrittura.
 * -----------------------------
 * Side Effects:
 * - Stampa i dettagli della prenotazione, inclusi ID, codice fiscale, targa e periodo, nel file specificato.
 */
void ottieniPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine);

/*
 * Funzione: copiaPrenotazione
 * -----------------------------
 * Parametri:
 * - `originale`: puntatore alla prenotazione da copiare.
 * -----------------------------
 * Precondizioni:
 * - `originale` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * -----------------------------
 * Side Effects:
 * - Restituisce un nuovo puntatore a una copia della prenotazione originale.
 */
void stampaPrenotazione(Prenotazione prenotazione);

/* * Funzione: stampaPrenotazioneSuFile
 * -----------------------------
 * Parametri:
 * - `prenotazione`: puntatore alla prenotazione da stampare.
 * - `fp`: puntatore al file in cui scrivere i dettagli della prenotazione.
 * -----------------------------
 * Precondizioni:
 * - `prenotazione` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * - `fp` deve essere un file aperto in modalità scrittura.
 * -----------------------------
 * Side Effects:
 * - Stampa i dettagli della prenotazione, inclusi ID, codice fiscale, targa e periodo, nel file specificato.
 */
void stampaPrenotazioneSuFile(Prenotazione prenotazione, FILE *fp);

/*
 * Funzione: distruggiPrenotazione
 * -----------------------------
 * Parametri:
 * - `p`: puntatore alla prenotazione da distruggere.
 * -----------------------------
 * Precondizioni:
 * - `p` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * -----------------------------
 * Postcondizioni:
 * - Libera la memoria allocata per la prenotazione, prevenendo memory leak.
 */
Prenotazione copiaPrenotazione(Prenotazione originale);

/* * Funzione: distruggiPrenotazione
 * -----------------------------
 * Parametri:
 * - `p`: puntatore alla prenotazione da distruggere.
 * -----------------------------
 * Precondizioni:
 * - `p` deve essere un puntatore valido a una struttura `s_prenotazione` creata con `creaPrenotazione`.
 * -----------------------------
 * Side Effects:
 * - Libera la memoria allocata per la prenotazione, prevenendo memory leak.
 */
void distruggiPrenotazione(Prenotazione p);

#endif // PRENOTAZIONE_H
