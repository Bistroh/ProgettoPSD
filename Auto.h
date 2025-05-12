#ifndef AUTO_H
#define AUTO_H

typedef struct s_auto *Auto;

Auto creaAuto(char *targa, char *marca, char *modello, int anno, float prezzoXOra);
char *getTarga(Auto a);
char *getMarca(Auto a);
char *getModello(Auto a);
int getAnno(Auto a);
float getPrezzo(Auto a);
void stampaAuto(Auto a);

#endif
