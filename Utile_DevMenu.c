#include <stdio.h>
#include <stdlib.h>
#include "Utile_DevMenu.h"
#include "HashTbAuto.h" // Nome corretto del file hash auto
#include "HashTbUtenti.h"  // Gestione utenti se necessario

// Funzione per inserire una nuova auto nella hash table
void aggiungiAutoInterattivo(AutoHashTable *ht) {
    char targa[10], marca[20], modello[20];
    int anno;
    float prezzo;

    printf("Inserisci la targa dell'auto: ");
    scanf("%9s", targa);

    printf("Inserisci la marca dell'auto: ");
    scanf("%19s", marca);

    printf("Inserisci il modello dell'auto: ");
    scanf("%19s", modello);

    printf("Inserisci l'anno di immatricolazione: ");
    scanf("%d", &anno);

    printf("Inserisci il prezzo orario del noleggio: ");
    scanf("%f", &prezzo);

    Auto a = creaAuto(targa, marca, modello, anno, prezzo);
    if (!a) {
        printf("Errore nella creazione dell'auto.\n");
        return;
    }

    if (inserisciAuto(ht, a)) {
        printf("Auto inserita correttamente.\n");
    } else {
        printf("Auto già presente nella tabella.\n");
        distruggiAuto(a); // libera se non inserita
    }
}

// Gestione del menu sviluppatore
void gestisciMenuDeveloper(int scelta, AutoHashTable *ht) {
    switch (scelta) {
        case 1:
            aggiungiAutoInterattivo(ht);
            stampaHashTableAuto(*ht);
            break;

        case 2: {
            char targa[10];
            printf("Inserisci la targa dell'auto da eliminare: ");
            scanf("%9s", targa);

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
            printf("Visualizzazione prenotazioni di tutti gli utenti...\n");
            // TODO: Aggiungere implementazione
            break;

        case 4:
            printf("Visualizzazione storico prenotazioni...\n");
            // TODO: Aggiungere implementazione
            break;

        case 5:
            printf("Chiusura applicazione...\n");
            exit(EXIT_SUCCESS);

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
        printf("Scelta: ");
        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2);

    return scelta;
}
