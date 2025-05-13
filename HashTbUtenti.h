#ifndef HASHTBUTENTI_H
#define HASHTBUTENTI_H

#include <glib.h>
#include "Utente.h"

// Alias per GHashTable
typedef GHashTable* HashTable;

// Crea una nuova hash table
HashTable newHashtableUtenti();

// Inserisce un utente nella tabella.
// Ritorna 1 se inserito, 0 se già presente.
int insertUtente(HashTable h, Utente u);

// Cerca un utente dato il codice fiscale (CF).
// Ritorna l'Utente o NULL se non trovato.
Utente cercaUtente(HashTable h, const char *CF);

// Elimina un utente dato il CF.
// Ritorna l'Utente rimosso (che va eventualmente distrutto a mano), o NULL se non trovato.
Utente eliminaUtente(HashTable h, const char *CF);

// Distrugge l'intera tabella hash e tutti gli utenti in essa contenuti.
void distruggiHashTable(HashTable h);

#endif // HASHTBUTENTI_H
