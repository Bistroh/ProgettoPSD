#include "Coda_StoricoUtente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utente.h"
#include "prenotazione.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define GIALLO  "\x1b[33m"

struct nodo {       // Definizione della struttura "nodo", che rappresenta un singolo nodo nella coda.
     Prenotazione value; // Campo "value" per memorizzare il valore del nodo, che è di tipo "Prenotazione".
     struct nodo *prossimo; // Puntatore "prossimo" al prossimo nodo nella coda.
};

struct c_coda {          // Definizione della struttura "c_Coda", che rappresenta la coda.
     struct nodo *testa,*coda; // Puntatori "testa" e "coda" rispettivamente al primo e all'ultimo nodo della coda.
     int numel;           // Campo "numel" per tenere traccia del numero di elementi nella coda.
};

Coda nuovaCoda(void)   // Definizione della funzione "nuovaCoda", che crea e inizializza una nuova coda.
{
     struct c_coda *q; // Dichiarazione di un puntatore "q" a "struct c_Coda".
     q = malloc (sizeof(struct c_coda)); // Allocazione dinamica della memoria per la coda.
     if (q == NULL) // Controllo se l'allocazione della memoria è fallita.
	return NULL; // Restituisce NULL se non c'è abbastanza memoria.

     q->numel = 0;   // Inizializzazione del campo "numel" a 0.
     q->testa = NULL; // Inizializzazione del puntatore "testa" a NULL.
     q->coda = NULL; // Inizializzazione del puntatore "coda" a NULL.
     return q;       // Restituisce il puntatore alla nuova coda.
}

int codaVuota(Coda q) // Definizione della funzione "codaVuota", che controlla se la coda è vuota.
{
     if (q==NULL) // Controlla se il puntatore alla coda è NULL, indicando che la coda non esiste.
            return -1; // Restituisce -1 in questo caso.
     return q->numel == 0; // Restituisce 1 (vero) se la coda è vuota (numel è 0), altrimenti 0 (falso).
}

int inserisciCoda(Prenotazione val, Coda q) // Definizione della funzione "inserisciCoda", che aggiunge un elemento alla coda.
{
    if (q==NULL) // Controlla se il puntatore alla coda è NULL.
            return -1; // Restituisce -1 se la coda non esiste.

    struct nodo *nuovo; // Dichiarazione di un nuovo nodo "nuovo".
    nuovo = malloc (sizeof(struct nodo)); // Allocazione dinamica della memoria per il nuovo nodo.
    if (nuovo == NULL) return 0; // Se l'allocazione fallisce, restituisce 0.

    nuovo->value = val; // Imposta il valore del nuovo nodo al valore passato alla funzione.
    nuovo->prossimo= NULL; // Imposta il puntatore "prossimo" del nuovo nodo a NULL.

    if(q->testa==NULL) // Controlla se la coda è vuota (testa è NULL).
         q->testa = nuovo; // Imposta "testa" e "coda" al nuovo nodo, poiché è l'unico nodo nella coda.
    else
         q->coda->prossimo= nuovo; // Se la coda non è vuota, collega il nodo precedente al nuovo nodo.

    q->coda = nuovo; // Imposta "coda" al nuovo nodo, poiché è ora l'ultimo nodo nella coda.
    (q->numel)++;    // Incrementa il numero di elementi nella coda.
    return 1;        // Restituisce 1 per indicare il successo.
}

Prenotazione prelevaCoda(Coda q)
{
      if (q==NULL) return NULL;  // Se il puntatore alla coda è NULL, cioè la coda non esiste, restituisce un valore speciale NULLPrenotazione che indica nessun elemento.

      if (q->numel == 0) return NULL;  // Se la coda è vuota (numel, il contatore degli elementi, è 0), restituisce NULLPrenotazione, indicando che non c'è niente da rimuovere.

      Prenotazione result = q->testa->value;  // Salva l'elemento in testa alla coda (il valore del nodo puntato da testa) nella variabile result, che verrà restituito alla fine della funzione.

      struct nodo *temp = q->testa;  // Crea un puntatore temporaneo al nodo attualmente in testa (q->testa), in modo da poter liberare questo nodo dopo averlo rimosso dalla coda.

      q->testa = q->testa->prossimo;  // Avanza il puntatore testa al prossimo nodo nella coda, effettivamente rimuovendo l'elemento attuale in testa dalla coda.

      free(temp);  // Libera la memoria allocata per il nodo che è stato appena rimosso dalla coda, prevenendo così memory leak.

      if(q->testa==NULL)  // Controlla se, dopo la rimozione, la coda è vuota (cioè se testa è NULL perché non ci sono più nodi).
             q->coda=NULL;  // Se la coda è ora vuota, anche coda viene impostato a NULL, perché non ci sono più elementi nella coda.

      (q->numel)--;  // Decrementa il contatore degli elementi nella coda, riflettendo la rimozione dell'elemento.

      return result;  // Restituisce l'elemento che era in testa alla coda all'inizio della funzione.
}

void stampaStorico(Coda q) {
     if (q == NULL || codaVuota(q)) {
          printf(GIALLO "Lo storico e' vuoto.\n" RESET);
          return;
     }

     Coda temp = nuovaCoda();  // Coda temporanea per non perdere i dati

     if (temp == NULL) {
          printf(ROSSO "Errore nella creazione della coda temporanea.\n" RESET);
          return;
     }

     int i = 1;
     while (!codaVuota(q)) {
          Prenotazione p = prelevaCoda(q);          // Prendi elemento dalla coda originale
          stampaPrenotazione(p);                // Stampa l’elemento
          inserisciCoda(p, temp);                     // Rimetti l’elemento nella coda temporanea
          i++;
     }

     // Ripristina la coda originale (rimetti gli elementi da temp a q)
     while (!codaVuota(temp)) {
          Prenotazione p = prelevaCoda(temp);
          inserisciCoda(p, q);
     }

     // Libera la coda temporanea
     free(temp);
}

Coda copiaCoda(Coda q) {
    if (!q) return NULL;

    Coda copia = nuovaCoda();
    if (!copia) return NULL;

    struct nodo* elAttuale = q->testa;
    while (elAttuale) {
        Prenotazione pCopia = copiaPrenotazione(
        elAttuale->value); // copia la prenotazione
        inserisciCoda(pCopia, copia);
        elAttuale = elAttuale->prossimo;
    }

    return copia;
}


