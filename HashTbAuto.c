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


// Definizione della struttura di hash record
typedef struct AutoRecord {
    char *targa;         // Chiave: targa dell'auto
    Auto autoPtr;        // Valore: puntatore all'oggetto Auto
    UT_hash_handle hh;   // Handler per uthash
} AutoRecord;

typedef AutoRecord* AutoHashTB;  // Tipo alias

// Crea una nuova hash table (inizializzata a NULL)
AutoHashTB creaAutoHashTB() {
    return NULL;
}

// Inserisce una nuova auto nella tabella
int inserisciAuto(AutoHashTB *ht, Auto a) {
    if (!a || !ht) return 0;

    const char *targa = ottieniTarga(a);
    if (!targa) return 0;

    AutoRecord *record = NULL;
    HASH_FIND_STR(*ht, targa, record);
    if (record) return 0;  // Auto già presente

    record = malloc(sizeof(AutoRecord));
    if (!record) {
        fprintf(stderr, ROSSO "Errore allocazione memoria AutoRecord\n" RESET);
        exit(EXIT_FAILURE);
    }

    record->targa = strdup(targa);
    record->autoPtr = a;
    HASH_ADD_KEYPTR(hh, *ht, record->targa, strlen(record->targa), record);

    return 1;
}


// Cerca un'auto tramite targa
Auto cercaAuto(AutoHashTB ht, const char *targa) {
    if (!targa) return NULL;

    AutoRecord *record = NULL;
    HASH_FIND_STR(ht, targa, record);
    return record ? record->autoPtr : NULL;
}

// Elimina un'auto e restituisce il puntatore
Auto rimuoviAuto(AutoHashTB *ht, const char *targa) {
    if (!ht || !targa) return NULL;

    AutoRecord *record = NULL;
    HASH_FIND_STR(*ht, targa, record);
    if (!record) return NULL;

    Auto a = record->autoPtr;
    HASH_DEL(*ht, record);
    free(record->targa);
    free(record);
    return a;
}

// Distrugge tutta la tabella e le auto contenute
void distruggiAutoHashTB(AutoHashTB *ht) {
    if (!ht) return;

    AutoRecord *curr, *tmp;
    HASH_ITER(hh, *ht, curr, tmp) {
        HASH_DEL(*ht, curr);
        distruggiAuto(curr->autoPtr);  // libera anche Auto
        free(curr->targa);
        free(curr);
    }

    *ht = NULL;
}

// Stampa tutte le auto nella tabella
void stampaAutoHashTB(AutoHashTB ht) {
    AutoRecord *record;
	if (!ht) {
        printf(ROSSO "Non sono presenti auto da stampare.\n" RESET);
        return;
    }
    printf("\n" CIANO "Auto presenti nel CarSharing:\n" RESET);
    for (record = ht; record != NULL; record = record->hh.next) {
        printf(BIANCO "------------------------\n" RESET);
        stampaAuto(record->autoPtr);
        printf(BIANCO "------------------------\n" RESET);
    }
}


void stampaTabellaDiHashPerDisp(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int almenoUna = 0;

    printf("\n" CIANO "Auto disponibili nella fascia selezionata:\n" RESET);

    AutoRecord *record;
    for (record = ht; record != NULL; record = record->hh.next) {
        Auto a = record->autoPtr;
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

void reimpostaDisponibilitaTutteLeAuto(AutoHashTB ht) {
    AutoRecord *record;

    for (record = ht; record != NULL; record = record->hh.next) {
        reimpostaDisponibileAuto(record->autoPtr);
    }

    printf(CIANO "Tutte le disponibilita' sono state reinizializzate.\n" RESET);
}

