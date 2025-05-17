#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Utile_DevMenu.h"
#include "HashTbAuto.h" // Nome corretto del file hash auto
#include "HashTbUtenti.h"  // Gestione utenti se necessario

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
        printf("Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): ");
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf("Errore: formato targa non valido. Riprova.\n");
        }
    } while (!validaTarga(targa));


    printf("Inserisci la marca dell'auto: ");
    scanf("%19s", marca);

    printf("Inserisci il modello dell'auto: ");
    scanf("%19s", modello);

    do {
        printf("Inserisci l'anno di immatricolazione (es. 2000 - 2025): ");
        scanf("%d", &anno);
        if (anno < 1900 || anno > 2025) {
            printf("Errore: anno non valido. Deve essere compreso tra 1900 e 2025.\n");
        }
    } while (anno < 1900 || anno > 2025);

    do {
        printf("Inserisci il prezzo orario del noleggio (minimo 20.00): ");
        scanf("%f", &prezzo);
        if (prezzo < 20.0) {
            printf("Errore: il prezzo orario non può essere inferiore a 20.00.\n");
        }
    } while (prezzo < 20.0);

    Auto a = creaAuto(targa, marca, modello, anno, prezzo);
    if (!a) {
        printf("Errore nella creazione dell'auto.\n");
        return;
    }

    if (inserisciAuto(ht, a)) {
        printf("Auto inserita correttamente.\n");
    } else {
        printf("Auto già presente nella tabella.\n");
    }
}

// Gestione del menu sviluppatore
void gestisciMenuDeveloper(int scelta, AutoHashTable *ht, List l){
    switch (scelta) {
        case 1:
            aggiungiAutoInterattivo(ht);
            stampaHashTableAuto(*ht);
            break;

        case 2: {
            char targa[8];
            do {
                printf("Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): ");
                scanf("%7s", targa);

                if (!validaTarga(targa)) {
                    printf("Errore: formato targa non valido. Riprova.\n");
                }
            } while (!validaTarga(targa));

            Auto a = rimuoviAuto(ht, targa);
            if (a) {
                distruggiAuto(a);
                printf("Auto eliminata con successo.\n");
            } else {
                printf("Auto non trovata.\n");
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
            break;

        case 5:
            printf("Chiusura applicazione...\n");
            break;

        default:
            printf("Opzione non valida. Riprova.\n");
            break;
    }
}

// Mostra il menu sviluppatore e restituisce la scelta
int mostraMenuDeveloper() {
    int scelta;
    printf("\n========== Car Sharing - Menu Sviluppatore ==========\n");
    printf("1. Aggiungi nuova auto\n");
    printf("2. Rimuovi auto esistente\n");
    printf("3. Visualizza tutte le prenotazioni\n");
    printf("4. Visualizza storico prenotazioni\n");
    printf("5. Esci dal programma\n");
    printf("=====================================================\n");
    printf("Scelta: ");
    scanf("%d", &scelta);
    return scelta;
}

// Chiede se si è utente o sviluppatore
int selezionaRuolo() {
    int scelta;
    do {
        printf("Seleziona il tuo ruolo:\n");
        printf("1. Utente\n");
        printf("2. Sviluppatore\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2 && scelta != 0);

    return scelta;
}
