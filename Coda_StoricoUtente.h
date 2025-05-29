
#ifndef CODA_STORICOUTENTE_H
#define CODA_STORICOUTENTE_H
#include "prenotazione.h"
// Definisce un nuovo tipo di dato 'Coda', che è un puntatore a una struttura 'c_Coda'.
// La struttura 'c_Coda' deve essere definita altrove nel codice. Questa struttura rappresenta la coda.
typedef struct c_coda *Coda;

// Prototipi delle funzioni per operare sulla coda:

/*
* Funzione: nuovaCoda
* -----------------------------
* Parametri:
* - Nessuno.
* -----------------------------
* Precondizioni:
* - Nessuna.
* -----------------------------
* Postcondizioni:
* - Crea una nuova coda e la restituisce come puntatore di tipo 'Coda'.
 * * Se l'allocazione della memoria fallisce, restituisce NULL.
 * -----------------------------
* Side Effects:
* La memoria per la coda viene allocata dinamicamente.
* -----------------------------
* Restituisce:
* - Un puntatore a una nuova coda di tipo 'Coda' se l'allocazione ha successo,
 */
Coda nuovaCoda(void);

/*
* Funzione: codaVuota
* -----------------------------
* Parametri:
* - q: un puntatore alla coda di tipo 'Coda'.
* -----------------------------
* Precondizioni:
* - q deve essere un puntatore valido a una coda creata con 'nuovaCoda'.
* -----------------------------
* Postcondizioni:
* - Restituisce 1 se la coda è vuota, 0 altrimenti.
* * Side Effects:
* Nessuno.
* -----------------------------
 */
int codaVuota(Coda q);

/*
* Funzione: inserisciCoda
* -----------------------------
* Parametri:
* - val: un valore di tipo 'Prenotazione' da inserire nella coda.
* - q: un puntatore alla coda di tipo 'Coda'.
* -----------------------------
* Precondizioni:
* - q deve essere un puntatore valido a una coda creata con 'nuovaCoda'.
* -----------------------------
* Postcondizioni:
* - Inserisce il valore 'val' alla fine della coda 'q'.
* * Restituisce 1 se l'inserimento ha successo, 0 se l'allocazione della memoria fallisce,
* -1 se il puntatore alla coda è NULL (cioè la coda non esiste).
* * Side Effects:
* La memoria per il nuovo nodo viene allocata dinamicamente.
* -----------------------------
 */
int inserisciCoda(Prenotazione val, Coda q);

/*
* Funzione: prelevaCoda
* -----------------------------
* Parametri:
* - q: un puntatore alla coda di tipo 'Coda'.
* -----------------------------
* Precondizioni:
* - q deve essere un puntatore valido a una coda creata con 'nuovaCoda'.
* -----------------------------
* Postcondizioni:
* - Rimuove e restituisce il primo elemento della coda 'q'.
* * Restituisce il valore del primo elemento della coda se l'operazione ha successo,
* * altrimenti restituisce NULL se la coda è vuota o se il puntatore alla coda è NULL.
* * Side Effects:
* La memoria del nodo rimosso viene liberata.
* -----------------------------
 */
Prenotazione prelevaCoda(Coda q);

/*
* Funzione: stampaStorico
* -----------------------------
* Parametri:
* - q: un puntatore alla coda di tipo 'Coda'.
* -----------------------------
* Precondizioni:
* - q deve essere un puntatore valido a una coda creata con 'nuovaCoda'.
* -----------------------------
* Postcondizioni:
* - Stampa tutte le prenotazioni presenti nella coda 'q'.
* Utilizza una coda temporanea per non perdere i dati originali durante la stampa.
* Se la coda è vuota, stampa un messaggio che indica che lo storico è vuoto.
* Side Effects:
* La memoria per la coda temporanea viene allocata dinamicamente.
* -----------------------------
* Restituisce:
* - Nessuno.
* -----------------------------
 */
void stampaStorico(Coda q);

/*
* Funzione: copiaCoda
* -----------------------------
* Parametri:
* - q: un puntatore alla coda di tipo 'Coda'.
* -----------------------------
* Precondizioni:
* - q deve essere un puntatore valido a una coda creata con 'nuovaCoda'.
* -----------------------------
* Postcondizioni:
* - Crea una copia della coda 'q' e restituisce un nuovo puntatore di tipo 'Coda'.
* * Se la coda è NULL, restituisce NULL.
* -------------------------------
* * Side Effects:
* La memoria per la nuova coda viene allocata dinamicamente.
* -----------------------------
 */
Coda copiaCoda(Coda q);

#endif //CODA_STORICOUTENTE_H
