#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#define MAX_GIORNI_LAVORATIVI 7
#define MAX_ORA_LAVORATIVI 24

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
    a->targa[sizeof(a->targa) - 1] = '\0';
    strncpy(a->marca, marca, sizeof(a->marca) - 1);
    a->marca[sizeof(a->marca) - 1] = '\0';
    strncpy(a->modello, modello, sizeof(a->modello) - 1);
    a->modello[sizeof(a->modello) - 1] = '\0';
    // Inizializza la matrice di disponibilità a false
    for (int g = 0; g < MAX_GIORNI_LAVORATIVI; g++) {
        for (int o = 0; o < MAX_ORA_LAVORATIVI; o++) {
            a->disponibile[g][o] = false;
        }
    }
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

void distruggiAuto(Auto a) {
    if (a != NULL) {
        free(a);
    }
}

void setDisponibile(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine, bool stato) {
    if (!a) return;

    // Validazione dei limiti
    if (giornoInizio < 0 || giornoFine >= MAX_GIORNI_LAVORATIVI ||
        oraInizio < 0 || oraFine >= MAX_ORA_LAVORATIVI ||
        giornoInizio > giornoFine || oraInizio > oraFine) {
        fprintf(stderr, "Intervallo giorno/ora non valido\n");
        return;
        }

    for (int g = giornoInizio; g <= giornoFine; g++) {
        for (int o = oraInizio; o <= oraFine; o++) {
            a->disponibile[g][o] = stato;
        }
    }
}

int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    if (!a) return 0;

    if (giornoInizio < 0 || giornoFine >= MAX_GIORNI_LAVORATIVI ||
        oraInizio < 0 || oraFine >= MAX_ORA_LAVORATIVI ||
        giornoInizio > giornoFine || oraInizio > oraFine) {
        fprintf(stderr, "Intervallo giorno/ora non valido nella verifica disponibilità\n");
        return 0;
        }

    for (int g = giornoInizio; g <= giornoFine; g++) {
        for (int o = oraInizio; o <= oraFine; o++) {
            if (a->disponibile[g][o]) {
                return 0;
            }
        }
    }
    return 1; // tutta la fascia è disponibile
}

void stampaAuto(Auto a) {
    printf("Targa: %s\n", a->targa);
    printf("Marca: %s\n", a->marca);
    printf("Modello: %s\n", a->modello);
    printf("Anno: %d\n", a->anno);
    printf("Prezzo per ora: %.2f\n", a->prezzoXOra);
}
