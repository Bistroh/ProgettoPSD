//
// Created by extra on 14/05/2025.
//

#include "HashTbAuto.h"
#include "Auto.h"
#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *targa;       // Chiave (targa)
    Auto a;  // Valore
    UT_hash_handle hh;
} HashEntry;

typedef HashEntry* HashTable;
HashTable newHashtableAuto() {
    return NULL; // Uthash usa una variabile inizializzata a NULL
}

int insertAuto(HashTable *h, Auto a) {
    const char *targa = getTarga(a);
    if (!targa || !a) return 0;

    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, targa, entry);
    if (entry) {
        return 0; // già presente
    }

    entry = malloc(sizeof(HashEntry));
    entry->targa = strdup(targa);  // duplica la chiave
    entry->auto = a;
    HASH_ADD_KEYPTR(hh, *h, entry->targa, strlen(entry->targa), entry);
    return 1;
}
Auto cercaAuto(HashTable h, const char *targa) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(h, targa, entry);
    return entry ? entry->auto : NULL;
}

Auto eliminaAuto(HashTable *h, const char *targa) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, targa, entry);
    if (entry) {
        Auto a = entry->auto;
        HASH_DEL(*h, entry);
        free(entry->targa);
        free(entry);
        return a; // Auto non distrutta qui, restituita al chiamante
    }
    return NULL;
}
void distruggiHashTableAuto(HashTable *h) {
    HashEntry *current, *tmp;
    HASH_ITER(hh, *h, current, tmp) {
        HASH_DEL(*h, current);
        distruggiAuto(current->auto); // distrugge Auto
        free(current->targa);         // libera chiave
        free(current);                // libera nodo
    }
    *h = NULL;
}
void stampaHashTableAuto(HashTable h) {
    HashEntry *current;
    for (current = h; current != NULL; current = current->hh.next) {
        printf("Targa: %s\n", current->targa);
        stampaAuto(current->auto); // Assicurati di avere una funzione per stampare Auto
    }
}