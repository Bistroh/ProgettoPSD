#include "Utente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        fprintf(stderr, "Errore di allocazione memoria\n");
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
    printf("CF: %s\n", u->CF);
    printf("Nome: %s\n", u->nome);
    printf("Cognome: %s\n", u->cognome);
    printf("Email: %s\n", u->email);
    printf("Telefono: %s\n", u->telefono);
}

