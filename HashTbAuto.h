#ifndef HASHTABLEAUTO_H
#define HASHTABLEAUTO_H

#include "Auto.h"
#include "uthash.h"

typedef struct AutoRecord AutoRecord;
typedef AutoRecord* AutoHashTB;

AutoHashTB creaAutoHashTB();
int inserisciAuto(AutoHashTB *ht, Auto a);
Auto cercaAuto(AutoHashTB ht, const char *targa);
Auto rimuoviAuto(AutoHashTB *ht, const char *targa);
void distruggiAutoHashTB(AutoHashTB *ht);
void stampaAutoHashTB(AutoHashTB ht);
void stampaTabellaDiHashPerDisp(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine);
void reimpostaDisponibilitaTutteLeAuto(AutoHashTB ht);

#endif // HASHTABLEAUTO_H
