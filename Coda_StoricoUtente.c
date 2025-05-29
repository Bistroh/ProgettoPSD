#include "Coda_StoricoUtente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utente.h"
#include "prenotazione.h"
/*Aggiunta delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define GIALLO  "\x1b[33m"

/*
* La struttura "nodo" rappresenta un nodo della coda,
* contenente un valore di tipo Prenotazione.
* Il nodo ha un puntatore "prossimo" che punta al nodo successivo nella coda.
 */
struct nodo {
     Prenotazione value;
     struct nodo *prossimo;
};

/*
* La struttura "c_coda" rappresenta la coda stessa,
* contenente i puntatori "testa" e "coda" che puntano rispettivamente
* al primo e all'ultimo nodo della coda.
* Inoltre, contiene un campo "numel" che tiene traccia del numero di elementi nella coda.
 */
struct c_coda {
     struct nodo *testa,*coda;
     int numel;
};

/*
* La funzione "nuovaCoda" crea una nuova coda dinamicamente allocata
* e inizializza i suoi campi.
* Restituisce un puntatore alla nuova coda.
* Se l'allocazione della memoria fallisce, restituisce NULL.
 */
Coda nuovaCoda(void)
{
     struct c_coda *q; // Dichiarazione di un puntatore "q" a "struct c_Coda".
     q = malloc (sizeof(struct c_coda)); // Allocazione dinamica della memoria per la coda.
     if (q == NULL) // Controllo se l'allocazione della memoria è fallita.
	return NULL;

     // Inizializza i campi della coda.
     q->numel = 0;
     q->testa = NULL;
     q->coda = NULL;
     return q;
}

/*
* La funzione "codaVuota" verifica se la coda è vuota.
* Prende come parametro un puntatore alla coda "q".
* Restituisce 1 (vero) se la coda è vuota, altrimenti 0 (falso).
* Se il puntatore alla coda è NULL, restituisce -1 per indicare che la coda non esiste.
 */
int codaVuota(Coda q)
{
     if (q==NULL)
            return -1;
     return q->numel == 0;
}

/*
* La funzione "inserisciCoda" aggiunge un nuovo elemento alla coda.
* Prende come parametri il valore da inserire (di tipo Prenotazione) e un puntatore alla coda "q".
* Restituisce 1 se l'inserimento ha successo, 0 se l'allocazione della memoria fallisce,
* e -1 se il puntatore alla coda è NULL (cioè la coda non esiste).
 */
int inserisciCoda(Prenotazione val, Coda q)
{
    if (q==NULL)
            return -1;

    struct nodo *nuovo;
    nuovo = malloc (sizeof(struct nodo));
    if (nuovo == NULL) return 0; // Controlla se l'allocazione della memoria è riuscita.

    nuovo->value = val; // Imposta il valore del nuovo nodo al valore passato alla funzione.
    nuovo->prossimo= NULL;

    if(q->testa==NULL)
         q->testa = nuovo; // Imposta "testa" e "coda" al nuovo nodo, poiché è l'unico nodo nella coda.
    else
         q->coda->prossimo= nuovo; // Se la coda non è vuota, collega il nodo precedente al nuovo nodo.

    q->coda = nuovo; // Imposta "coda" al nuovo nodo, poiché è ora l'ultimo nodo nella coda.
    (q->numel)++;
    return 1;
}
/*
* La funzione "prelevaCoda" rimuove e restituisce l'elemento in testa alla coda.
* Prende come parametro un puntatore alla coda "q".
* Restituisce il valore del nodo in testa alla coda se la coda non è vuota,
* altrimenti restituisce NULL.
 */
Prenotazione prelevaCoda(Coda q)
{
      // Controlla se la coda è NULL o vuota.
      if (q==NULL) return NULL;
      if (q->numel == 0) return NULL;

      Prenotazione result = q->testa->value;  // Salva l'elemento in testa alla coda nella variabile result

      struct nodo *temp = q->testa;  // Crea un puntatore temporaneo al nodo attualmente in testa (q->testa)

      q->testa = q->testa->prossimo;  // Avanza il puntatore testa al prossimo nodo nella coda
      free(temp);

      // Se dopo l'operazione la coda diventa vuota,
      // imposta anche il puntatore coda a NULL.
      if(q->testa==NULL)
             q->coda=NULL;
      (q->numel)--;

      return result;  // Restituisce l'elemento che era in testa alla coda all'inizio della funzione.
}

/*
* La funzione stampaStorico stampa tutte le prenotazioni presenti nella coda "q".
* * Utilizza una coda temporanea per non perdere i dati originali durante la stampa.
* * Prende come parametro un puntatore alla coda "q".
* * Se la coda temporanea non può essere creata, stampa un messaggio di errore.
*
 */
void stampaStorico(Coda q) {
  	 //Se la coda è vuota, stampa un messaggio che indica che lo storico è vuoto.
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

     /*
	* La funzione itera attraverso gli elementi della coda, stampa ogni prenotazione
	* e li reinserisce nella coda originale per preservare i dati.
     */
     while (!codaVuota(q)) {
          Prenotazione p = prelevaCoda(q);          // Prendi elemento dalla coda originale
          stampaPrenotazione(p);
          inserisciCoda(p, temp);                   // Rimetti l’elemento nella coda temporanea
          i++;
     }

     // Ripristina la coda originale (rimette gli elementi da temp a q)
     while (!codaVuota(temp)) {
          Prenotazione p = prelevaCoda(temp);
          inserisciCoda(p, q);
     }

     free(temp);
}

/*
* La funzione copiaCoda crea una copia della coda "q".
* * Prende come parametro un puntatore alla coda "q".
* * * Se la coda è NULL, restituisce NULL.
* * * Crea una nuova coda e copia ogni prenotazione dalla coda originale alla nuova coda.
 */
Coda copiaCoda(Coda q) {
    // Controlla se la coda è NULL
    if (!q) return NULL;

    Coda copia = nuovaCoda();
    if (!copia) return NULL;

    // Itera attraverso gli elementi della coda originale
    struct nodo* elAttuale = q->testa;
    while (elAttuale) {
        Prenotazione pCopia = copiaPrenotazione(
        elAttuale->value); // copia la prenotazione
        inserisciCoda(pCopia, copia);
        elAttuale = elAttuale->prossimo;
    }

    return copia;
}


