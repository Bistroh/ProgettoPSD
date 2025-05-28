#include "prenotazione.h"
#include "Auto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define BLU    "\x1b[34m"
#define GIALLO  "\x1b[33m"
#define CIANO    "\x1b[36m"

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
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
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


int ottieniIDPrenotazione(Prenotazione prenotazione) {
    return prenotazione->ID_prenotazione;
}

char *ottieniCFPrenotazione(Prenotazione prenotazione) {
    return prenotazione->CF;
}

char *ottieniTargaPrenotazione(Prenotazione prenotazione) {
    return prenotazione->targa;
}

void ottieniPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine) {
    if (p) {
        *giornoInizio = p->periodo.giornoInizio;
        *giornoFine = p->periodo.giornoFine;
        *oraInizio = p->periodo.oraInizio;
        *oraFine = p->periodo.oraFine;
    }
}

const char* giornoToString(int giorno) {
    switch (giorno) {
        case 0: return "Lunedi'";
        case 1: return "Martedi'";
        case 2: return "Mercoledi'";
        case 3: return "Giovedi'";
        case 4: return "Venerdi'";
        case 5: return "Sabato";
        case 6: return "Domenica";
        default: return "Giorno sconosciuto";
    }
}

void stampaPrenotazione(Prenotazione prenotazione) {
    printf(CIANO "ID Prenotazione: " RESET "%d\n", prenotazione->ID_prenotazione);
    printf(CIANO "CF: " RESET "%s\n", prenotazione->CF);
    printf(CIANO "Targa: " RESET "%s\n", prenotazione->targa);
    if ((prenotazione->periodo.giornoInizio == 5 || prenotazione->periodo.giornoInizio == 6 || prenotazione->periodo.giornoFine == 5   || prenotazione->periodo.giornoFine == 6)) {
        printf(CIANO "Periodo: da %s ore %d:00 a %s ore %d:00\n" RESET,
               giornoToString(prenotazione->periodo.giornoInizio),
               prenotazione->periodo.oraInizio,
               giornoToString(prenotazione->periodo.giornoFine),
               prenotazione->periodo.oraFine);
    }
    else {
        printf(CIANO "Periodo: dal %s ore %d:00 al %s ore %d:00\n" RESET,
               giornoToString(prenotazione->periodo.giornoInizio),
               prenotazione->periodo.oraInizio,
               giornoToString(prenotazione->periodo.giornoFine),
               prenotazione->periodo.oraFine);
    }
}

void stampaPrenotazioneSuFile(Prenotazione prenotazione, FILE *fp) {
    fprintf(fp, "ID Prenotazione: %d\n", prenotazione->ID_prenotazione);
    fprintf(fp, "CF: %s\n", prenotazione->CF);
    fprintf(fp, "Targa: %s\n", prenotazione->targa);

    if ((prenotazione->periodo.giornoInizio == 5 || prenotazione->periodo.giornoInizio == 6 ||
            prenotazione->periodo.giornoFine == 5   || prenotazione->periodo.giornoFine == 6)) {
        fprintf(fp, "Periodo: da %s ore %d:00 a %s ore %d:00\n",
                giornoToString(prenotazione->periodo.giornoInizio),
                prenotazione->periodo.oraInizio,
                giornoToString(prenotazione->periodo.giornoFine),
                prenotazione->periodo.oraFine);
        } else {
            fprintf(fp, "Periodo: dal %s ore %d:00 al %s ore %d:00\n",
                    giornoToString(prenotazione->periodo.giornoInizio),
                    prenotazione->periodo.oraInizio,
                    giornoToString(prenotazione->periodo.giornoFine),
                    prenotazione->periodo.oraFine);
        }
}


Prenotazione copiaPrenotazione(Prenotazione originale)
{
    if (originale == NULL) return NULL;

    Prenotazione copia = malloc(sizeof(struct s_prenotazione));
    if (copia == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria nella copia.\n" RESET);
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