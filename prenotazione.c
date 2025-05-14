#include "prenotazione.h"
#include "Auto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int giornoInizio;
    int giornoFine;
    int oraInizio;
    int oraFine;
} Periodo;

struct s_prenotazione {
    int ID_prenotazione;
    char CF[17];
    char targa[10];
    Periodo periodo;
};

Prenotazione creaPrenotazione(char *CF, char *targa, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    static int id_contatore = 0;
    Prenotazione nuovaPrenotazione = malloc(sizeof(struct s_prenotazione));
    if (nuovaPrenotazione == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }

    nuovaPrenotazione->ID_prenotazione = id_contatore++;
    strncpy(nuovaPrenotazione->CF, CF, sizeof(nuovaPrenotazione->CF) - 1);
    nuovaPrenotazione->CF[sizeof(nuovaPrenotazione->CF) - 1] = '\0';

    strncpy(nuovaPrenotazione->targa, targa, sizeof(nuovaPrenotazione->targa) - 1);
    nuovaPrenotazione->targa[sizeof(nuovaPrenotazione->targa) - 1] = '\0';

    nuovaPrenotazione->periodo.giornoInizio = giornoInizio;
    nuovaPrenotazione->periodo.giornoFine = giornoFine;
    nuovaPrenotazione->periodo.oraInizio = oraInizio;
    nuovaPrenotazione->periodo.oraFine = oraFine;

    return nuovaPrenotazione;
}

int getIDPrenotazione(Prenotazione prenotazione) {
    return prenotazione->ID_prenotazione;
}

char *getCFPrenotazione(Prenotazione prenotazione) {
    return prenotazione->CF;
}

char *getTargaPrenotazione(Prenotazione prenotazione) {
    return prenotazione->targa;
}

void getPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine) {
    if (p) {
        *giornoInizio = p->periodo.giornoInizio;
        *giornoFine = p->periodo.giornoFine;
        *oraInizio = p->periodo.oraInizio;
        *oraFine = p->periodo.oraFine;
    }
}

void stampaPrenotazione(Prenotazione prenotazione) {
    printf("ID Prenotazione: %d\n", prenotazione->ID_prenotazione);
    printf("CF: %s\n", prenotazione->CF);
    printf("Targa: %s\n", prenotazione->targa);
    printf("Periodo: dal giorno %d ore %d al giorno %d ore %d\n",
           prenotazione->periodo.giornoInizio,
           prenotazione->periodo.oraInizio,
           prenotazione->periodo.giornoFine,
           prenotazione->periodo.oraFine);
}
