#include "Controlli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
    * Controlli.c
* -----------------------------
* Contiene funzioni per la validazione di stringhe e formati specifici.
* -----------------------------
 */
#define RESET   "\x1b[0m"
#define ROSSO   "\x1b[31m"

// Funzioni per pulire e mettere in pausa la console
void pulisciConsole() {
#ifdef _WIN32
    system("cls");    // Comando per pulire la console su Windows
#else
    system("clear"); // Comando per pulire la console su Unix/Linux
#endif
}

// Funzione per mettere in pausa la console
void pausaConsole() {
#ifdef _WIN32
    system("pause");    // Comando per mettere in pausa la console su Windows
#else
    printf("Premi INVIO per continuare...");    // Messaggio per Unix/Linux
    getchar();
#endif
}

/*
    * Funzione per verificare se una stringa contiene solo caratteri alfanumerici e spazi.
* * Parametri:
* - `str`: la stringa da verificare.
* Se la stringa contiene solo caratteri alfanumerici e spazi, restituisce 1 (vero).
 */
int stringaValida(const char *str) {
    while (*str) {
        if (!isalpha(*str) && !isdigit(*str) && !isspace(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

/*
    * Funzione per confrontare due stringhe in modo case-insensitive.
* * Parametri:
* - `a`: la prima stringa da confrontare.
* - `b`: la seconda stringa da confrontare.
 */
int confrontaCaseInsensitive(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

/*
    * Funzione per validare una password.
    * La password deve avere almeno 8 caratteri, contenere almeno una lettera maiuscola,
    * una lettera minuscola, un numero e un carattere speciale.
    * Restituisce 1 se la password è valida, 0 altrimenti.
* * Parametri:
* - `pwd`: la password da validare.
 */
int validaPassword(const char *pwd) {
    int len = strlen(pwd);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    if (len < 8) return 0;

    for (int i = 0; i < len; i++) {
        if (isupper(pwd[i])) hasUpper = 1;
        else if (islower(pwd[i])) hasLower = 1;
        else if (isdigit(pwd[i])) hasDigit = 1;
        else hasSpecial = 1;    // Considera qualsiasi carattere non alfanumerico come speciale
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

/*
    * Funzione per validare una targa di auto.
    * La targa deve essere composta da 2 lettere, 3 cifre e 2 lettere.
    * Restituisce 1 se la targa è valida, 0 altrimenti.
* * Parametri:
* - `targa`: la targa da validare.
 */
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

/*
    * Funzione per validare un nome.
    * Il nome deve contenere solo lettere e spazi, e non può essere vuoto.
    * Restituisce 1 se il nome è valido, 0 altrimenti.
* * Parametri:
* - `nome`: il nome da validare.
 */
int validaNome(const char *nome) {
    if (strlen(nome) == 0) return 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; // Solo lettere e spazi
        }
    }
    return 1;
}

/*
    * Funzione per validare un cognome.
    * Il cognome deve contenere solo lettere e spazi, e non può essere vuoto.
    * Restituisce 1 se il cognome è valido, 0 altrimenti.
* * Parametri:
* - `cognome`: il cognome da validare.
 */
int validaCognome(const char *cognome) {
    if (strlen(cognome) == 0) return 0;

    for (int i = 0; cognome[i] != '\0'; i++) {
        if (!isalpha(cognome[i]) && cognome[i] != ' ') {
            return 0; // Solo lettere e spazi
        }
    }
    return 1;
}

/*
    * Funzione per validare un indirizzo email.
    * L'email deve contenere un '@', un '.' dopo l'@ e non può essere vuota.
    * Restituisce 1 se l'email è valida, 0 altrimenti.
* * Parametri:
* - `email`: l'email da validare.
 */
int validaEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    // Controlla che ci sia un '@' e un '.' e che siano nella posizione corretta
    return (at && dot && at < dot && dot - at > 1 && dot[1] != '\0');
}

/*
    * Funzione per validare un codice fiscale italiano.
    * Il codice fiscale deve essere lungo 16 caratteri, con lettere e numeri nei posti giusti.
    * Restituisce 1 se il codice fiscale è valido, 0 altrimenti.
* * Parametri:
* - `cf`: il codice fiscale da validare.
* * La struttura del codice fiscale è:
* - 6 lettere (cognome e nome)
* - 2 cifre (anno di nascita)
* - 1 lettera (mese di nascita)
* - 2 cifre (giorno di nascita e sesso)
* - 4 caratteri alfanumerici (codice catastale del comune e carattere di controllo)
 */
int validaCodiceFiscale(const char *cf) {
    if (strlen(cf) != 16)
        return 0;

    for (int i = 0; i < 16; i++) {
        char c = toupper(cf[i]);
        // Controlla i caratteri in base alla posizione
        if (i < 6 || (i == 8 || i == 11 || i == 15)) {
            if (!isalpha(c)) return 0;
        } else {
            if (!isdigit(c)) return 0;
        }
    }
    return 1;
}

/*
    * Funzione per validare un numero di telefono italiano.
    * Il numero deve essere lungo 10 caratteri, iniziare con '3' e contenere solo cifre.
    * Restituisce 1 se il numero è valido, 0 altrimenti.
* * Parametri:
* - `numero`: il numero di telefono da validare.
* * La struttura del numero di telefono è:
* - 10 cifre
* - Inizia con '3' (per i cellulari italiani)
 */
int validaTelefono(const char *numero) {
    int len = strlen(numero);
    if (len != 10) return 0;
    if (numero[0] != '3') return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit(numero[i])) return 0;
    }
    return 1;
}

/*
    * Funzione per confrontare un prefisso con l'inizio di una stringa.
    * Restituisce 1 se la stringa inizia con il prefisso, 0 altrimenti.
* * Parametri:
* - `input`: la stringa da confrontare.
* - `prefisso`: il prefisso da confrontare.
 */
int confrontaPrefisso(const char* input, const char* prefisso) {
    while (*prefisso) {
        // Controlla se il carattere corrente di input corrisponde al prefisso
        if (tolower(*input) != tolower(*prefisso)) {
            return 0;
        }
        input++;
        prefisso++;
    }
    if (*input != ' ') return 0;
    return 1;
}

/*
    * Funzione per verificare se una stringa inizia con un prefisso valido.
    * Restituisce 1 se la stringa inizia con un prefisso valido, 0 altrimenti.
    * Se `prefissoUsato` è fornito, viene impostato al prefisso usato.
* * Parametri:
* - `input`: la stringa da verificare.
* - `prefissoUsato`: puntatore a una stringa che verrà impostata al prefisso usato.
 */
int iniziaConPrefissoValido(const char* input, const char** prefissoUsato) {
    // Lista dei prefissi validi
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
/*
    * Funzione per verificare se un token è un numero civico.
    * Un numero civico è composto solo da cifre.
    * Restituisce 1 se il token è un numero civico, 0 altrimenti.
* * Parametri:
* - `token`: il token da verificare.
 */
int isNumeroCivico(const char* token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) return 0;
    }
    return 1;
}

/*
    * Funzione per validare una via stradale.
    * La via deve iniziare con un prefisso valido, seguito da un nome e un numero civico.
    * Restituisce 1 se la via è valida, 0 altrimenti.
* * Parametri:
* - `input`: la stringa da validare.
* * La struttura della via stradale è:
* - Prefisso (ad esempio, "Via", "Viale", "Corso", ecc.)
* - Nome della via (composto da lettere e spazi)
* - Numero civico (composto da cifre)
 */
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

    // Verifica validità caratteri
    char copia[200];
    strncpy(copia, restante, sizeof(copia));
    copia[sizeof(copia) - 1] = '\0';

    // Trova l'ultima parola (numero civico)
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

/*
    * Funzione per capitalizzare la prima lettera di ogni parola in una stringa.
    * Le parole sono separate da spazi.
* * Parametri:
* - `nome`: la stringa da capitalizzare.
* * La funzione modifica la stringa in loco, capitalizzando la prima lettera di ogni parola
* e rendendo gli altri caratteri minuscoli.
 */
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
