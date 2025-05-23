#include "Controlli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RESET   "\x1b[0m"
#define ROSSO   "\x1b[31m"

void pulisciConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausaConsole() {
#ifdef _WIN32
    system("pause");
#else
    printf("Premi INVIO per continuare...");
    getchar();
#endif
}


int stringaValida(const char *str) {
    while (*str) {
        if (!isalpha(*str) && !isdigit(*str) && !isspace(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int confrontaCaseInsensitive(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}


int validaPassword(const char *pwd) {
    int len = strlen(pwd);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    if (len < 8) return 0;

    for (int i = 0; i < len; i++) {
        if (isupper(pwd[i])) hasUpper = 1;
        else if (islower(pwd[i])) hasLower = 1;
        else if (isdigit(pwd[i])) hasDigit = 1;
        else hasSpecial = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int validaTarga(const char *targa) {
    if (strlen(targa) != 7) {
        return 0;
    }

    for (int i = 0; i < 7; i++) {
        if ((i < 2 || i > 4) && !isupper(targa[i])) {
            return 0; // Le lettere devono essere maiuscole
        }
        if (i >= 2 && i <= 4 && !isdigit(targa[i])) {
            return 0; // Le cifre centrali devono essere numeri
        }
    }

    return 1;
}

int validaNome(const char *nome) {
    if (strlen(nome) == 0) return 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; // Solo lettere e spazi
        }
    }
    return 1;
}

int validaCognome(const char *cognome) {
    if (strlen(cognome) == 0) return 0;

    for (int i = 0; cognome[i] != '\0'; i++) {
        if (!isalpha(cognome[i]) && cognome[i] != ' ') {
            return 0; // Solo lettere e spazi
        }
    }
    return 1;
}

int validaEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    return (at && dot && at < dot && dot - at > 1 && dot[1] != '\0');
}

int validaCodiceFiscale(const char *cf) {
    if (strlen(cf) != 16)
        return 0;

    for (int i = 0; i < 16; i++) {
        char c = toupper(cf[i]);
        if (i < 6 || (i == 8 || i == 11 || i == 15)) {
            if (!isalpha(c)) return 0;
        } else {
            if (!isdigit(c)) return 0;
        }
    }
    return 1;
}

int validaTelefono(const char *numero) {
    int len = strlen(numero);
    if (len != 10) return 0;
    if (numero[0] != '3') return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit(numero[i])) return 0;
    }
    return 1;
}

int confrontaPrefisso(const char* input, const char* prefisso) {
    while (*prefisso) {
        if (tolower(*input) != tolower(*prefisso)) {
            return 0;
        }
        input++;
        prefisso++;
    }
    if (*input != ' ') return 0;
    return 1;
}

int iniziaConPrefissoValido(const char* input, const char** prefissoUsato) {
    const char* prefissi[] = {
        "Via", "Viale", "Corso", "Piazza", "Strada",
        "Largo", "Piazzale", "Vicolo", "Borgo", "Contrada"
    };
    for (int i = 0; i < sizeof(prefissi) / sizeof(prefissi[0]); i++) {
        if (confrontaPrefisso(input, prefissi[i])) {
            if (prefissoUsato) *prefissoUsato = prefissi[i];
            return 1;
        }
    }
    return 0;
}

int isNumeroCivico(const char* token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) return 0;
    }
    return 1;
}

int validaViaStradale(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return 0;
    }

    const char* prefissoUsato = NULL;
    if (!iniziaConPrefissoValido(input, &prefissoUsato)) {
        printf(ROSSO "Prefisso non valido\n" RESET);
        return 0;
    }

    // Estrai il resto della stringa dopo il prefisso
    const char* restante = input + strlen(prefissoUsato);
    while (*restante == ' ') restante++; // salta spazi

    if (strlen(restante) == 0) {
        printf(ROSSO "Manca il nome della via e il numero civico\n" RESET);
        return 0;
    }

    // Verifica validità caratteri e trova l'ultima parola
    char copia[200];
    strncpy(copia, restante, sizeof(copia));
    copia[sizeof(copia) - 1] = '\0';

    char* ultimoSpazio = strrchr(copia, ' ');
    if (!ultimoSpazio || strlen(ultimoSpazio + 1) == 0) {
        printf(ROSSO "Manca il numero civico\n" RESET);
        return 0;
    }

    // Controlla che l'ultima parola sia un numero (civico)
    if (!isNumeroCivico(ultimoSpazio + 1)) {
        printf(ROSSO "Numero civico non valido\n" RESET);
        return 0;
    }

    // Controllo sui caratteri (tutti validi?)
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (!(isalpha(c) || isdigit(c) || c == ' ' || c == '.' || c == ',' || c == '\'' || c == '-')) {
            printf(ROSSO "Carattere non valido: '%c'\n" RESET, c);
            return 0;
        }
    }

    return 1;
}

#include <ctype.h>
#include <string.h>

// Mette in maiuscolo la prima lettera di ogni parola nel nome
void capitalizza(char* nome) {
    int nuovaParola = 1;

    for (int i = 0; nome[i] != '\0'; i++) {
        if (isspace(nome[i])) {
            nuovaParola = 1; // Prossimo carattere sarà l'inizio di una nuova parola
        } else if (nuovaParola && isalpha(nome[i])) {
            nome[i] = toupper(nome[i]);
            nuovaParola = 0;
        } else {
            nome[i] = tolower(nome[i]); // Rende gli altri caratteri minuscoli (opzionale)
        }
    }
}
