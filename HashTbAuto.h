#ifndef HASHTABLEAUTO_H
#define HASHTABLEAUTO_H

#include "Auto.h"
#include "uthash.h"

typedef struct AutoEntry AutoEntry;
typedef AutoEntry* AutoHashTable;

AutoHashTable creaHashTableAuto();
int inserisciAuto(AutoHashTable *ht, Auto a);
Auto cercaAuto(AutoHashTable ht, const char *targa);
Auto rimuoviAuto(AutoHashTable *ht, const char *targa);
void distruggiHashTableAuto(AutoHashTable *ht);
void stampaHashTableAuto(AutoHashTable ht);
void stampaHashTablePerDisp(AutoHashTable ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine);
void resetDisponibilitaTutteLeAuto(AutoHashTable ht);

#endif // HASHTABLEAUTO_H
