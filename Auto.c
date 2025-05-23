#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#define MAX_GIORNI_LAVORATIVI 7
#define MAX_ORA_LAVORATIVI 24
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define CIANO    "\x1b[36m"

struct s_auto {
    char targa[10];
    char marca[20];
    char modello[20];
    char posizione[35];
    int anno;
    float prezzoXOra;
	bool disponibile[MAX_GIORNI_LAVORATIVI][MAX_ORA_LAVORATIVI]; // Matrice per la disponibilità
};

//Crea un’auto che successivamente può essere aggiunta al catalogo
Auto creaAuto(char *targa, char *marca, char *modello, char*posizione, int anno, float prezzoXOra) {
    Auto a = malloc(sizeof(struct s_auto));
    if (a == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
        exit(EXIT_FAILURE);
    }
    strncpy(a->targa, targa, sizeof(a->targa) - 1);
    a->targa[sizeof(a->targa) - 1] = '\0';
    strncpy(a->marca, marca, sizeof(a->marca) - 1);
    a->marca[sizeof(a->marca) - 1] = '\0';
    strncpy(a->modello, modello, sizeof(a->modello) - 1);
    a->modello[sizeof(a->modello) - 1] = '\0';
    strncpy(a->posizione, posizione, sizeof(a->posizione) - 1);
    a->posizione[sizeof(a->posizione) - 1] = '\0';
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

char *getPosizione(Auto a) {
    return a->posizione;
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
    if (!a || !a->disponibile) return;

    // Verifica che l'intervallo sia valido e disponibile (per prenotazioni true = libero, false = occupato)
    if (!verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
        fprintf(stderr, ROSSO "Intervallo giorno/ora non valido o non disponibile\n" RESET);
        return;
    }

    for (int g = giornoInizio; g <= giornoFine; g++) {
        int oraStart = (g == giornoInizio) ? oraInizio : 0;
        int oraEnd   = (g == giornoFine)  ? oraFine    : MAX_ORA_LAVORATIVI - 1;

        for (int o = oraStart; o <= oraEnd; o++) {
            a->disponibile[g][o] = stato;
        }
    }
}


int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    if (!a) return 0;

    // Controllo di validità degli intervalli
    if (giornoInizio < 0 || giornoFine >= MAX_GIORNI_LAVORATIVI ||
        oraInizio < 0 || oraFine >= MAX_ORA_LAVORATIVI ||
        giornoInizio > giornoFine ||
        (giornoInizio == giornoFine && oraInizio > oraFine)) {
        fprintf(stderr, ROSSO "Intervallo giorno/ora non valido nella verifica disponibilita'\n" RESET);
        return 0;
        }

    for (int g = giornoInizio; g <= giornoFine; g++) {
        int oraStart, oraEnd;

        if (giornoInizio == giornoFine) {
            // Prenotazione nello stesso giorno
            oraStart = oraInizio;
            oraEnd = oraFine;
        } else {
            // Prenotazione su più giorni
            if (g == giornoInizio) {
                oraStart = oraInizio;
                oraEnd = MAX_ORA_LAVORATIVI - 1;
            } else if (g == giornoFine) {
                oraStart = 0;
                oraEnd = oraFine;
            } else {
                oraStart = 0;
                oraEnd = MAX_ORA_LAVORATIVI - 1;
            }
        }

        for (int o = oraStart; o <= oraEnd; o++) {
            if (a->disponibile[g][o]) {
                return 0; // occupato
            }
        }
    }
    return 1; // disponibile
}


void stampaAuto(Auto a) {
    printf(CIANO "Targa:           " RESET "%s\n", a->targa);
    printf(CIANO "Marca:           " RESET "%s\n", a->marca);
    printf(CIANO "Modello:         " RESET "%s\n", a->modello);
    printf(CIANO "Posizione:       " RESET "%s\n", a->posizione);
    printf(CIANO "Anno:            " RESET "%d\n", a->anno);
    printf(CIANO "Prezzo per ora:  " RESET "%.2f\n", a->prezzoXOra);
}

void resetDisponibilitaAuto(Auto a) {
    if (!a) return;

    for (int g = 0; g < MAX_GIORNI_LAVORATIVI; g++) {
        for (int o = 0; o < MAX_ORA_LAVORATIVI; o++) {
            a->disponibile[g][o] = false;
        }
    }
}

