//
// Created by extra on 14/05/2025.
//

#ifndef HASHTBAUTO_H
#define HASHTBAUTO_H

#include "Auto.h"

typedef struct HashEntry HashEntry;
typedef HashEntry* HashTable;

/**
 * Crea una nuova hash table (inizialmente vuota).
 * Per UTHash, è sufficiente inizializzare a NULL.
 */
HashTable newHashtableAuto();
/**
 * Inserisce un'auto nella tabella.
 * Restituisce 1 se l'inserimento è avvenuto con successo, 0 se la targa era già presente.
 */
int insertAuto(HashTable *h, Auto a);
/**
 * Cerca un'auto tramite targa.
 * Restituisce il puntatore all'auto, o NULL se non trovata.
 */
Auto cercaAuto(HashTable h, const char *targa);
/**
 * Elimina un'auto dalla tabella e la restituisce senza deallocarla.
 * Il chiamante è responsabile di liberarla con distruggiAuto().
 */
void distruggiHashTableAuto(HashTable *h);
void stampaHashTableAuto(HashTable h);
#endif //HASHTBAUTO_H
