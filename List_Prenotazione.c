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

/*
    * La struttura nodo rappresenta un elemento della Lista,
* contenente un valore di tipo Prenotazione e un puntatore al nodo successivo.
* La struttura Lista è definita come un puntatore a nodo, che rappresenta la testa della Lista.
* La struttura nodo contiene:
* - `value`: un elemento di tipo Prenotazione che rappresenta il valore del nodo.
* - `prossimo`: un puntatore al nodo successivo nella Lista.
*
 */
struct nodo {
    Prenotazione value;
    struct nodo *prossimo;
};

/*
    * Funzione per creare una nuova Lista vuota.
    * Restituisce un puntatore a una Lista vuota (NULL).
* * La funzione non accetta parametri e restituisce un puntatore a una Lista vuota.
 */
Lista nuovaLista(void)
{
    return NULL; // Restituisce NULL, indicando una Lista vuota
}

/*
    * Funzione per verificare se una Lista è vuota.
* * Parametri:
* - `l`: un puntatore alla Lista da verificare.
* * Restituisce:
* - 1 se la Lista è vuota (NULL), altrimenti restituisce 0.
 */
int ListaVuota(Lista l)
{
    return l == NULL;
}

/*
    * Funzione per aggiungere un nuovo elemento di tipo Prenotazione alla testa della Lista.
* * Parametri:
* - `val`: il valore di tipo Prenotazione da aggiungere alla Lista.
* - `l`: un puntatore alla Lista a cui aggiungere il nuovo elemento.
* * Restituisce:
* - Un puntatore alla Lista aggiornata con il nuovo elemento aggiunto in testa.
* * La funzione alloca memoria per un nuovo nodo, assegna il valore `val` al campo `value` del nodo,
* collega il nuovo nodo al nodo successivo (che è la Lista `l`)
* e restituisce il puntatore alla Lista aggiornata.
 */
Lista consLista(Prenotazione val, Lista l)
{
    struct nodo *nuovo;
    nuovo = malloc(sizeof(struct nodo));

    if (nuovo != NULL) { // Verifica se l'allocazione della memoria è riuscita
        nuovo->value = val;
        nuovo->prossimo = l;

        l = nuovo; // Aggiorna il puntatore alla testa della Lista in modo che punti al nuovo nodo
    }

    return l;
}

/*
    * Funzione per ottenere la coda della Lista.
* * Parametri:
* - `l`: un puntatore alla Lista da cui ottenere la coda.
* * Restituisce:
* - Un puntatore alla coda della Lista, che è il nodo successivo al primo nodo.
 */
Lista codaLista(Lista l)
{
    Lista temp; // Dichiarazione di un puntatore temporaneo a Lista

    if (l != NULL)
        temp = l->prossimo; // Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
    else
        temp = NULL; // Se la Lista è vuota, la coda sarà anche vuota

    return temp;
}

/*
    * Funzione per ottenere il primo elemento della Lista.
* * Parametri:
* - `l`: un puntatore alla Lista da cui ottenere il primo elemento.
* * Restituisce:
* - Il primo elemento di tipo Prenotazione della Lista, o un valore speciale NULLITEM se la Lista è vuota.
 */
Prenotazione ottieniPrimo(Lista l)
{
    Prenotazione e; // Variabile temporanea per memorizzare il primo elemento della Lista

    if (l != NULL)
        e = l->value; // Se la Lista non è vuota, assegna il valore del primo elemento alla variabile temporanea
    else
        e = NULL;

    return e;
}

/*
    * Funzione per creare una copia profonda della Lista.
* * Parametri:
* - `l`: un puntatore alla Lista da copiare.
* * Restituisce:
* - Un puntatore a una nuova Lista che è una copia profonda della Lista `l`.
* * La funzione itera attraverso ogni elemento della Lista `l`,
*   crea una copia di ogni Prenotazione
*   e la aggiunge alla nuova Lista in ordine inverso.
 */
Lista copiaProfondaLista(Lista l)
{
    Lista nuova = nuovaLista();
    Lista temp = l;
    Lista inOrdine = nuovaLista();  // Lista temporanea per mantenere ordine originale

    // Itera attraverso la Lista originale e crea una copia
    while (temp != NULL) {
        Prenotazione p = copiaPrenotazione(temp->value);
        inOrdine = consLista(p, inOrdine);
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

/*
    * Funzione per distruggere una Lista e liberare la memoria allocata.
* * Parametri:
* - `l`: un puntatore alla Lista da distruggere.
* * La funzione itera attraverso ogni nodo della Lista,
*   libera la memoria allocata per il nodo e per la Prenotazione contenuta nel nodo.
 */
void distruggiLista(Lista l)
{
    while (l != NULL) {
        // Libera la memoria per il nodo corrente e per la Prenotazione
        Lista temp = l;
        l = l->prossimo;
        distruggiPrenotazione(temp->value);
        free(temp);
    }
}

/*
    * Funzione per visualizzare le prenotazioni di un utente specifico in base al codice fiscale (CF).
* * Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni.
* - `CF`: una stringa che rappresenta il codice fiscale dell'utente di cui si vogliono visualizzare le prenotazioni.
 */
void visPrenotazioniPerUtente(Lista l, const char *CF)
{
    int trovate = 0;
    // Creiamo una copia profonda della Lista per non modificare l'originale
    Lista copia = copiaProfondaLista(l);

    // Controlliamo se la Lista è vuota
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

/*
    * Funzione per stampare tutte le prenotazioni presenti nella Lista.
* * Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni da stampare.
* * La funzione itera attraverso ogni elemento della Lista,
*   ottiene il primo elemento e lo stampa utilizzando la funzione `stampaPrenotazione`.
 */
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

/*
    * Funzione per filtrare le prenotazioni in base al codice fiscale (CF) dell'utente.
* * Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni da filtrare.
* - `CF`: una stringa che rappresenta il codice fiscale dell'utente di cui si vogliono filtrare le prenotazioni.
* * Restituisce:
* - Una nuova Lista contenente solo le prenotazioni dell'utente con il codice fiscale specificato.
 */
Lista filtraPrenotazioniPerCF(Lista l, const char *CF) {
    Lista risultato = nuovaLista();  // Lista da restituire
    Lista temp = l;

    while (!ListaVuota(temp)) {
        Prenotazione p = ottieniPrimo(temp);
        if (strcmp(ottieniCFPrenotazione(p), CF) == 0) {
            Prenotazione copia = copiaPrenotazione(p);
            risultato = consLista(copia, risultato);
        }
        temp = codaLista(temp);
    }

    return risultato;  // contiene solo prenotazioni dell'utente con CF
}



