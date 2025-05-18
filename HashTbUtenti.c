#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Utente.h"
#include "uthash.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"

typedef struct {
    char *cf;       // Chiave (codice fiscale)
    Utente utente;  // Valore
    UT_hash_handle hh;
} HashEntry;

typedef HashEntry* HashTable;

HashTable newHashtableUtenti() {
    return NULL; // Uthash usa una variabile inizializzata a NULL
}

int insertUtente(HashTable *h, Utente u) {
    const char *cf = getCF(u);
    if (!cf || !u) return 0;

    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, cf, entry);
    if (entry) {
        return 0; // già presente
    }

    entry = malloc(sizeof(HashEntry));
    entry->cf = strdup(cf);  // duplica la chiave
    entry->utente = u;
    HASH_ADD_KEYPTR(hh, *h, entry->cf, strlen(entry->cf), entry);
    return 1;
}

Utente cercaUtente(HashTable h, const char *CF) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(h, CF, entry);
    return entry ? entry->utente : NULL;
}

Utente eliminaUtente(HashTable *h, const char *CF) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, CF, entry);
    if (entry) {
        Utente u = entry->utente;
        HASH_DEL(*h, entry);
        free(entry->cf);
        free(entry);
        return u; // Utente non distrutto qui, restituito al chiamante
    }
    return NULL;
}

void distruggiHashTableUtenti(HashTable *h) {
    HashEntry *current, *tmp;
    HASH_ITER(hh, *h, current, tmp) {
        HASH_DEL(*h, current);
        distruggiUtente(current->utente); // distrugge Utente
        free(current->cf);                // libera chiave
        free(current);                    // libera nodo
    }
    *h = NULL;
}
// Funzione per stampare la tabella utenti
void stampaHashTableUtenti(HashTable h) {
    HashEntry *current;
    for (current = h; current != NULL; current = current->hh.next) {
        printf(CYAN "CF: %s\n" RESET, current->cf);
        stampaUtente(current->utente); // Assicurati di avere una funzione per stampare Utente
    }
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


Utente loginRegisterUtente(HashTable *h) {
    int scelta;
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char password[20];
    char passwordInserita[20];

    printf(GREEN "Benvenuto!\n" RESET);
    printf(YELLOW "1. Login\n");
    printf("2. Registrazione\n");
    printf("Seleziona un'opzione (1 o 2): " RESET);
    scanf("%d", &scelta);

    while(getchar() != '\n');

    do {
        printf(YELLOW "Inserisci codice fiscale (16 caratteri): " RESET);
        fgets(CF, 17, stdin);
        CF[strcspn(CF, "\n")] = '\0';
        if (!validaCodiceFiscale(CF)) printf(RED "Codice fiscale non valido.\n" RESET);
    } while (!validaCodiceFiscale(CF));

    Utente u = cercaUtente(*h, CF);

    if (scelta == 1) {
        // LOGIN
        if (u != NULL) {
            printf(YELLOW "Inserisci la tua password: " RESET);
            fgets(passwordInserita, 15, stdin);
            passwordInserita[strcspn(passwordInserita, "\n")] = '\0';
            if (strcmp(getPassword(u), passwordInserita) == 0) {
                printf(GREEN "Login riuscito! Benvenuto, %s %s!\n" RESET, getNome(u), getCognome(u));
                return u;
            } else {
                printf(RED "Password errata. Riprova.\n" RESET);
                return NULL;
            }
        } else {
            printf(RED "Utente non trovato. Procedo con la registrazione.\n" RESET);

            // REGISTRAZIONE AUTOMATICA
            printf(YELLOW "Inserisci il tuo nome: " RESET);
            scanf("%19s", nome);

            printf(YELLOW "Inserisci il tuo cognome: " RESET);
            scanf("%19s", cognome);


        do {
            printf(YELLOW "Inserisci la tua email: " RESET);
            fgets(email, 30, stdin);
            email[strcspn(email, "\n")] = '\0';
            if (!validaEmail(email)) printf(RED "Email non valida.\n" RESET);
        } while (!validaEmail(email));


do {
        printf(YELLOW "Inserisci numero di telefono (10 cifre, inizia per 3): " RESET);
        fgets(telefono, 14, stdin);
        telefono[strcspn(telefono, "\n")] = '\0';
        if (!validaTelefono(telefono)) printf(RED "Numero non valido.\n" RESET);
    } while (!validaTelefono(telefono));



    do {
        printf(YELLOW "Inserisci password (almeno 8 caratteri, 1 maiuscola, 1 minuscola, 1 numero, 1 simbolo): " RESET);
        fgets(password, 19, stdin);
        password[strcspn(password, "\n")] = '\0';
        if (!validaPassword(password)) printf(RED "Password non valida.\n" RESET);
    } while (!validaPassword(password));


        Utente nuovoUtente = creaUtente(CF, nome, cognome, email, password, telefono);

            if (insertUtente(h, nuovoUtente)) {
                printf(GREEN "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                getNome(nuovoUtente), getCognome(nuovoUtente));
            return nuovoUtente;
            } else {
                printf(RED "Errore nella registrazione, riprova.\n" RESET);
                return NULL;
            }
    }
    } else if (scelta == 2) {
        // REGISTRAZIONE
        if (u != NULL) {
            printf(RED "Utente già registrato. Procedo con il login.\n" RESET);

            printf(YELLOW "Inserisci la tua password: " RESET);
            fgets(passwordInserita, 19, stdin);
            passwordInserita[strcspn(passwordInserita, "\n")] = '\0';
            if (strcmp(getPassword(u), passwordInserita) == 0) {
                printf(GREEN "Login riuscito! Benvenuto, %s %s!\n" RESET, getNome(u), getCognome(u));
                return u;
            } else {
                printf(RED "Password errata. Riprova.\n" RESET);
                return NULL;
            }
        } else {
            printf(YELLOW "Inserisci il tuo nome: " RESET);
            scanf("%19s", nome);

            printf(YELLOW "Inserisci il tuo cognome: " RESET);
            scanf("%19s", cognome);

            do {
            printf(YELLOW "Inserisci la tua email: " RESET);
            fgets(email, 30, stdin);
            email[strcspn(email, "\n")] = '\0';
            if (!validaEmail(email)) printf(RED "Email non valida.\n" RESET);
        } while (!validaEmail(email));

           do {
        printf(YELLOW "Inserisci numero di telefono (10 cifre, inizia per 3): " RESET);
        fgets(telefono, 14, stdin);
        telefono[strcspn(telefono, "\n")] = '\0';
        if (!validaTelefono(telefono)) printf(RED "Numero non valido.\n" RESET);
    } while (!validaTelefono(telefono));

            do {
        printf(YELLOW "Inserisci password (almeno 8 caratteri, 1 maiuscola, 1 minuscola, 1 numero, 1 simbolo): " RESET);
        fgets(password, 19, stdin);
        password[strcspn(password, "\n")] = '\0';
        if (!validaPassword(password)) printf(RED "Password non valida.\n" RESET);
    } while (!validaPassword(password));

            Utente nuovoUtente = creaUtente(CF, nome, cognome, email, password, telefono);

            if (insertUtente(h, nuovoUtente)) {
                printf(GREEN "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                       getNome(nuovoUtente), getCognome(nuovoUtente));
                return nuovoUtente;
            } else {
                printf(RED "Errore nella registrazione, riprova.\n" RESET);
                return NULL;
            }
        }
    } else {
        printf(RED "Scelta non valida.\n" RESET);
        return NULL;
    }
}
