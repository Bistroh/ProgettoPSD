#ifndef LIST_PRENOTAZIONE_H
#define LIST_PRENOTAZIONE_H
#include "prenotazione.h"

/*
    * La struttura nodo rappresenta un elemento della Lista,
    * contenente un valore di tipo Prenotazione e un puntatore al nodo successivo.
    * La struttura Lista è definita come un puntatore a nodo, che rappresenta la testa della Lista.
    * La struttura nodo contiene:
    * - `value`: un elemento di tipo Prenotazione che rappresenta il valore del nodo.
    * - `prossimo`: un puntatore al nodo successivo nella Lista.
    *
 */
typedef struct nodo *Lista;

/*
* Funzione: nuovaLista
* -----------------------------
* Precondizioni:
* - Nessuna.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore a una Lista vuota (NULL).
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
Lista nuovaLista(void);

/*
* Funzione: ListaVuota
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista da verificare.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista.
* -----------------------------
* Postcondizioni:
* - Restituisce 1 se la Lista è vuota (NULL), altrimenti restituisce 0.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
int ListaVuota(Lista l);

/*
* Funzione: consLista
* -----------------------------
* Parametri:
* - `val`: il valore di tipo Prenotazione da aggiungere alla Lista.
* - `l`: un puntatore alla Lista a cui aggiungere il nuovo elemento.
* -----------------------------
* Precondizioni:
* - `val` deve essere un valore di tipo Prenotazione valido.
* -----------------------------
* Postcondizioni:
* - Aggiunge un nuovo elemento di tipo Prenotazione alla testa della Lista.
* -----------------------------
* Side Effects:
* Alloca memoria per un nuovo nodo, assegna il valore `val` al campo `value` del nodo,
* collega il nuovo nodo al nodo successivo (che è la Lista `l`)
* e restituisce il puntatore alla Lista aggiornata.
* -----------------------------
 */
Lista consLista(Prenotazione val, Lista l);

/*
* Funzione: codaLista
 * -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista da cui ottenere la coda.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore alla coda della Lista, che è il nodo successivo al primo nodo.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
Lista codaLista(Lista l);

/*
* Funzione: ottieniPrimo
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista da cui ottenere il primo elemento.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista.
* -----------------------------
* Postcondizioni:
* - Restituisce il primo elemento di tipo Prenotazione della Lista,
*  o un valore speciale NULLITEM se la Lista è vuota.
* -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
Prenotazione ottieniPrimo(Lista l);

/*
* Funzione: distruggiLista
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista da distruggere.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista.
* -----------------------------
* Postcondizioni:
* - Libera la memoria allocata per la Lista e per ogni Prenotazione contenuta nel nodo.
* -----------------------------
 */
void distruggiLista(Lista l);

/*
* Funzione: copiaProfondaLista
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista da copiare.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista.
* -----------------------------
* Postcondizioni:
* - Restituisce un puntatore a una nuova Lista che è una copia profonda della Lista `l`.
* -----------------------------
* Side Effects:
* Alloca memoria per una nuova Lista e per ogni Prenotazione contenuta nella Lista `l`,
* mantenendo l'ordine originale degli elementi.
* -----------------------------
 */
Lista copiaProfondaLista(Lista l);

/*
* Funzione: visPrenotazioniPerUtente
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni.
* - `CF`: una stringa che rappresenta il codice fiscale dell'utente di cui si vogliono visualizzare le prenotazioni.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista contenente Prenotazioni.
* - `CF` deve essere una stringa valida che rappresenta il codice fiscale dell'utente.
* -----------------------------
* Postcondizioni:
* - Stampa tutte le prenotazioni dell'utente con il codice fiscale specificato.
* -----------------------------
 */
void visPrenotazioniPerUtente(Lista l, const char *CF);

/*
* Funzione: stampaListaPrenotazioni
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni da stampare.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista contenente Prenotazioni.
* -----------------------------
* Postcondizioni:
* - Stampa tutte le prenotazioni presenti nella Lista.
* -----------------------------
 */
void stampaListaPrenotazioni(Lista l);

/*
* Funzione: filtraPrenotazioniPerCF
* -----------------------------
* Parametri:
* - `l`: un puntatore alla Lista contenente le prenotazioni da filtrare.
* - `CF`: una stringa che rappresenta il codice fiscale dell'utente di cui si vogliono filtrare le prenotazioni.
* -----------------------------
* Precondizioni:
* - `l` deve essere un puntatore valido a una Lista contenente Prenotazioni.
* - `CF` deve essere una stringa valida che rappresenta il codice fiscale dell'utente.
* -----------------------------
* Postcondizioni:
* - Restituisce una nuova Lista contenente solo le prenotazioni dell'utente con il codice fiscale specificato.
* -----------------------------
* Side Effects:
* Alloca memoria per una nuova Lista e per ogni Prenotazione filtrata,
* mantenendo l'ordine originale degli elementi.
* -----------------------------
 */
Lista filtraPrenotazioniPerCF(Lista l, const char *CF);


#endif //LIST_PRENOTAZIONE_H
