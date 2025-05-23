#ifndef AUTO_H
#define AUTO_H

#include <stdbool.h>

typedef struct s_auto *Auto;

Auto creaAuto(char *targa, char *marca, char *modello, char* posizione, int anno, float prezzoXOra);
char *getTarga(Auto a);
char *getMarca(Auto a);
char *getModello(Auto a);
char *getPosizione(Auto a);
int getAnno(Auto a);
float getPrezzo(Auto a);
void stampaAuto(Auto a);
int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine);
void setDisponibile(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine, bool stato);
void distruggiAuto(Auto a);
void resetDisponibilitaAuto(Auto a);


#endif
