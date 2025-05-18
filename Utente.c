#include "Utente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"

struct s_utente {
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char password[20];
};

Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password, char *telefono) {
    Utente nuovoUtente = malloc(sizeof(struct s_utente));
    if (nuovoUtente == NULL) {
        fprintf(stderr, RED "Errore di allocazione memoria\n" RESET);
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

    return nuovoUtente;
}


char *getCF(Utente utente) {
    return utente->CF;
}

char *getNome(Utente utente) {
    return utente->nome;
}

char *getCognome(Utente utente) {
    return utente->cognome;
}

char *getEmail(Utente utente) {
    return utente->email;
}

char *getTelefono(Utente utente) {
    return utente->telefono;
}

char *getPassword(Utente utente) {
    return utente->password;
}

void distruggiUtente(Utente u) {
    free(u);
}

void stampaUtente(Utente u) {
    printf(CYAN "CF: " RESET "%s\n", u->CF);
    printf(CYAN "Nome: " RESET "%s\n", u->nome);
    printf(CYAN "Cognome: " RESET "%s\n", u->cognome);
    printf(CYAN "Email: " RESET "%s\n", u->email);
    printf(CYAN "Telefono: " RESET "%s\n", u->telefono);
}

