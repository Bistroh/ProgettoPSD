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

struct node {       // Definizione della struttura "node", che rappresenta un singolo nodo nella coda.
     Prenotazione value; // Campo "value" per memorizzare il valore del nodo, che è di tipo "Prenotazione".
     struct node *next; // Puntatore "next" al prossimo nodo nella coda.
};

struct c_queue {          // Definizione della struttura "c_queue", che rappresenta la coda.
     struct node *head,*tail; // Puntatori "head" e "tail" rispettivamente al primo e all'ultimo nodo della coda.
     int numel;           // Campo "numel" per tenere traccia del numero di elementi nella coda.
};

Queue newQueue(void)   // Definizione della funzione "newQueue", che crea e inizializza una nuova coda.
{
     struct c_queue *q; // Dichiarazione di un puntatore "q" a "struct c_queue".
     q = malloc (sizeof(struct c_queue)); // Allocazione dinamica della memoria per la coda.
     if (q == NULL) // Controllo se l'allocazione della memoria è fallita.
	return NULL; // Restituisce NULL se non c'è abbastanza memoria.

     q->numel = 0;   // Inizializzazione del campo "numel" a 0.
     q->head = NULL; // Inizializzazione del puntatore "head" a NULL.
     q->tail = NULL; // Inizializzazione del puntatore "tail" a NULL.
     return q;       // Restituisce il puntatore alla nuova coda.
}

int emptyQueue(Queue q) // Definizione della funzione "emptyQueue", che controlla se la coda è vuota.
{
     if (q==NULL) // Controlla se il puntatore alla coda è NULL, indicando che la coda non esiste.
            return -1; // Restituisce -1 in questo caso.
     return q->numel == 0; // Restituisce 1 (vero) se la coda è vuota (numel è 0), altrimenti 0 (falso).
}

int enqueue(Prenotazione val, Queue q) // Definizione della funzione "enqueue", che aggiunge un elemento alla coda.
{
    if (q==NULL) // Controlla se il puntatore alla coda è NULL.
            return -1; // Restituisce -1 se la coda non esiste.

    struct node *nuovo; // Dichiarazione di un nuovo nodo "nuovo".
    nuovo = malloc (sizeof(struct node)); // Allocazione dinamica della memoria per il nuovo nodo.
    if (nuovo == NULL) return 0; // Se l'allocazione fallisce, restituisce 0.

    nuovo->value = val; // Imposta il valore del nuovo nodo al valore passato alla funzione.
    nuovo->next= NULL; // Imposta il puntatore "next" del nuovo nodo a NULL.

    if(q->head==NULL) // Controlla se la coda è vuota (head è NULL).
         q->head = nuovo; // Imposta "head" e "tail" al nuovo nodo, poiché è l'unico nodo nella coda.
    else
         q->tail->next= nuovo; // Se la coda non è vuota, collega il nodo precedente al nuovo nodo.

    q->tail = nuovo; // Imposta "tail" al nuovo nodo, poiché è ora l'ultimo nodo nella coda.
    (q->numel)++;    // Incrementa il numero di elementi nella coda.
    return 1;        // Restituisce 1 per indicare il successo.
}

Prenotazione dequeue(Queue q)
{
      if (q==NULL) return NULL;  // Se il puntatore alla coda è NULL, cioè la coda non esiste, restituisce un valore speciale NULLPrenotazione che indica nessun elemento.

      if (q->numel == 0) return NULL;  // Se la coda è vuota (numel, il contatore degli elementi, è 0), restituisce NULLPrenotazione, indicando che non c'è niente da rimuovere.

      Prenotazione result = q->head->value;  // Salva l'elemento in testa alla coda (il valore del nodo puntato da head) nella variabile result, che verrà restituito alla fine della funzione.

      struct node *temp = q->head;  // Crea un puntatore temporaneo al nodo attualmente in testa (q->head), in modo da poter liberare questo nodo dopo averlo rimosso dalla coda.

      q->head = q->head->next;  // Avanza il puntatore head al prossimo nodo nella coda, effettivamente rimuovendo l'elemento attuale in testa dalla coda.

      free(temp);  // Libera la memoria allocata per il nodo che è stato appena rimosso dalla coda, prevenendo così memory leak.

      if(q->head==NULL)  // Controlla se, dopo la rimozione, la coda è vuota (cioè se head è NULL perché non ci sono più nodi).
             q->tail=NULL;  // Se la coda è ora vuota, anche tail viene impostato a NULL, perché non ci sono più elementi nella coda.

      (q->numel)--;  // Decrementa il contatore degli elementi nella coda, riflettendo la rimozione dell'elemento.

      return result;  // Restituisce l'elemento che era in testa alla coda all'inizio della funzione.
}

void stampaStorico(Queue q) {
     if (q == NULL || emptyQueue(q)) {
          printf(GIALLO "Lo storico e' vuoto.\n" RESET);
          return;
     }

     Queue temp = newQueue();  // Coda temporanea per non perdere i dati

     if (temp == NULL) {
          printf(ROSSO "Errore nella creazione della coda temporanea.\n" RESET);
          return;
     }

     int i = 1;
     while (!emptyQueue(q)) {
          Prenotazione p = dequeue(q);          // Prendi elemento dalla coda originale
          stampaPrenotazione(p);                // Stampa l’elemento
          enqueue(p, temp);                     // Rimetti l’elemento nella coda temporanea
          i++;
     }

     // Ripristina la coda originale (rimetti gli elementi da temp a q)
     while (!emptyQueue(temp)) {
          Prenotazione p = dequeue(temp);
          enqueue(p, q);
     }

     // Libera la coda temporanea
     free(temp);
}

Queue copiaQueue(Queue q) {
    if (!q) return NULL;

    Queue copia = newQueue();
    if (!copia) return NULL;

    struct node* current = q->head;
    while (current) {
        Prenotazione pCopia = copiaPrenotazione(
        current->value); // copia la prenotazione
        enqueue(pCopia, copia);
        current = current->next;
    }

    return copia;
}


