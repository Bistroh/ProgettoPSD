#ifndef AUTO_H
#define AUTO_H

#include <stdbool.h>

typedef struct s_auto *Auto;
/*
* Funzione: creaAuto
* -----------------------------
* Crea una nuova auto con i dati specificati.
* -----------------------------
* Parametri:
* - `targa`: la targa dell'auto.
* - `marca`: la marca dell'auto.
* - `modello`: il modello dell'auto.
* - `posizione`: la posizione dell'auto.
* - `anno`: l'anno di produzione dell'auto.
* - `prezzoXOra`: il prezzo per ora di noleggio dell'auto.
* -------------------------------
* Precondizioni:
* - `targa`, `marca`, `modello`, `posizione` devono essere stringhe non vuote.
* - 'targa' deve essere una stringa di 2 lettere seguite da 3 numeri seguiti da 2 lettere.
* - 'marca' e `modello`devono rientrare in un certo dominio di valori definito.
* - `posizione` deve rispettare un formato specifico (ad esempio, "prefisso", "nome della via" e "numero civico").
* - `anno` deve essere un intero positivo compreso tra 1900 e 2025.
* - `prezzoXOra` deve essere un numero positivo compreso tra 10 e 45.
* ---------------------------------
* Postcondizioni:
*    'a' è un puntatore a una struttura (Auto) inizializzata con i valori forniti in input.
* ---------------------------------
* Side Effects:
* la variabile struttura a viene allocata dinamicamente in memoria.
*
 */
Auto creaAuto(char *targa, char *marca, char *modello, char* posizione, int anno, float prezzoXOra);

/*
* Funzione: ottieniTarga
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere la targa.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta la targa dell'auto.
* -----------------------------
 */
char *ottieniTarga(Auto a);

/*
* Funzione: ottieniMarca
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere la marca.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta la marca dell'auto.
* -----------------------------
 */
char *ottieniMarca(Auto a);

/*
* Funzione: ottieniModello
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere la modello.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta la modello dell'auto.
* -----------------------------
 */
char *ottieniModello(Auto a);

/*
* Funzione: ottieniPozione
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere la posizione.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla stringa che rappresenta la posizione dell'auto.
* -----------------------------
 */
char *ottieniPosizione(Auto a);

/*
* Funzione: ottieniAnno
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere l'anno.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla variabile int che rappresenta l'anno dell'auto.
* -----------------------------
 */
int ottieniAnno(Auto a);

/*
* Funzione: ottieniPrezzo
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da cui ottenere il prezzo.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla variabile int che rappresenta il prezzo dell'auto.
* -----------------------------
 */
float ottieniPrezzo(Auto a);

/*
* Funzione: stampaAuto
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da stampare.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Postcondizioni:
* - Stampa i campi dell'auto, inclusa la targa, marca, modello, posizione, anno e prezzo per ora.
* -----------------------------
* Side Effects:
* Stampa le informazioni dell'auto sulla console.
* -----------------------------
* Restituisce:
* - Non restituisce nulla.
* -----------------------------
 */
void stampaAuto(Auto a);

/*
* Funzione: verificaDisponibileAuto
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da verificare.
* - `giornoInizio`: il giorno di inizio dell'intervallo.
* - `giornoFine`: il giorno di fine dell'intervallo.
* - `oraInizio`: l'ora di inizio dell'intervallo.
* - `oraFine`: l'ora di fine dell'intervallo.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine` devono essere valori validi:
*  - `giornoInizio` e `giornoFine` devono essere compresi tra 0 e 6 (dove 0 = Lunedì, 6 = Domenica).
* - `oraInizio` deve essere compreso tra 0 e 23.
* - `oraFine` deve essere compreso tra 1 e 24.
* -----------------------------
* Postcondizioni:
* - Restituisce 1 se l'auto è disponibile nell'intervallo specificato, 0 altrimenti.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/*
* Funzione: impostaDisponibile
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da verificare.
* - `giornoInizio`: il giorno di inizio dell'intervallo.
* - `giornoFine`: il giorno di fine dell'intervallo.
* - `oraInizio`: l'ora di inizio dell'intervallo.
* - `oraFine`: l'ora di fine dell'intervallo.
* - `stato`: booleano che indica se l'auto è disponibile (True) o no (False).
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* - `giornoInizio`, `giornoFine`, `oraInizio`, `oraFine` devono essere valori validi:
*  - `giornoInizio` e `giornoFine` devono essere compresi tra 0 e 6 (dove 0 = Lunedì, 6 = Domenica).
* - `oraInizio` deve essere compreso tra 0 e 23.
* - `oraFine` deve essere compreso tra 1 e 24.
* -----------------------------
* Postcondizioni:
* - Imposta lo stato di disponibilità dell'auto nell'intervallo specificato.
* -----------------------------
* Side Effects:
* Modifica lo stato di disponibilità dell'auto nella matrice di disponibilità.
* -----------------------------
 */
void impostaDisponibile(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine, bool stato);

/*
* Funzione: distruggiAuto
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da distruggere.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Side Effects:
* Libera la memoria allocata per l'auto, prevenendo memory leak.
* -----------------------------
 */
void distruggiAuto(Auto a);

/*
* Funzione: reimpostaDisponibileAuto
* -----------------------------
* Parametri:
* - `a`: puntatore all'auto da reimpostare.
* -----------------------------
* Precondizioni:
* - `a` deve essere un puntatore valido a una struttura `Auto` creata con `creaAuto`.
* -----------------------------
* Side Effects:
* Reimposta la disponibilità dell'auto,
* impostando tutti i giorni e le ore come non disponibili (false).
* -----------------------------
 */
void reimpostaDisponibileAuto(Auto a);


#endif
