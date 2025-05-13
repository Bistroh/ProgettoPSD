//
// Created by extra on 30/04/2025.
//

#include "prenotazione.h"
#include "Auto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
    int oraInizio;
    int oraFine;
} data;

struct s_prenotazione {
    int ID_prenotazione;
    char CF[17];
    char targa[10];
    data dataPrenotazione;
};

Prenotazione creaPrenotazione(char *CF, char *targa, int giorno, int mese, int anno, int oraInizio, int oraFine) {
    static int id_contatore = 0;
    Prenotazione nuovaPrenotazione = malloc(sizeof(struct s_prenotazione));
    if (nuovaPrenotazione == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    nuovaPrenotazione->ID_prenotazione = id_contatore++; // Inizializza l'ID della prenotazione
    strncpy(nuovaPrenotazione->CF, CF, sizeof(nuovaPrenotazione->CF) - 1);
    nuovaPrenotazione->CF[sizeof(nuovaPrenotazione->CF) - 1] = '\0'; // Assicurati che la stringa sia terminata
    strncpy(nuovaPrenotazione->targa, targa, sizeof(nuovaPrenotazione->targa) - 1);
    nuovaPrenotazione->targa[sizeof(nuovaPrenotazione->targa) - 1] = '\0';
    nuovaPrenotazione->dataPrenotazione.giorno = giorno;
    nuovaPrenotazione->dataPrenotazione.mese = mese;
    nuovaPrenotazione->dataPrenotazione.anno = anno;
    nuovaPrenotazione->dataPrenotazione.oraInizio = oraInizio;
    nuovaPrenotazione->dataPrenotazione.oraFine = oraFine;
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

char *getDataPrenotazione(Prenotazione prenotazione) {
    static char dataStr[20];
    snprintf(dataStr, sizeof(dataStr), "%02d/%02d/%04d %02d-%02d", prenotazione->dataPrenotazione.giorno,
             prenotazione->dataPrenotazione.mese, prenotazione->dataPrenotazione.anno,
             prenotazione->dataPrenotazione.oraInizio, prenotazione->dataPrenotazione.oraFine);
    return dataStr;
}

void stampaPrenotazione(Prenotazione prenotazione) {
    printf("ID Prenotazione: %d\n", prenotazione->ID_prenotazione);
    printf("CF: %s\n", prenotazione->CF);
    printf("Targa: %s\n", prenotazione->targa);
    printf("Data Prenotazione: %s\n", getDataPrenotazione(prenotazione));
}
