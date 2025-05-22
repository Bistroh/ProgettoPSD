//
// Created by extra on 19/05/2025.
//

#include "Controlli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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

