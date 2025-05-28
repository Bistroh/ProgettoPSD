#ifndef LIST_PRENOTAZIONE_H
#define LIST_PRENOTAZIONE_H
#include "prenotazione.h"

typedef struct nodo *Lista;
Lista nuovaLista(void);
int ListaVuota(Lista l);
Lista consLista(Prenotazione val, Lista l);
Lista codaLista(Lista l);
Prenotazione ottieniPrimo(Lista l);
void distruggiLista(Lista l);
Lista copiaProfondaLista(Lista l);
void visPrenotazioniPerUtente(Lista l, const char *CF);
void stampaListaPrenotazioni(Lista l);
Lista filtraPrenotazioniPerCF(Lista l, const char *CF);


#endif //LIST_PRENOTAZIONE_H
