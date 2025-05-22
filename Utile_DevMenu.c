#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#include "Utile_DevMenu.h"
#include "HashTbAuto.h"
#include "HashTbUtenti.h"
#include "Controlli.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define ROSSO    "\x1b[31m"
#define VERDE  "\x1b[32m"
#define GIALLO "\x1b[33m"
#define BLU   "\x1b[34m"
#define CIANO   "\x1b[36m"
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
    {"Toyota", {"Yaris", "Corolla", "CHR", "RAV4", "Auris"}, 5},
    {"Ford", {"Fiesta", "Focus", "Kuga", "Puma", "Mondeo"}, 5},
    {"Alfa Romeo", {"Giulia", "Stelvio", "Tonale", "147", "156"}, 5}
};




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
            printf(GIALLO "Le marche disponibili del nostro CarSharing sono:\n" RESET);
            for (int i = 0; i < NUM_MARCHE; i++) {
                printf(CIANO " - " RESET "%s\n", databaseMarche[i].marca);
            }
            printf(BLU "\nInserisci la marca dell'auto: " RESET);
            fgets(marca, MAX_LUNGHEZZA, stdin);
            marca[strcspn(marca, "\n")] = '\0';
            if (!stringaValida(marca)) {
                printf(ROSSO "Marca non valida. Usa solo lettere, numeri e spazi.\n" RESET);
            }
        } while (!stringaValida(marca));

        indiceMarca = trovaMarca(marca);
        if (indiceMarca == -1) {
            printf(ROSSO "Marca non riconosciuta. Riprova.\n" RESET);
        }
    } while (!stringaValida(marca) || indiceMarca == -1);

    // Input modello
    MarcaModelli *marcaSelezionata = &databaseMarche[indiceMarca];
    do {
        printf(GIALLO "\nModelli disponibili per %s:\n" RESET, marcaSelezionata->marca);
        for (int i = 0; i < marcaSelezionata->numeroModelli; i++) {
            printf(GIALLO " - " RESET "%s\n", marcaSelezionata->modelli[i]);
        }

        printf(BLU "\nInserisci il modello dell'auto: " RESET);
        fgets(modello, MAX_LUNGHEZZA, stdin);
        modello[strcspn(modello, "\n")] = '\0';

        if (!stringaValida(modello)) {
            printf(ROSSO "Modello non valido. Usa solo lettere, numeri e spazi.\n" RESET);
        } else if (!modelloPresente(modello, marcaSelezionata)) {
            printf(ROSSO "Modello non riconosciuto per la marca %s.\n" RESET, marcaSelezionata->marca);
        }
    } while (!stringaValida(modello) || !modelloPresente(modello, marcaSelezionata));
}


// Funzione per inserire una nuova auto nella hash table
void aggiungiAutoInterattivo(AutoHashTable *ht) {
    char targa[8], marca[20], modello[20],buffer[100];
    int anno;
    float prezzo;
    int valid;

    do {
        printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
        }
    } while (!validaTarga(targa));

    inserisciMarcaModello(marca, modello);

    do {
    printf(BLU "Inserisci l'anno di immatricolazione (es. 2000 - 2025): " RESET);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // Errore o EOF
        printf(ROSSO "Errore nella lettura.\n" RESET);
        continue;
    }

    // Provo a leggere un intero dalla stringa
    valid = sscanf(buffer, "%d", &anno);

    if (valid != 1 || anno < 1900 || anno > 2025) {
        printf(ROSSO "Errore: anno non valido. Deve essere compreso tra 1900 e 2025.\n" RESET);
    }
    } while (valid != 1 || anno < 1900 || anno > 2025);

    do {
        printf(BLU "Inserisci il prezzo orario del noleggio (minimo 20.00): " RESET);
        scanf("%f", &prezzo);
        if (prezzo < 20.0) {
            printf(ROSSO "Errore: il prezzo orario non può essere inferiore a 20.00.\n" RESET);
        }
    } while (prezzo < 20.0);

    Auto a = creaAuto(targa, marca, modello, anno, prezzo);
    if (!a) {
        printf(ROSSO "Errore nella creazione dell'auto.\n" RESET);
        return;
    }

    if (inserisciAuto(ht, a)) {
        printf(VERDE "Auto inserita correttamente!\n" RESET);
    } else {
        printf(ROSSO "Auto già presente nella tabella.\n" RESET);
    }
}

// Gestione del menu sviluppatore
List gestisciMenuDeveloper(int scelta, AutoHashTable *ht, List l, HashTable tabUtenti) {
    switch (scelta) {
        case 1:
            aggiungiAutoInterattivo(ht);
            stampaHashTableAuto(*ht);
            break;

        case 2: {
            char targa[8];
            do {
                printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
                scanf("%7s", targa);

                if (!validaTarga(targa)) {
                    printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
                }
            } while (!validaTarga(targa));

            Auto a = rimuoviAuto(ht, targa);
            if (a) {
                distruggiAuto(a);
                printf(VERDE "Auto eliminata con successo.\n" RESET);
            } else {
                printf(ROSSO "Auto non trovata.\n" RESET);
            }
        }
            break;

        case 3:
          printf("\n");
          stampaHashTableAuto(*ht);
            break;
        case 4:
            printf("\n");
            stampaListaPrenotazioni(l);
            break;

        case 5:
            printf(BLU "Visualizzazione storico prenotazioni...\n" RESET);
            stampaStoricoTuttiUtenti(tabUtenti);
            break;
        case 6:
            printf(BLU "Avanza di una settimana settimana...\n" RESET);
            aggiungiPrenotazioniAStoricoUtenti(tabUtenti, l);
            resetDisponibilitaTutteLeAuto(*ht);
            distruggiLista(l);
            l = newList();
            break;
        case 7:
            printf("Uscita dal menu sviluppatore...\n");
            break;

        default:
            printf(ROSSO "Opzione non valida. Riprova.\n" RESET);
            break;
    }
    return l;
}


// Mostra il menu sviluppatore e restituisce la scelta
int mostraMenuDeveloper() {
    int scelta;
    printf("\n" CIANO "*----------------------------------------------------*\n");
    printf(        "|             Car Sharing - Sviluppatore             |\n");
    printf(        "*----------------------------------------------------*\n");

    printf(        "| " RESET GIALLO "1." RESET " Aggiungi nuova auto                             " CIANO "|\n");
    printf(        "| " RESET GIALLO "2." RESET " Rimuovi auto esistente                          " CIANO "|\n");
    printf(        "| " RESET GIALLO "3." RESET " Visualizza tutte le auto                        " CIANO "|\n");
    printf(        "| " RESET GIALLO "4." RESET " Visualizza tutte le prenotazioni                " CIANO "|\n");
    printf(        "| " RESET GIALLO "5." RESET " Visualizza storico prenotazioni                 " CIANO "|\n");
    printf(        "| " RESET GIALLO "6." RESET " Avanza di una settimana                         " CIANO "|\n");
    printf(        "| " RESET ROSSO "7." RESET " Esci                                            " CIANO "|\n");

    printf(        "*----------------------------------------------------*\n");
    printf(BLU "Scelta: " RESET);

    scanf("%d", &scelta);
    return scelta;
}

int selezionaRuolo() {
    int scelta;
    do {
        printf("\n" CIANO "*--------------------------------------*\n");
        printf(        "|       Seleziona il tuo ruolo         |\n");
        printf(        "*--------------------------------------*\n");
        printf(        "| " RESET GIALLO "1." RESET " Utente                            " CIANO "|\n");
        printf(        "| " RESET GIALLO "2." RESET " Sviluppatore                      " CIANO "|\n");
        printf(        "| " RESET ROSSO "0." RESET " Esci                              " CIANO "|\n");
        printf(        "*--------------------------------------*\n");
        printf(BLU "Scelta: " RESET);

        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2 && scelta != 0);

    return scelta;
}
