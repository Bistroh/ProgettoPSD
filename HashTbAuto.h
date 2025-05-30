#ifndef HASHTABLEAUTO_H
#define HASHTABLEAUTO_H

#include "Auto.h"
#include "uthash.h"

/*
* La struttura AutoRecord rappresenta un record nella tabella hash per le auto.
 */
typedef struct AutoRecord AutoRecord;
typedef AutoRecord* AutoHashTB;

/*
* Funzione: creaAutoHashTB
* -----------------------------
* Parametri:
* - Nessuno.
* -----------------------------
* Precondizioni:
* - Nessuna.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore a una nuova tabella hash per le auto, inizializzata a NULL.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
AutoHashTB creaAutoHashTB();

/*
* Funzione: inserisciAuto
* -----------------------------
* Parametri:
* - `ht`: puntatore alla tabella hash in cui inserire l'auto.
* - `a`: l'auto da inserire.
* -----------------------------
* Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce 1 se l'inserimento è riuscito, 0 se l'auto è già presente.
* -----------------------------
* Side Effects:
* Inserisce l'auto nella tabella hash, allocando memoria per il record.
* -----------------------------
 */
int inserisciAuto(AutoHashTB *ht, Auto a);

/*
* Funzione: cercaAuto
* -----------------------------
* Parametri:
* - `ht`: la tabella hash in cui cercare l'auto.
* - `targa`: la targa dell'auto da cercare.
* -----------------------------
* Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* - `targa` deve essere una stringa non vuota che rappresenta la targa dell'auto.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore all'auto se trovata, altrimenti NULL.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
Auto cercaAuto(AutoHashTB ht, const char *targa);

/*
* Funzione: rimuoviAuto
* -----------------------------
* Parametri:
* - `ht`: puntatore alla tabella hash da cui rimuovere l'auto.
* - `targa`: la targa dell'auto da rimuovere.
* -----------------------------
* Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* - `targa` deve essere una stringa non vuota che rappresenta la targa dell'auto.
* -----------------------------
* Postcondizioni:
* - Rimuove l'auto dalla tabella hash e restituisce un puntatore all'auto rimossa se trovata, altrimenti NULL.
* -----------------------------
* Restituisce:
* - Un puntatore all'auto rimossa se trovata, altrimenti NULL.
 */
Auto rimuoviAuto(AutoHashTB *ht, const char *targa);

/*
* Funzione: distruggiAutoHashTB
* -----------------------------
* Parametri:
* - `ht`: puntatore alla tabella hash da distruggere.
* -----------------------------
* Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* -----------------------------
* Side Effects:
* - Libera la memoria allocata per la tabella hash e per ogni auto.
* -----------------------------
* Restituisce:
* - Nessuno.
* -----------------------------
 */
void distruggiAutoHashTB(AutoHashTB *ht);

/*
* Funzione: stampaAutoHashTB
* -----------------------------
* * Parametri:
* - `ht`: la tabella hash da cui stampare le auto.
* -----------------------------
* Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* -----------------------------
* * Side Effects:
* - Stampa le informazioni delle auto nella tabella hash.
* -----------------------------
 */
void stampaAutoHashTB(AutoHashTB ht);

/*
* Funzione: stampaTabellaDiHashPerDisp
* -----------------------------
* * Parametri:
* - `ht`: la tabella hash da cui stampare le auto.
* - `giornoInizio`: il giorno di inizio dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `giornoFine`: il giorno di fine dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `oraInizio`: l'ora di inizio dell'intervallo (0-23).
* - `oraFine`: l'ora di fine dell'intervallo (1-24, dove 24 indica la mezzanotte del giorno successivo).
* -----------------------------
* * Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* * - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine` devono essere valori validi:
*  - `giornoInizio` e `giornoFine` devono essere compresi tra 0 e 6.
* * - `oraInizio` deve essere compreso tra 0 e 23.
* * - `oraFine` deve essere compreso tra 1 e 24.
* -----------------------------
* * Side Effects:
* - Stampa le auto disponibili nell'intervallo specificato.
* -----------------------------
* Restituisce:
* - Nessuno.
* -----------------------------
 */
void stampaTabellaDiHashPerDisp(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/*
* Funzione: reimpostaDisponibilitaTutteLeAuto
* -----------------------------
* * Parametri:
* - `ht`: la tabella hash delle auto da reimpostare.
* -----------------------------
* * Precondizioni:
* - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
* -----------------------------
* * Side Effects:
* - Reimposta la disponibilità di tutte le auto nella tabella hash a disponibile (True).
* -----------------------------
* Restituisce:
* - Nessuno.
* -----------------------------
 */
void reimpostaDisponibilitaTutteLeAuto(AutoHashTB ht);

/*
 * Funzione: stampaTabellaDiHashPerDispFile
 * -----------------------------
 * Parametri:
 * - `ht`: la tabella hash da cui stampare le auto.
 * - `giornoInizio`: il giorno di inizio dell'intervallo (0 = Lunedì, 6 = Domenica).
 * - `giornoFine`: il giorno di fine dell'intervallo (0 = Lunedì, 6 = Domenica).
 * - `oraInizio`: l'ora di inizio dell'intervallo (0-23).
 * - `oraFine`: l'ora di fine dell'intervallo (1-24, dove 24 indica la mezzanotte del giorno successivo).
 * - `fp`: il file in cui scrivere le informazioni delle auto disponibili.
 * -----------------------------
 * * Precondizioni:
 * - `ht` deve essere un puntatore valido a una tabella hash creata con `creaAutoHashTB`.
 * - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine` devono essere valori validi:
 *  - `giornoInizio` e `giornoFine` devono essere compresi tra 0 e 6.
 * * - `oraInizio` deve essere compreso tra 0 e 23.
 * * - `oraFine` deve essere compreso tra 1 e 24.
 * * - `fp` deve essere un puntatore valido a un file aperto in modalità scrittura.
 * -----------------------------
 * Side Effects:
 * Scrive le informazioni delle auto disponibili nell'intervallo specificato nel file.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
 */
void stampaTabellaDiHashPerDispFile(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine, FILE *fp);

#endif // HASHTABLEAUTO_H
