#include "prenotazione.h"
#include "Auto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"

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
        fprintf(stderr, RED "Errore di allocazione memoria\n" RESET);
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
    printf(CYAN "ID Prenotazione: " RESET "%d" "\n", prenotazione->ID_prenotazione);
    printf(CYAN "CF: " RESET "%s\n", prenotazione->CF);
    printf(CYAN "Targa: " RESET "%s\n", prenotazione->targa);
    printf(CYAN "Periodo: dal giorno %d ore %d al giorno %d ore %d\n" RESET,
           prenotazione->periodo.giornoInizio,
           prenotazione->periodo.oraInizio,
           prenotazione->periodo.giornoFine,
           prenotazione->periodo.oraFine);
}

Prenotazione copiaPrenotazione(Prenotazione originale)
{
    if (originale == NULL) return NULL;

    Prenotazione copia = malloc(sizeof(struct s_prenotazione));
    if (copia == NULL) {
        fprintf(stderr, RED "Errore di allocazione memoria nella copia.\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Copia dei dati
    copia->ID_prenotazione = originale->ID_prenotazione;
    strncpy(copia->CF, originale->CF, sizeof(copia->CF));
    copia->CF[sizeof(copia->CF) - 1] = '\0';

    strncpy(copia->targa, originale->targa, sizeof(copia->targa));
    copia->targa[sizeof(copia->targa) - 1] = '\0';

    copia->periodo.giornoInizio = originale->periodo.giornoInizio;
    copia->periodo.giornoFine = originale->periodo.giornoFine;
    copia->periodo.oraInizio = originale->periodo.oraInizio;
    copia->periodo.oraFine = originale->periodo.oraFine;

    return copia;
}

void distruggiPrenotazione(Prenotazione p)
{
    if (p != NULL) {
        free(p);
    }
}