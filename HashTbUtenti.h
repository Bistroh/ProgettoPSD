#ifndef HASHTBUTENTI_H
#define HASHTBUTENTI_H

#include "Utente.h"
#include "Coda_StoricoUtente.h"
#include "List_Prenotazione.h"

// Struttura opaca per la tabella hash
typedef struct HashEntry HashEntry;
typedef HashEntry* HashTable;

/**
 * Crea una nuova hash table (inizialmente vuota).
 * Per UTHash, è sufficiente inizializzare a NULL.
 */
HashTable newHashtableUtenti();

/**
 * Inserisce un utente nella tabella.
 * Restituisce 1 se l'inserimento è avvenuto con successo, 0 se il CF era già presente.
 */
int insertUtente(HashTable *h, Utente u);

Utente loginRegisterUtente(HashTable *h);
/**
 * Cerca un utente tramite codice fiscale (CF).
 * Restituisce il puntatore all'utente, o NULL se non trovato.
 */
Utente cercaUtente(HashTable h, const char *CF);

/**
 * Elimina un utente dalla tabella e lo restituisce senza deallocarlo.
 * Il chiamante è responsabile di liberarlo con distruggiUtente().
 */
Utente eliminaUtente(HashTable *h, const char *CF);

/**
 * Distrugge completamente la tabella hash e tutti gli utenti contenuti.
 * Dopo la chiamata, il puntatore viene impostato a NULL.
 */
void distruggiHashTableUtenti(HashTable *h);

void stampaHashTableUtenti(HashTable h);
void aggiungiPrenotazioniAStoricoUtenti(HashTable h, List listaPrenotazioni);
void stampaStoricoTuttiUtenti(HashTable h);

#endif // HASHTBUTENTI_H
