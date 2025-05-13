#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h" // Includi il file di intestazione per l'elemento (item)
#include "List_Prenotazione.h"// Includi il file di intestazione per la lista (list)

// Definizione della struttura node
struct node {
    Prenotazione value;
    struct node *next;
};

// Definizione della funzione newList per creare una nuova lista vuota
list newList(void)
{
    return NULL; // Restituisce NULL, indicando una lista vuota
}

// Funzione per verificare se la lista è vuota
int emptyList(list l)
{
    return l == NULL; // Restituisce 1 se la lista è vuota (NULL), altrimenti restituisce 0
}

// Funzione per aggiungere un nuovo elemento in testa alla lista
list consList(Prenotazione val, list l)
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

list tailList(list l)
{
    list temp; // Dichiarazione di un puntatore temporaneo a lista

    if (l != NULL) // Verifica se la lista non è vuota
        temp = l->next; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la lista è vuota, la coda sarà anche vuota

    return temp; // Restituisce la coda della lista (una nuova lista)
}

Prenotazione getFirst(list l)
{
    Prenotazione e; // Dichiarazione di una variabile temporanea per memorizzare il primo elemento della lista

    if (l != NULL) // Verifica se la lista non è vuota
        e = l->value; // Se la lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULL; // Se la lista è vuota, assegna un valore speciale NULLITEM alla variabile temporanea

    return e; // Restituisce il primo elemento della lista
}

Prenotazione getPrenotazioneByCF(list l, char *CF)
{
    while (l != NULL) {    //verifica se la lista non è vuota
        if (strcmp(getCFPrenotazione(l->value), CF) == 0) {    //cerca  l'elemento con CF uguale a quello passato come parametro
            return l->value; //restituisce l'elemento trovato tramite CF
        }

        l = l->next; //passa al nodo successivo
    }

    return NULL; // oppure NULL
}

void stampaListaPrenotazioni(list l)
{
    if (l == NULL) {
        printf("La lista è vuota.\n");
        return;
    }

    printf("Elenco prenotazioni:\n");

    list corrente = l;  // copia del puntatore, NON modifica la lista originale

    while (corrente != NULL) {
        stampaPrenotazione(corrente->value);  // stampa l'elemento corrente
        corrente = corrente->next;            // passa al nodo successivo
    }
}
