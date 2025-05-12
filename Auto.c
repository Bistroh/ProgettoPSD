#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#define MAX_GIORNI_LAVORATIVI 5
#define MAX_ORA_LAVORATIVI 13

struct s_auto {
    char targa[10];
    char marca[20];
    char modello[20];
    int anno;
    float prezzoXOra;
	bool disponibile[MAX_GIORNI_LAVORATIVI][MAX_ORA_LAVORATIVI]; // Matrice per la disponibilità
};

Auto creaAuto(char *targa, char *marca, char *modello, int anno, float prezzoXOra) {
    Auto a = malloc(sizeof(struct s_auto));
    if (a == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    strncpy(a->targa, targa, sizeof(a->targa) - 1);
    a->targa[sizeof(a->targa) - 1] = '\0'; // Assicurati che la stringa sia terminata
    strncpy(a->marca, marca, sizeof(a->marca) - 1);
    a->marca[sizeof(a->marca) - 1] = '\0';
    strncpy(a->modello, modello, sizeof(a->modello) - 1);
    a->modello[sizeof(a->modello) - 1] = '\0';
    a->anno = anno;
    a->prezzoXOra = prezzoXOra;
    return a;
}

char *getTarga(Auto a) {
    return a->targa;
}

char *getMarca(Auto a) {
    return a->marca;
}

char *getModello(Auto a) {
    return a->modello;
}

int getAnno(Auto a) {
    return a->anno;
}

float getPrezzo(Auto a) {
    return a->prezzoXOra;
}

void stampaAuto(Auto a) {
    printf("Targa: %s\n", a->targa);
    printf("Marca: %s\n", a->marca);
    printf("Modello: %s\n", a->modello);
    printf("Anno: %d\n", a->anno);
    printf("Prezzo per ora: %.2f\n", a->prezzoXOra);
}
