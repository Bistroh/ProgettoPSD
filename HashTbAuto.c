#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auto.h"
#include "HashTbAuto.h"
#include "uthash.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define CIANO    "\x1b[36m"
#define BIANCO   "\x1b[37m"


// Definizione della struttura di hash entry
typedef struct AutoEntry {
    char *targa;         // Chiave: targa dell'auto
    Auto autoPtr;        // Valore: puntatore all'oggetto Auto
    UT_hash_handle hh;   // Handler per uthash
} AutoEntry;

typedef AutoEntry* AutoHashTable;  // Tipo alias

// Crea una nuova hash table (inizializzata a NULL)
AutoHashTable creaHashTableAuto() {
    return NULL;
}

// Inserisce una nuova auto nella tabella
int inserisciAuto(AutoHashTable *ht, Auto a) {
    if (!a || !ht) return 0;

    const char *targa = getTarga(a);
    if (!targa) return 0;

    AutoEntry *entry = NULL;
    HASH_FIND_STR(*ht, targa, entry);
    if (entry) return 0;  // Auto già presente

    entry = malloc(sizeof(AutoEntry));
    if (!entry) {
        fprintf(stderr, ROSSO "Errore allocazione memoria AutoEntry\n" RESET);
        exit(EXIT_FAILURE);
    }

    entry->targa = strdup(targa);
    entry->autoPtr = a;
    HASH_ADD_KEYPTR(hh, *ht, entry->targa, strlen(entry->targa), entry);

    return 1;
}


// Cerca un'auto tramite targa
Auto cercaAuto(AutoHashTable ht, const char *targa) {
    if (!targa) return NULL;

    AutoEntry *entry = NULL;
    HASH_FIND_STR(ht, targa, entry);
    return entry ? entry->autoPtr : NULL;
}

// Elimina un'auto e restituisce il puntatore
Auto rimuoviAuto(AutoHashTable *ht, const char *targa) {
    if (!ht || !targa) return NULL;

    AutoEntry *entry = NULL;
    HASH_FIND_STR(*ht, targa, entry);
    if (!entry) return NULL;

    Auto a = entry->autoPtr;
    HASH_DEL(*ht, entry);
    free(entry->targa);
    free(entry);
    return a;
}

// Distrugge tutta la tabella e le auto contenute
void distruggiHashTableAuto(AutoHashTable *ht) {
    if (!ht) return;

    AutoEntry *curr, *tmp;
    HASH_ITER(hh, *ht, curr, tmp) {
        HASH_DEL(*ht, curr);
        distruggiAuto(curr->autoPtr);  // libera anche Auto
        free(curr->targa);
        free(curr);
    }

    *ht = NULL;
}

// Stampa tutte le auto nella tabella
void stampaHashTableAuto(AutoHashTable ht) {
    AutoEntry *entry;
	if (!ht) {
        printf(ROSSO "Non sono presenti auto da stampare.\n" RESET);
        return;
    }
    printf("\n" CIANO "Auto presenti nel CarSharing:\n" RESET);
    for (entry = ht; entry != NULL; entry = entry->hh.next) {
        printf(BIANCO "------------------------\n" RESET);
        stampaAuto(entry->autoPtr);
        printf(BIANCO "------------------------\n" RESET);
    }
}


void stampaHashTablePerDisp(AutoHashTable ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int almenoUna = 0;

    printf("\n" CIANO "Auto disponibili nella fascia selezionata:\n" RESET);

    AutoEntry *entry;
    for (entry = ht; entry != NULL; entry = entry->hh.next) {
        Auto a = entry->autoPtr;
        if (verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
            printf(BIANCO "------------------------\n" RESET);
            stampaAuto(a);
            printf(BIANCO "------------------------\n" RESET);
            almenoUna = 1;
        }
    }

    if (!almenoUna) {
        printf(ROSSO "Nessuna auto disponibile per questa fascia.\n" RESET);
    }
}

void resetDisponibilitaTutteLeAuto(AutoHashTable ht) {
    AutoEntry *entry;

    for (entry = ht; entry != NULL; entry = entry->hh.next) {
        resetDisponibilitaAuto(entry->autoPtr);
    }

    printf(CIANO "Tutte le disponibilita' sono state reinizializzate.\n" RESET);
}

