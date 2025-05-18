#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h" // Includi il file di intestazione per l'elemento (item)
#include "List_Prenotazione.h"// Includi il file di intestazione per la lista (list)
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"

// Definizione della struttura node
struct node {
    Prenotazione value;
    struct node *next;
};

// Definizione della funzione newList per creare una nuova lista vuota
List newList(void)
{
    return NULL; // Restituisce NULL, indicando una lista vuota
}

// Funzione per verificare se la lista è vuota
int emptyList(List l)
{
    return l == NULL; // Restituisce 1 se la lista è vuota (NULL), altrimenti restituisce 0
}

// Funzione per aggiungere un nuovo elemento in testa alla lista
List consList(Prenotazione val, List l)
{
    struct node *nuovo; // Dichiarazione di un puntatore a un nuovo nodo
    nuovo = malloc(sizeof(struct node)); // Allocazione della memoria per il nuovo nodo

    if (nuovo != NULL) { // Verifica se l'allocazione della memoria è riuscita
        nuovo->value = val; // Assegna il valore val al campo value del nuovo nodo
        nuovo->next = l; // Collega il nuovo nodo al nodo successivo, che è la lista l

        l = nuovo; // Aggiorna il puntatore alla testa della lista in modo che punti al nuovo nodo
    }

    return l; // Restituisce il puntatore alla lista aggiornata
}

List tailList(List l)
{
    List temp; // Dichiarazione di un puntatore temporaneo a lista

    if (l != NULL) // Verifica se la lista non è vuota
        temp = l->next; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la lista è vuota, la coda sarà anche vuota

    return temp; // Restituisce la coda della lista (una nuova lista)
}

Prenotazione getFirst(List l)
{
    Prenotazione e; // Dichiarazione di una variabile temporanea per memorizzare il primo elemento della lista

    if (l != NULL) // Verifica se la lista non è vuota
        e = l->value; // Se la lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULL; // Se la lista è vuota, assegna un valore speciale NULLITEM alla variabile temporanea

    return e; // Restituisce il primo elemento della lista
}

List copiaProfondaLista(List l)
{
    List nuova = newList();  // inizializza nuova lista vuota
    List temp = l;
    List inOrdine = newList();  // lista temporanea per mantenere ordine originale

    while (temp != NULL) {
        Prenotazione p = copiaPrenotazione(temp->value); // <-- serve funzione copiaPrenotazione()
        inOrdine = consList(p, inOrdine); // costruiamo al contrario
        temp = temp->next;
    }

    // invertiamo per mantenere l'ordine originale
    while (!emptyList(inOrdine)) {
        Prenotazione p = getFirst(inOrdine);
        nuova = consList(p, nuova);
        inOrdine = tailList(inOrdine);
    }

    return nuova;
}

void distruggiLista(List l)
{
    while (l != NULL) {
        List temp = l;
        l = l->next;
        distruggiPrenotazione(temp->value); // <-- serve funzione destroyPrenotazione()
        free(temp);
    }
}

// Funzione per visualizzare le prenotazioni per utente
void visPrenotazioniPerUtente(List l, const char *CF)
{
    int trovate = 0;
    List copia = copiaProfondaLista(l);  // crea una copia profonda della lista

    while (!emptyList(copia)) {
        Prenotazione p = getFirst(copia);
        if (strcmp(getCFPrenotazione(p), CF) == 0) {
            stampaPrenotazione(p);
            trovate++;
        }
        copia = tailList(copia);  // NON modifica l'originale
    }

    if (trovate == 0) {
        printf(RED "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, CF);
    }

    distruggiLista(copiaProfondaLista(l));  // distruggi la copia profonda
}

// Funzione per stampare tutte le prenotazioni
void stampaListaPrenotazioni(List l)
{
    if (emptyList(l)) {
        printf(RED "Non è presente nessuna prenotazione.\n" RESET);
        return;
    }

    printf(YELLOW "Elenco prenotazioni:\n" RESET);

    List copia = l;

    while (!emptyList(copia)) {
        Prenotazione p = getFirst(copia);
        stampaPrenotazione(p);
        copia = tailList(copia);
    }
}



