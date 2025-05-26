
#ifndef CODA_STORICOUTENTE_H
#define CODA_STORICOUTENTE_H
#include "prenotazione.h"
// Definisce un nuovo tipo di dato 'Coda', che è un puntatore a una struttura 'c_Coda'.
// La struttura 'c_Coda' deve essere definita altrove nel codice. Questa struttura rappresenta la coda.
typedef struct c_coda *Coda;

// Prototipi delle funzioni per operare sulla coda:

// Crea una nuova coda e restituisce un puntatore ad essa.
// Non richiede parametri in ingresso.
Coda nuovaCoda(void);

// Verifica se la coda specificata è vuota.
// Prende come parametro un puntatore a una coda e restituisce un intero.
// Tipicamente, restituisce 0 se la coda non è vuota e un valore non-zero (solitamente 1) se la coda è vuota.
int codaVuota(Coda q);


// Aggiunge un nuovo elemento alla parte posteriore della coda.
// Prende come parametri l'elemento da aggiungere (di tipo 'item', che deve essere definito altrove nel codice) e un puntatore alla coda a cui aggiungere l'elemento.
// Restituisce un intero, che solitamente indica il successo o il fallimento dell'operazione (ad esempio 0 per successo, -1 per fallimento).
int inserisciCoda(Prenotazione val, Coda q);

Prenotazione prelevaCoda(Coda q);

void stampaStorico(Coda q);
Coda copiaCoda(Coda q);

#endif //CODA_STORICOUTENTE_H
