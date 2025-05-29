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

/*
    * Definizione di costanti per la gestione delle marche e modelli delle auto.
 */
#define MAX_MODELLI 5
#define MAX_AUTO 5
#define NUM_MARCHE 5
#define MAX_LUNGHEZZA 20

/*
    * Struttura per rappresentare una marca e i suoi modelli.
    * La struttura contiene il nome della marca e un array di modelli associati.
    * Il numero di modelli è limitato da MAX_MODELLI.
 */
typedef struct {
    const char *marca;
    const char *modelli[MAX_MODELLI];
    int numeroModelli;
} MarcaModelli;

// Database delle marche e modelli delle auto
MarcaModelli databaseMarche[NUM_MARCHE] = {
    {"Fiat", {"Panda", "500", "Tipo", "Punto", "Bravo"}, 5},
    {"BMW", {"Serie 1", "Serie 3", "Serie 5", "X1", "X3"}, 5},
    {"Toyota", {"Yaris", "Corolla", "CHR", "RAV4", "Auris"}, 5},
    {"Ford", {"Fiesta", "Focus", "Kuga", "Puma", "Mondeo"}, 5},
    {"Alfa Romeo", {"Giulia", "Stelvio", "Tonale", "147", "156"}, 5}
};

/*
* Funzione per trovare una marca nel database.
* * Parametri:
* - `marca`: la marca da cercare.
* * Restituisce l'indice della marca nel database se trovata, altrimenti -1.
 */
int trovaMarca(const char *marca) {
    for (int i = 0; i < NUM_MARCHE; i++) {
        // Confronto case-insensitive tra la marca cercata e le marche nel database
        if (confrontaCaseInsensitive(marca, databaseMarche[i].marca)) {
            return i;
        }
    }
    return -1;
}

/*
* Funzione per verificare la presenza di un modello in una marca.
* * Parametri:
* - `modello`: il modello da cercare.
* - `marca`: puntatore alla struttura MarcaModelli che contiene i modelli della marca.
* * Restituisce 1 se il modello è presente, altrimenti 0.
 */
int modelloPresente(const char *modello, const MarcaModelli *marca) {
    for (int i = 0; i < marca->numeroModelli; i++) {
        // Confronto case-insensitive tra il modello cercato e i modelli della marca
        if (confrontaCaseInsensitive(modello, marca->modelli[i])) {
            return 1;
        }
    }
    return 0;
}

/*
* Funzione per inserire una marca e un modello di auto.
* * Parametri:
* - `marca`: puntatore a una stringa dove verrà memorizzata la marca inserita.
* - `modello`: puntatore a una stringa dove verrà memorizzato il modello inserito.
* * La funzione richiede all'utente di inserire una marca e un modello,
*  * verificando che la marca sia valida e che il modello sia presente per quella marca.
 */
void inserisciMarcaModello(char *marca, char *modello) {
    int indiceMarca;

    while(getchar() != '\n');

    // Ciclo per l'inserimento della marca
    // Si richiede all'utente di inserire una marca valida
    do {
        // Stampa le marche disponibili
        do {
            printf(GIALLO "Le marche disponibili del nostro CarSharing sono:\n" RESET);
            for (int i = 0; i < NUM_MARCHE; i++) {
                printf(CIANO " - " RESET "%s\n", databaseMarche[i].marca);
            }
            // Input marca
            printf(BLU "\nInserisci la marca dell'auto: " RESET);
            fgets(marca, MAX_LUNGHEZZA, stdin);
            marca[strcspn(marca, "\n")] = '\0';
            // Controllo se la marca inserita è valida
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

        // Controllo se il modello inserito è valido
        if (!stringaValida(modello)) {
            printf(ROSSO "Modello non valido. Usa solo lettere, numeri e spazi.\n" RESET);
        } else if (!modelloPresente(modello, marcaSelezionata)) {
            printf(ROSSO "Modello non riconosciuto per la marca %s.\n" RESET, marcaSelezionata->marca);
        }
    } while (!stringaValida(modello) || !modelloPresente(modello, marcaSelezionata));
}



/*
 * Funzione per aggiungere un'auto interattivamente.
* * Parametri:
* - `ht`: puntatore alla tabella hash delle auto.
 * La funzione richiede all'utente di inserire i dettagli dell'auto,
 * come targa, marca, modello, posizione, anno e prezzo orario.
 * Se l'auto con la stessa targa esiste già, viene visualizzato un messaggio di errore.
 * Se l'inserimento è valido, l'auto viene aggiunta alla tabella hash.
 */
void aggiungiAutoInterattivo(AutoHashTB *ht) {
    char targa[8], marca[20], modello[20], posizione[35], buffer[100];
    char *endptr;
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

    if(cercaAuto(*ht, targa)) {
        printf(ROSSO "Errore: auto con targa %s gia' presente.\n" RESET, targa);
        return;
    }

    inserisciMarcaModello(marca, modello);

    do {
    printf(BLU "Inserisci l'anno di immatricolazione (es. 2000 - 2025): " RESET);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // Errore o EOF
        printf(ROSSO "Errore nella lettura.\n" RESET);
        continue;
    }

    valid = sscanf(buffer, "%d", &anno);

    // Controllo se l'input è valido
    if (valid != 1 || anno < 1900 || anno > 2025) {
        printf(ROSSO "Errore: anno non valido. Deve essere compreso tra 1900 e 2025.\n" RESET);
    }
    } while (valid != 1 || anno < 1900 || anno > 2025);

    // Inserimento della posizione dell'auto
    do{
		printf(BLU "Inserisci la posizione dell'auto (es. Via Roma 123): " RESET);
		fgets(posizione, sizeof(posizione), stdin);
        posizione[strcspn(posizione, "\n")] = '\0';
        // Controllo se la posizione è valida
    }while(!validaViaStradale(posizione));	//si suppone che l'utente riporta l'auto nella stessa via

    capitalizza(posizione);    // Capitalizza la posizione per uniformità
    do {
        printf(BLU "Inserisci il prezzo orario del noleggio (minimo 10.00|massimo 45.00): " RESET);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Rimuovi nuova linea finale se presente
            buffer[strcspn(buffer, "\n")] = '\0';

            prezzo = strtof(buffer, &endptr);

            // Controlla se c'erano caratteri non numerici
            if (endptr == buffer || *endptr != '\0') {
                printf(ROSSO "Errore: inserisci un numero valido (es. 15.99).\n" RESET);
                prezzo = 0.0; // Imposta a valore sotto soglia per ripetere
            } else if (prezzo < 10.0 || prezzo > 45.0) {
                printf(ROSSO "Errore: il prezzo orario non puo' essere inferiore a 10.00 o maggiore di 45.00\n" RESET);
            }
        }
    } while (prezzo < 10.0 || prezzo > 45.00);

    // Creazione dell'auto
    Auto a = creaAuto(targa, marca, modello, posizione, anno, prezzo);
    // Controllo se l'auto è stata creata correttamente
    if (!a) {
        printf(ROSSO "Errore nella creazione dell'auto.\n" RESET);
        distruggiAuto(a);
        return;
    }

    inserisciAuto(ht, a);
    printf(VERDE "Auto inserita correttamente!\n" RESET);
}

/*
    * Funzione per gestire il menu dello sviluppatore.
* * Parametri:
* - `scelta`: l'opzione scelta dallo sviluppatore.
* - `ht`: puntatore alla tabella hash delle auto.
* - `l`: lista delle prenotazioni.
* - `tabUtenti`: tabella hash degli utenti.
* * La funzione esegue l'azione corrispondente all'opzione scelta dallo sviluppatore.
* * Le opzioni includono l'aggiunta di un'auto, la rimozione di un'auto,
*  * la visualizzazione delle auto, la visualizzazione delle prenotazioni,
* * la visualizzazione dello storico delle prenotazioni e l'avanzamento di una settimana.
* * Se l'opzione scelta è 7, la funzione termina il menu.
 */
Lista gestisciMenuSviluppatore(int scelta, AutoHashTB *ht, Lista l, UtentiHashTB tabUtenti) {
    switch (scelta) {
        case 1:
            aggiungiAutoInterattivo(ht);
            stampaAutoHashTB(*ht);
            break;

        case 2:
          	if(!*ht) {
                printf(ROSSO "Non sono presenti auto da eliminare.\n" RESET);
                break;
            }
            char targa[8];
            do {
                printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
                scanf("%7s", targa);

                // Controllo se la targa è valida
                if (!validaTarga(targa)) {
                    printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
                }
            } while (!validaTarga(targa));
            while(getchar() != '\n'); // pulizia buffer

            Auto a = rimuoviAuto(ht, targa);
            if (a) {
                distruggiAuto(a);
                printf(VERDE "Auto eliminata con successo.\n" RESET);
            } else {
                printf(ROSSO "Auto non trovata.\n" RESET);
            }
            break;

        case 3:
          printf("\n");
          stampaAutoHashTB(*ht);
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

            aggiungiPrenotazioniAStoricoUtenti(tabUtenti, l);    // Aggiungi le prenotazioni alla coda di storico degli utenti
            reimpostaDisponibilitaTutteLeAuto(*ht);    // Reimposta la disponibilità di tutte le auto
            distruggiLista(l);    // Distrugge la lista delle prenotazioni
            l = nuovaLista();    // Crea una nuova lista per le prenotazioni della settimana successiva
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

/*
    * Funzione per mostrare il menu dello sviluppatore.
    * * Restituisce l'opzione scelta dallo sviluppatore.
    * * Il menu include opzioni per aggiungere un'auto, rimuovere un'auto,
    *  * visualizzare le auto, visualizzare le prenotazioni, visualizzare lo storico delle prenotazioni,
    * * avanzare di una settimana e uscire dal menu.
 */
int mostraMenuSviluppatore() {
    char buffer[100];    // Buffer per la lettura dell'input
    int scelta;
    int valido = 0;    // Variabile per verificare se la scelta è valida

    // Ciclo per mostrare il menu e ottenere una scelta valida
    do {
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

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // rimuovi nuova linea
            buffer[strcspn(buffer, "\n")] = '\0';

            // prova a leggere un intero
            if (sscanf(buffer, "%d", &scelta) == 1 && scelta >= 1 && scelta <= 7) {
                valido = 1;
            } else {
                printf(ROSSO "Errore: inserisci un numero valido tra 1 e 7.\n" RESET);
            }
        }
    } while (!valido);

    return scelta;
}

/*
 * Funzione per selezionare il ruolo dell'utente.
 * * Restituisce l'opzione scelta dall'utente:
 * - 0 per uscire,
 * - 1 per utente,
 * - 2 per sviluppatore.
 */
int selezionaRuolo() {
    char buffer[100];    // Buffer per la lettura dell'input
    int scelta;
    int valido = 0;    // Variabile per verificare se la scelta è valida

    // Ciclo per mostrare il menu e ottenere una scelta valida
    do {
        printf("\n" CIANO "*--------------------------------------*\n");
        printf(        "|       Seleziona il tuo ruolo         |\n");
        printf(        "*--------------------------------------*\n");
        printf(        "| " RESET GIALLO "1." RESET " Utente                            " CIANO "|\n");
        printf(        "| " RESET GIALLO "2." RESET " Sviluppatore                      " CIANO "|\n");
        printf(        "| " RESET ROSSO "0." RESET " Esci                              " CIANO "|\n");
        printf(        "*--------------------------------------*\n");
        printf(BLU "Scelta: " RESET);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Rimuove nuova linea
            buffer[strcspn(buffer, "\n")] = '\0';

            // Verifica che sia un numero valido
            if (sscanf(buffer, "%d", &scelta) == 1 && (scelta == 0 || scelta == 1 || scelta == 2 || scelta == 3)) {
                valido = 1;
            } else {
                printf(ROSSO "Errore: inserisci 0, 1 o 2.\n" RESET);
            }
        }
    } while (!valido);

    // Pulisce la console dopo la scelta
	pulisciConsole();

    return scelta;
}
