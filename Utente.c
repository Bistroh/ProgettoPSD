#include "Utente.h"
#include "Coda_StoricoUtente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define BLU    "\x1b[34m"
#define CIANO    "\x1b[36m"

struct s_utente {
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char password[20];
    Coda storico;
};

Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password, char *telefono) {
    Utente nuovoUtente = malloc(sizeof(struct s_utente));
    if (nuovoUtente == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Copia i dati nelle rispettive variabili
    strncpy(nuovoUtente->CF, CF, sizeof(nuovoUtente->CF) - 1);
    nuovoUtente->CF[sizeof(nuovoUtente->CF) - 1] = '\0'; // Assicurati che la stringa sia terminata

    strncpy(nuovoUtente->nome, nome, sizeof(nuovoUtente->nome) - 1);
    nuovoUtente->nome[sizeof(nuovoUtente->nome) - 1] = '\0';

    strncpy(nuovoUtente->cognome, cognome, sizeof(nuovoUtente->cognome) - 1);
    nuovoUtente->cognome[sizeof(nuovoUtente->cognome) - 1] = '\0';

    strncpy(nuovoUtente->email, email, sizeof(nuovoUtente->email) - 1);
    nuovoUtente->email[sizeof(nuovoUtente->email) - 1] = '\0';

    strncpy(nuovoUtente->password, password, sizeof(nuovoUtente->password) - 1);
    nuovoUtente->password[sizeof(nuovoUtente->password) - 1] = '\0';

    strncpy(nuovoUtente->telefono, telefono, sizeof(nuovoUtente->telefono) - 1);
    nuovoUtente->telefono[sizeof(nuovoUtente->telefono) - 1] = '\0';

    nuovoUtente->storico = nuovaCoda();

    return nuovoUtente;
}


char *ottieniCF(Utente utente) {
    return utente->CF;
}

char *ottieniNome(Utente utente) {
    return utente->nome;
}

char *ottieniCognome(Utente utente) {
    return utente->cognome;
}

char *ottieniEmail(Utente utente) {
    return utente->email;
}

char *ottieniTelefono(Utente utente) {
    return utente->telefono;
}

char *ottieniPassword(Utente utente) {
    return utente->password;
}

Coda ottieniStorico(Utente u) {
    return u->storico;
}

void distruggiUtente(Utente u) {
    free(u);
}

void stampaUtente(Utente u) {
    printf(CIANO "CF: " RESET "%s\n", u->CF);
    printf(CIANO "Nome: " RESET "%s\n", u->nome);
    printf(CIANO "Cognome: " RESET "%s\n", u->cognome);
    printf(CIANO "Email: " RESET "%s\n", u->email);
    printf(CIANO "Telefono: " RESET "%s\n", u->telefono);
}

