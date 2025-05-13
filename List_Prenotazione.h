#include "prenotazione.h"

#ifndef LIST_PRENOTAZIONE_H
#define LIST_PRENOTAZIONE_H

typedef struct node *list;
list newList(void);
int emptyList(list l);
list consList(Prenotazione val, list l);
list tailList(list l);
Prenotazione getFirst(list l);
Prenotazione getPrenotazioneByID(list l, int id);


#endif //LIST_PRENOTAZIONE_H
