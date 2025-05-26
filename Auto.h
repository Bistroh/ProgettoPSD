#ifndef AUTO_H
#define AUTO_H

#include <stdbool.h>

typedef struct s_auto *Auto;

Auto creaAuto(char *targa, char *marca, char *modello, char* posizione, int anno, float prezzoXOra);
char *ottieniTarga(Auto a);
char *ottieniMarca(Auto a);
char *ottieniModello(Auto a);
char *ottieniPosizione(Auto a);
int ottieniAnno(Auto a);
float ottieniPrezzo(Auto a);
void stampaAuto(Auto a);
int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine);
void impostaDisponibile(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine, bool stato);
void distruggiAuto(Auto a);
void reimpostaDisponibileAuto(Auto a);


#endif
