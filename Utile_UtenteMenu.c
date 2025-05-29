#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
#include "prenotazione.h"
#include "Utile_UtenteMenu.h"
#include "Auto.h"
#include "Utente.h"
#include "Controlli.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta.*/
#define RESET  "\x1b[0m"
#define ROSSO    "\x1b[31m"
#define VERDE  "\x1b[32m"
#define GIALLO "\x1b[33m"
#define BLU   "\x1b[34m"
#define CIANO   "\x1b[36m"

/*
 * Funzione che gestisce il menu per l'utente.
 * Parametri:
 * - `scelta`: la scelta dell'utente.
 * - `u`: l'utente che sta effettuando la prenotazione.
 * - `l`: la lista delle prenotazioni.
 * - `tabAuto`: la tabella hash delle auto disponibili.
 * La funzione gestisce le operazioni che l'utente può effettuare,
 * Prende in input la scelta dell'utente, un utente e una lista di prenotazioni.
 * Restituisce la lista aggiornata delle prenotazioni.
 */
Lista switchUtente(int scelta, Utente u, Lista l, AutoHashTB tabAuto) {
    char * CF = malloc(sizeof(char) * 17);
    char * targa = malloc(sizeof(char) * 8);
    int * giornoInizio = malloc(sizeof(int));
    int * giornoFine = malloc(sizeof(int));
    int * oraInizio = malloc(sizeof(int));
    int * oraFine = malloc(sizeof(int));
    int stato = 0;
    // Funzione per gestire le scelte dell'utente
    switch (scelta) {
        case 1:
            printf(BLU "Prenotazione auto...\n" RESET);
            if(tabAuto == NULL) {
                printf(ROSSO "ERRORE! Non sono presenti auto disponibili per prenotare.\n" RESET);
                break;
            }
            else{
                // Chiamata alla funzione per inserire i dati della prenotazione
                inserimentoPrenotazione(CF, targa, giornoInizio, giornoFine, oraInizio, oraFine, u);
            	l = prenotazioneAuto(l, tabAuto, CF, targa, giornoInizio, giornoFine, oraInizio, oraFine, &stato);
                if(!stato){
                  printf(ROSSO "Prenotazione non riuscita. Controlla i dati inseriti.\n" RESET);
                }
            }
            break;
        case 2:
            printf(BLU "Calcolo tariffa per auto prenotata...\n" RESET);
            calcolaPrezziPrenotazioni(l, u, tabAuto);
            break;
        case 3:
            printf(BLU "Visualizzazione auto disponibili...\n" RESET);
            visualizzaAutoDisponibili(tabAuto);
            break;
        case 4:
            printf(BLU "Visualizzazione prenotazioni...\n" RESET);
            visPrenotazioniPerUtente(l, ottieniCF(u));
            break;
        case 5:
            printf(BLU "Visualizzazione prenotazioni precedenti...\n" RESET);
            stampaStorico(ottieniStorico(u));
            break;
        case 6:
            printf(VERDE "Uscita menu utente...\n" RESET);
            break;
        default:
            printf(ROSSO "Opzione non valida. Riprova.\n" RESET);
            break;
    }
    return l;
}

/* * Funzione che mostra il menu per l'utente e gestisce la scelta dell'utente.
 * Parametri:
 * - Nessuno.
 * Restituisce la scelta dell'utente come un intero.
 * Il menu permette di prenotare un'auto, calcolare la tariffa per un'auto prenotata,
 * visualizzare le auto disponibili, visualizzare le prenotazioni e uscire dal menu.
 */
int menuUtente() {
    char buffer[100];
    int scelta;
    int valido = 0;

    // Ciclo per mostrare il menu e gestire la scelta dell'utente
    do {
        printf("\n" CIANO "*----------------------------------------------------*\n");
        printf(        "|                Car Sharing - Utente                |\n");
        printf(        "*----------------------------------------------------*\n");

        printf(        "| " RESET GIALLO "1." RESET " Prenotazione auto                               " CIANO "|\n");
        printf(        "| " RESET GIALLO "2." RESET " Calcolo tariffa per auto prenotata              " CIANO "|\n");
        printf(        "| " RESET GIALLO "3." RESET " Visualizza auto disponibili                     " CIANO "|\n");
        printf(        "| " RESET GIALLO "4." RESET " Visualizza prenotazioni                         " CIANO "|\n");
        printf(        "| " RESET GIALLO "5." RESET " Visualizza prenotazioni precedenti              " CIANO "|\n");
        printf(        "| " RESET ROSSO  "6." RESET " Esci                                            " CIANO "|\n");

        printf(        "*----------------------------------------------------*\n");
        printf(BLU"Scelta: " RESET);

        // Legge l'input dell'utente
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Rimuove nuova linea

            // Verifica se input è un intero valido tra 1 e 6
            if (sscanf(buffer, "%d", &scelta) == 1 && scelta >= 1 && scelta <= 6) {
                valido = 1;
            } else {
                printf(ROSSO "Errore: inserisci un numero valido tra 1 e 6.\n" RESET);
            }
        }
    } while (!valido);

    return scelta;
}

/* Funzione per inserire i dati della prenotazione.
 * Parametri:
 * - `CF`: il codice fiscale dell'utente.
 * - `targa`: la targa dell'auto da prenotare.
 * - `giornoInizio`: puntatore al giorno di inizio della prenotazione.
 * - `giornoFine`: puntatore al giorno di fine della prenotazione.
 * - `oraInizio`: puntatore all'ora di inizio della prenotazione.
 * - `oraFine`: puntatore all'ora di fine della prenotazione.
 * - `u`: l'utente che sta effettuando la prenotazione.
 * Restituisce 1 se l'inserimento è andato a buon fine, altrimenti 0.
 */
int inserimentoPrenotazione(char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, Utente u) {
    char buffer[100];   // Buffer per l'input dell'utente
    strcpy(CF, ottieniCF(u));


    do {
        printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
        }
    } while (!validaTarga(targa));
    while ((getchar()) != '\n');  // Pulisce il buffer


    while (1) {
        printf(GIALLO "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        // Legge il giorno di inizio
        if (sscanf(buffer, "%d", giornoInizio) != 1 || *giornoInizio < 1 || *giornoInizio > 7) {
            printf(ROSSO "Errore: il giorno deve essere un numero da 1 a 7.\n" RESET);
        } else {
            break;
        }
    }

    // Giorno fine
    while (1) {
        printf(GIALLO "Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", giornoFine) != 1 || *giornoFine < *giornoInizio || *giornoFine > 7) {
            printf(ROSSO "Errore: il giorno di fine deve essere compreso tra %d e 7.\n" RESET, *giornoInizio);
        } else {
            break;
        }
    }

    // Ora inizio
    while (1) {
        printf(GIALLO "Inserisci l'ora di inizio (0-23): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", oraInizio) != 1 || *oraInizio < 0 || *oraInizio > 23) {
            printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 0 e 23 (0 = mezzanotte, 23 = 23:00).\n" RESET);
        } else {
            break;
        }
    }

    // Ora fine
    while (1) {
        printf(GIALLO "Inserisci l'ora di fine (1-24): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", oraFine) != 1 || *oraFine < 1 || *oraFine > 24) {
            printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 1 e 24 (24 = mezzanotte).\n" RESET);
        } else if (*giornoInizio == *giornoFine && *oraFine <= *oraInizio) {
            printf(ROSSO "Errore: per lo stesso giorno, l'ora di fine deve essere maggiore dell'ora di inizio.\n" RESET);
        } else {
            break;
        }
    }

    return 1;
}

/* * Funzione per prenotare un'auto.
 * Parametri:
 * - `l`: la lista delle prenotazioni.
 * - `tabAuto`: la tabella hash delle auto disponibili.
 * - `CF`: il codice fiscale dell'utente.
 * - `targa`: la targa dell'auto da prenotare.
 * - `giornoInizio`: puntatore al giorno di inizio della prenotazione.
 * - `giornoFine`: puntatore al giorno di fine della prenotazione.
 * - `oraInizio`: puntatore all'ora di inizio della prenotazione.
 * - `oraFine`: puntatore all'ora di fine della prenotazione.
 * - `stato`: puntatore allo stato della prenotazione (1 = successo, 0 = fallimento).
 * Restituisce la lista aggiornata delle prenotazioni.
 */
Lista prenotazioneAuto(Lista l, AutoHashTB tabAuto, char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, int *stato) {
    Auto a = cercaAuto(tabAuto, targa);
    if(a == NULL) {
        printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        *stato = 0;
        return l;
    }

	*giornoInizio = *giornoInizio -1;
    *giornoFine = *giornoFine -1;

    // Controllo disponibilità dell'auto
    if (verificaDisponibilita(a, *giornoInizio, *giornoFine, *oraInizio, *oraFine)) {
        impostaDisponibile(a, *giornoInizio, *giornoFine, *oraInizio, *oraFine, true);
        Prenotazione nuovaPrenotazione = creaPrenotazione(CF, targa, *giornoInizio, *giornoFine, *oraInizio, *oraFine);
        l = consLista(nuovaPrenotazione, l);
        printf(VERDE "Prenotazione registrata con successo!\n" RESET);
        *stato = 1;
    } else {
        printf(ROSSO "Auto non disponibile nel periodo selezionato.\n" RESET);
        *stato = 0;
    }

    return l;
}

/* Funzione per visualizzare le auto disponibili in un intervallo di giorni e ore.
 * Parametri:
 * - `ht`: la tabella hash delle auto.
 * - `giornoInizio`: il giorno di inizio della prenotazione (1 = lunedì, ..., 7 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (1 = lunedì, ..., 7 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce le auto disponibili in un formato tabellare.
 */
void visualizzaAutoDisponibiliConParametri(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    if (!ht) {
        printf(ROSSO "Nessuna auto registrata.\n" RESET);
        return;
    }

    // Validazione
    if (giornoInizio < 1 || giornoInizio > 7 ||
        giornoFine < giornoInizio || giornoFine > 7 ||
        oraInizio < 0 || oraInizio > 23 ||
        oraFine < 1 || oraFine > 24 ||
        (giornoInizio == giornoFine && oraFine <= oraInizio)) {
        printf(ROSSO "Parametri non validi per la visualizzazione della disponibilità.\n" RESET);
        return;
        }


    giornoInizio--;
    giornoFine--;

    // Stampa la tabella di hash per le auto disponibili
    stampaTabellaDiHashPerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}

/* Funzione per visualizzare le auto disponibili in un intervallo di giorni e ore.
 * Parametri:
 * - `ht`: la tabella hash delle auto.
 * La funzione chiede all'utente di inserire i parametri per la visualizzazione
 * e chiama `visualizzaAutoDisponibiliConParametri` per mostrare le auto disponibili.
 * Restituisce le auto disponibili in un formato tabellare.
 */
void visualizzaAutoDisponibili(AutoHashTB ht) {
    if (!ht) {
        printf(ROSSO "Nessuna auto registrata.\n" RESET);
        return;
    }

    // Variabili per i parametri di ricerca
    int giornoInizio, giornoFine, oraInizio, oraFine;
    char buffer[100];

    // Giorno inizio
    while (1) {
        printf(GIALLO "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &giornoInizio) != 1 || giornoInizio < 1 || giornoInizio > 7) {
            printf(ROSSO "Errore: il giorno deve essere un numero da 1 a 7.\n" RESET);
        } else {
            break;
        }
    }

    // Giorno fine
    while (1) {
        printf(GIALLO "Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &giornoFine) != 1 || giornoFine < giornoInizio || giornoFine > 7) {
            printf(ROSSO "Errore: il giorno di fine deve essere compreso tra %d e 7.\n" RESET, giornoInizio);
        } else {
            break;
        }
    }

    // Ora inizio
    while (1) {
        printf(GIALLO "Inserisci l'ora di inizio (0-23): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &oraInizio) != 1 || oraInizio < 0 || oraInizio > 23) {
            printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 0 e 23.\n" RESET);
        } else {
            break;
        }
    }

    // Ora fine
    while (1) {
        printf(GIALLO "Inserisci l'ora di fine (1-24): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &oraFine) != 1 || oraFine < 1 || oraFine > 24) {
            printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 1 e 24.\n" RESET);
        } else if (giornoInizio == giornoFine && oraFine <= oraInizio) {
            printf(ROSSO "Errore: per lo stesso giorno, l'ora di fine deve essere maggiore dell'ora di inizio.\n" RESET);
        } else {
            break;
        }
    }


    visualizzaAutoDisponibiliConParametri(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}


/* * Funzione per calcolare le ore totali di una prenotazione.
 * Parametri:
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce le ore totali della prenotazione.
 */
int calcolaOreTotali(int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int oreInizio = giornoInizio * 24 + oraInizio;
    int oreFine = giornoFine * 24 + oraFine;

    int oreTotali = oreFine - oreInizio;  // Inclusivo
    return oreTotali;
}

/* * Funzione per calcolare il prezzo di una prenotazione.
 * Parametri:
 * - `a`: l'auto di cui calcolare il prezzo.
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce il prezzo totale della prenotazione.
 */
float calcolaPrezzo(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzoOrario = ottieniPrezzo(a);
    int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
    return prezzoOrario * oreTotali;
}

/* * Funzione per calcolare lo sconto in base ai giorni della settimana (weekend).
 * Parametri:
 * - `prezzo`: il prezzo originale della prenotazione.
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * Restituisce il prezzo scontato se applicabile, altrimenti il prezzo originale.
 */
float calcolaSconto(float prezzo, int giornoInizio, int giornoFine) {
    if ((giornoInizio == 5 || giornoInizio == 6) && (giornoFine == 5 || giornoFine == 6)) {
        return prezzo * 0.9f;  // 10% di sconto
    }
    return prezzo;
}

/* * Funzione per calcolare lo sconto in base alle ore totali prenotate.
 * Parametri:
 * - `prezzo`: il prezzo originale della prenotazione.
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce il prezzo scontato se applicabile, altrimenti il prezzo originale.
 */
float calcolaScontoOre(float prezzo, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
    if (oreTotali >= 10) {
        return prezzo * 0.8f;  // 20% di sconto
    }
    return prezzo;
}

/* * Funzione per calcolare lo sconto in base alla fascia oraria.
 * Parametri:
 * - `prezzo`: il prezzo originale della prenotazione.
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce il prezzo scontato se applicabile, altrimenti il prezzo originale.
 */
float calcolaScontoFasciaOraria(float prezzo, int oraInizio, int oraFine) {
    if (oraInizio >= 20 || oraFine <= 8) {
        return prezzo * 0.85f;  // 15% di sconto
    }
    return prezzo;
}

/* Funzione per calcolare il prezzo finale di una prenotazione.
 * Parametri:
 * - `a`: l'auto di cui calcolare il prezzo.
 * - `giornoInizio`: il giorno di inizio della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `giornoFine`: il giorno di fine della prenotazione (0 = lunedì, ..., 6 = domenica).
 * - `oraInizio`: l'ora di inizio della prenotazione (0-23).
 * - `oraFine`: l'ora di fine della prenotazione (1-24).
 * Restituisce il prezzo finale della prenotazione dopo aver applicato gli sconti.
 */
float calcolaPrezzoFinale(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzo = calcolaPrezzo(a, giornoInizio, giornoFine, oraInizio, oraFine);
    // Applica gli sconti
    prezzo = calcolaSconto(prezzo, giornoInizio, giornoFine);
    prezzo = calcolaScontoOre(prezzo, giornoInizio, giornoFine, oraInizio, oraFine);
    prezzo = calcolaScontoFasciaOraria(prezzo, oraInizio, oraFine);
    return prezzo;
}

/* Funzione per calcolare i prezzi delle prenotazioni di un utente.
 * Parametri:
 * - `prenotazioni`: la lista delle prenotazioni.
 * - `u`: l'utente di cui calcolare i prezzi.
 * - `ht`: la tabella hash delle auto disponibili.
 * Restituisce il totale dei prezzi delle prenotazioni dell'utente.
 */
float calcolaPrezziPrenotazioni(Lista prenotazioni, Utente u, AutoHashTB ht) {
    int giornoInizio, giornoFine, oraInizio, oraFine;

    // Controllo se l'utente è valido
    if (!u) {
        printf(ROSSO "Utente non valido.\n" RESET);
        return -1.0f;  // Errore
    }

    const char *cf = ottieniCF(u);
    Lista listaUtente = filtraPrenotazioniPerCF(prenotazioni, cf);  // Filtra le prenotazioni per l'utente

    // Controllo se la lista delle prenotazioni dell'utente è vuota
    if (ListaVuota(listaUtente)) {
        printf(ROSSO "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, cf);
        return -1.0f;  // Errore
    }

    printf(GIALLO "Prezzi delle prenotazioni per l'utente con CF: %s\n" RESET, cf);

    float totale = 0.0f;
    Lista temp = listaUtente;

    // Itera attraverso le prenotazioni dell'utente
    while (!ListaVuota(temp)) {
        Prenotazione p = ottieniPrimo(temp);
        const char *targa = ottieniTargaPrenotazione(p);
        Auto a = cercaAuto(ht, targa);

        if (!a) {
            printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        } else {
            ottieniPeriodoPrenotazione(p, &giornoInizio, &giornoFine, &oraInizio, &oraFine);

            // Calcola le ore totali e il prezzo finale
            int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
            float prezzoFinale = calcolaPrezzoFinale(a, giornoInizio, giornoFine, oraInizio, oraFine);
            totale += prezzoFinale;

            // Stampa i dettagli della prenotazione
            printf("\n--------------------------\n");
            stampaPrenotazione(p);

            if (oraInizio >= 20 || oraFine <= 8) {
                printf(VERDE "Sconto del 15%% per prenotazioni notturne.\n" RESET);
            }
            if (oreTotali >= 10) {
                printf(VERDE "Sconto del 20%% per prenotazioni di 10 ore o piu'.\n" RESET);
            }
            if ((giornoInizio == 5 || giornoInizio == 6) && (giornoFine == 5 || giornoFine == 6)) {
                printf(VERDE "Sconto del 10%% per prenotazioni nel weekend.\n" RESET);
            }

            printf(GIALLO "Prezzo finale per questa prenotazione: %.2f\n" RESET, prezzoFinale);
        }

        temp = codaLista(temp);
    }

    printf("\n" GIALLO "Totale complessivo per tutte le prenotazioni dell'utente: %.2f\n" RESET, totale);

    distruggiLista(listaUtente);
    return totale;
}


