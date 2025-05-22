#ifndef LIST_PRENOTAZIONE_H
#define LIST_PRENOTAZIONE_H
#include "prenotazione.h"
#include "List_Prenotazione.h"

typedef struct node *List;
List newList(void);
int emptyList(List l);
List consList(Prenotazione val, List l);
List tailList(List l);
Prenotazione getFirst(List l);
void distruggiLista(List l);
List copiaProfondaLista(List l);
void visPrenotazioniPerUtente(List l, const char *CF);
void stampaListaPrenotazioni(List l);
List filtraPrenotazioniPerCF(List l, const char *CF);


#endif //LIST_PRENOTAZIONE_H
