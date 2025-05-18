#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#include "Utile_DevMenu.h"
#include "HashTbAuto.h"
#include "HashTbUtenti.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE   "\x1b[34m"
#define CYAN   "\x1b[36m"
#define RESET  "\x1b[0m"

#define MAX_MODELLI 5
#define MAX_AUTO 5
#define NUM_MARCHE 5
#define MAX_LUNGHEZZA 20


typedef struct {
    const char *marca;
    const char *modelli[MAX_MODELLI];
    int numeroModelli;
} MarcaModelli;

MarcaModelli databaseMarche[NUM_MARCHE] = {
    {"Fiat", {"Panda", "500", "Tipo", "Punto", "Bravo"}, 5},
    {"BMW", {"Serie 1", "Serie 3", "Serie 5", "X1", "X3"}, 5},
    {"Toyota", {"Yaris", "Corolla", "C-HR", "RAV4", "Auris"}, 5},
    {"Ford", {"Fiesta", "Focus", "Kuga", "Puma", "Mondeo"}, 5},
    {"Alfa Romeo", {"Giulia", "Stelvio", "Tonale", "147", "156"}, 5}
};

void rimuoviNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
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

int trovaMarca(const char *marca) {
    for (int i = 0; i < NUM_MARCHE; i++) {
        if (confrontaCaseInsensitive(marca, databaseMarche[i].marca)) {
            return i;
        }
    }
    return -1;
}

int modelloPresente(const char *modello, const MarcaModelli *marca) {
    for (int i = 0; i < marca->numeroModelli; i++) {
        if (confrontaCaseInsensitive(modello, marca->modelli[i])) {
            return 1;
        }
    }
    return 0;
}

void inserisciMarcaModello(char *marca, char *modello) {
    int indiceMarca;

    while(getchar() != '\n');

    // Input marca
    do {
        do {
            printf(YELLOW "Le marche disponibili del nostro CarSharing sono:\n" RESET);
            for (int i = 0; i < NUM_MARCHE; i++) {
                printf(CYAN " - " RESET "%s\n", databaseMarche[i].marca);
            }
            printf(BLUE "\nInserisci la marca dell'auto: " RESET);
            fgets(marca, MAX_LUNGHEZZA, stdin);
            rimuoviNewline(marca);
            if (!stringaValida(marca)) {
                printf(RED "Marca non valida. Usa solo lettere, numeri e spazi.\n" RESET);
            }
        } while (!stringaValida(marca));

        indiceMarca = trovaMarca(marca);
        if (indiceMarca == -1) {
            printf(RED "Marca non riconosciuta. Riprova.\n" RESET);
        }
    } while (!stringaValida(marca) || indiceMarca == -1);

    // Input modello
    MarcaModelli *marcaSelezionata = &databaseMarche[indiceMarca];
    do {
        printf(YELLOW "\nModelli disponibili per %s:\n" RESET, marcaSelezionata->marca);
        for (int i = 0; i < marcaSelezionata->numeroModelli; i++) {
            printf(YELLOW " - " RESET "%s\n", marcaSelezionata->modelli[i]);
        }

        printf(BLUE "\nInserisci il modello dell'auto: " RESET);
        fgets(modello, MAX_LUNGHEZZA, stdin);
        rimuoviNewline(modello);

        if (!stringaValida(modello)) {
            printf(RED "Modello non valido. Usa solo lettere, numeri e spazi.\n" RESET);
        } else if (!modelloPresente(modello, marcaSelezionata)) {
            printf(RED "Modello non riconosciuto per la marca %s.\n" RESET, marcaSelezionata->marca);
        }
    } while (!stringaValida(modello) || !modelloPresente(modello, marcaSelezionata));
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

// Funzione per inserire una nuova auto nella hash table
void aggiungiAutoInterattivo(AutoHashTable *ht) {
    char targa[8], marca[20], modello[20];
    int anno;
    float prezzo;

    do {
        printf(BLUE "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf(RED "Errore: formato targa non valido. Riprova.\n" RESET);
        }
    } while (!validaTarga(targa));

    inserisciMarcaModello(marca, modello);

    do {
        printf(BLUE "Inserisci l'anno di immatricolazione (es. 2000 - 2025): " RESET);
        scanf("%d", &anno);
        if (anno < 1900 || anno > 2025) {
            printf(RED "Errore: anno non valido. Deve essere compreso tra 1900 e 2025.\n" RESET);
        }
    } while (anno < 1900 || anno > 2025);

    do {
        printf(BLUE "Inserisci il prezzo orario del noleggio (minimo 20.00): " RESET);
        scanf("%f", &prezzo);
        if (prezzo < 20.0) {
            printf(RED "Errore: il prezzo orario non può essere inferiore a 20.00.\n" RESET);
        }
    } while (prezzo < 20.0);

    Auto a = creaAuto(targa, marca, modello, anno, prezzo);
    if (!a) {
        printf(RED "Errore nella creazione dell'auto.\n" RESET);
        return;
    }

    if (inserisciAuto(ht, a)) {
        printf(GREEN "Auto inserita correttamente!\n" RESET);
    } else {
        printf(RED "Auto già presente nella tabella.\n" RESET);
    }
}

// Gestione del menu sviluppatore
void gestisciMenuDeveloper(int scelta, AutoHashTable *ht, List l) {
    switch (scelta) {
        case 1:
            aggiungiAutoInterattivo(ht);
            stampaHashTableAuto(*ht);
            break;

        case 2: {
            char targa[8];
            do {
                printf(BLUE "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
                scanf("%7s", targa);

                if (!validaTarga(targa)) {
                    printf(RED "Errore: formato targa non valido. Riprova.\n" RESET);
                }
            } while (!validaTarga(targa));

            Auto a = rimuoviAuto(ht, targa);
            if (a) {
                distruggiAuto(a);
                printf(GREEN "Auto eliminata con successo.\n" RESET);
            } else {
                printf(RED "Auto non trovata.\n" RESET);
            }
            break;
        }

        case 3:
            printf("\n");
            stampaListaPrenotazioni(l);
            break;

        case 4:
            printf("Visualizzazione storico prenotazioni...\n");
            // TODO: Aggiungere implementazione
            printf(YELLOW "Visualizzazione storico prenotazioni... (funzione da implementare)\n" RESET);
            break;

        case 5:
            printf("Uscita dal menu sviluppatore...\n");
            break;

        default:
            printf(RED "Opzione non valida. Riprova.\n" RESET);
            break;
    }
}


// Mostra il menu sviluppatore e restituisce la scelta
int mostraMenuDeveloper() {
    int scelta;
    printf("\n" CYAN "*----------------------------------------------------*\n");
    printf(        "|             Car Sharing - Sviluppatore             |\n");
    printf(        "*----------------------------------------------------*\n");

    printf(        "| " RESET YELLOW "1." RESET " Aggiungi nuova auto                             " CYAN "|\n");
    printf(        "| " RESET YELLOW "2." RESET " Rimuovi auto esistente                          " CYAN "|\n");
    printf(        "| " RESET YELLOW "3." RESET " Visualizza tutte le prenotazioni                " CYAN "|\n");
    printf(        "| " RESET YELLOW "4." RESET " Visualizza storico prenotazioni                 " CYAN "|\n");
    printf(        "| " RESET RED "5." RESET " Esci dal programma                              " CYAN "|\n");

    printf(        "*----------------------------------------------------*\n");
    printf(BLUE "Scelta: " RESET);

    scanf("%d", &scelta);
    return scelta;
}

int selezionaRuolo() {
    int scelta;
    do {
        printf("\n" CYAN "*--------------------------------------*\n");
        printf(        "|       Seleziona il tuo ruolo         |\n");
        printf(        "*--------------------------------------*\n");
        printf(        "| " RESET YELLOW "1." RESET " Utente                            " CYAN "|\n");
        printf(        "| " RESET YELLOW "2." RESET " Sviluppatore                      " CYAN "|\n");
        printf(        "| " RESET RED "0." RESET " Esci                              " CYAN "|\n");
        printf(        "*--------------------------------------*\n");
        printf(BLUE "Scelta: " RESET);

        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2 && scelta != 0);

    return scelta;
}
