#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h" // Includi il file di intestazione per l'elemento (item)
#include "List_Prenotazione.h"// Includi il file di intestazione per la Lista (Lista)
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define GIALLO  "\x1b[33m"

// Definizione della struttura nodo
struct nodo {
    Prenotazione value;
    struct nodo *prossimo;
};

// Definizione della funzione nuovaLista per creare una nuova Lista vuota
Lista nuovaLista(void)
{
    return NULL; // Restituisce NULL, indicando una Lista vuota
}

// Funzione per verificare se la Lista è vuota
int ListaVuota(Lista l)
{
    return l == NULL; // Restituisce 1 se la Lista è vuota (NULL), altrimenti restituisce 0
}

// Funzione per aggiungere un nuovo elemento in testa alla Lista
Lista consLista(Prenotazione val, Lista l)
{
    struct nodo *nuovo; // Dichiarazione di un puntatore a un nuovo nodo
    nuovo = malloc(sizeof(struct nodo)); // Allocazione della memoria per il nuovo nodo

    if (nuovo != NULL) { // Verifica se l'allocazione della memoria è riuscita
        nuovo->value = val; // Assegna il valore val al campo value del nuovo nodo
        nuovo->prossimo = l; // Collega il nuovo nodo al nodo successivo, che è la Lista l

        l = nuovo; // Aggiorna il puntatore alla testa della Lista in modo che punti al nuovo nodo
    }

    return l; // Restituisce il puntatore alla Lista aggiornata
}

Lista codaLista(Lista l)
{
    Lista temp; // Dichiarazione di un puntatore temporaneo a Lista

    if (l != NULL) // Verifica se la Lista non è vuota
        temp = l->prossimo; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la Lista è vuota, la coda sarà anche vuota

    return temp; // Restituisce la coda della Lista (una nuova Lista)
}

Prenotazione ottieniPrimo(Lista l)
{
    Prenotazione e; // Dichiarazione di una variabile temporanea per memorizzare il primo elemento della Lista

    if (l != NULL) // Verifica se la Lista non è vuota
        e = l->value; // Se la Lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULL; // Se la Lista è vuota, assegna un valore speciale NULLITEM alla variabile temporanea

    return e; // Restituisce il primo elemento della Lista
}

Lista copiaProfondaLista(Lista l)
{
    Lista nuova = nuovaLista();  // inizializza nuova Lista vuota
    Lista temp = l;
    Lista inOrdine = nuovaLista();  // Lista temporanea per mantenere ordine originale

    while (temp != NULL) {
        Prenotazione p = copiaPrenotazione(temp->value); // <-- serve funzione copiaPrenotazione()
        inOrdine = consLista(p, inOrdine); // costruiamo al contrario
        temp = temp->prossimo;
    }

    // invertiamo per mantenere l'ordine originale
    while (!ListaVuota(inOrdine)) {
        Prenotazione p = ottieniPrimo(inOrdine);
        nuova = consLista(p, nuova);
        inOrdine = codaLista(inOrdine);
    }

    return nuova;
}

void distruggiLista(Lista l)
{
    while (l != NULL) {
        Lista temp = l;
        l = l->prossimo;
        distruggiPrenotazione(temp->value); // <-- serve funzione destroyPrenotazione()
        free(temp);
    }
}

// Funzione per visualizzare le prenotazioni per utente
void visPrenotazioniPerUtente(Lista l, const char *CF)
{
    int trovate = 0;
    Lista copia = copiaProfondaLista(l);  // crea una copia profonda della Lista

    while (!ListaVuota(copia)) {
        Prenotazione p = ottieniPrimo(copia);
        if (strcmp(ottieniCFPrenotazione(p), CF) == 0) {
            stampaPrenotazione(p);
            trovate++;
        }
        copia = codaLista(copia);  // NON modifica l'originale
    }

    if (trovate == 0) {
        printf(ROSSO "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, CF);
    }

    distruggiLista(copiaProfondaLista(l));  // distruggi la copia profonda
}

// Funzione per stampare tutte le prenotazioni
void stampaListaPrenotazioni(Lista l)
{
    if (ListaVuota(l)) {
        printf(ROSSO "Non e' presente nessuna prenotazione.\n" RESET);
        return;
    }

    printf(GIALLO "Elenco prenotazioni:\n" RESET);

    Lista copia = l;

    while (!ListaVuota(copia)) {
        Prenotazione p = ottieniPrimo(copia);
        stampaPrenotazione(p);
        copia = codaLista(copia);
    }
}

Lista filtraPrenotazioniPerCF(Lista l, const char *CF) {
    Lista risultato = nuovaLista();  // Lista da restituire
    Lista temp = l;

    while (!ListaVuota(temp)) {
        Prenotazione p = ottieniPrimo(temp);
        if (strcmp(ottieniCFPrenotazione(p), CF) == 0) {
            Prenotazione copia = copiaPrenotazione(p); // <-- serve funzione di copia profonda
            risultato = consLista(copia, risultato);
        }
        temp = codaLista(temp);
    }

    return risultato;  // contiene solo prenotazioni dell'utente con CF
}



