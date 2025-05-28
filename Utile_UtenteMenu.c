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

int menuUtente() {
    char buffer[100];
    int scelta;
    int valido = 0;

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

//funzione che prende in input i dati per la prenotazione
int inserimentoPrenotazione(char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, Utente u) {
    char buffer[100];
    strcpy(CF, ottieniCF(u));

    do {
        printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
        }
    } while (!validaTarga(targa));
    while ((getchar()) != '\n');  // Pulisce il buffer

    // Giorno inizio
    while (1) {
        printf(GIALLO "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

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


Lista prenotazioneAuto(Lista l, AutoHashTB tabAuto, char *CF, char *targa, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine, int *stato) {
    Auto a = cercaAuto(tabAuto, targa);
    if(a == NULL) {
        printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        *stato = 0;
        return l;
    }

	*giornoInizio = *giornoInizio -1;
    *giornoFine = *giornoFine -1;

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

    // Conversione 0-based
    giornoInizio--;
    giornoFine--;

    stampaTabellaDiHashPerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}

void visualizzaAutoDisponibili(AutoHashTB ht) {
    if (!ht) {
        printf(ROSSO "Nessuna auto registrata.\n" RESET);
        return;
    }

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


// Calcolo ore effettive
int calcolaOreTotali(int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int oreInizio = giornoInizio * 24 + oraInizio;
    int oreFine = giornoFine * 24 + oraFine;

    int oreTotali = oreFine - oreInizio;  // Inclusivo
    return oreTotali;
}

// Funzione per calcolare il prezzo base della prenotazione
float calcolaPrezzo(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzoOrario = ottieniPrezzo(a);
    int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
    return prezzoOrario * oreTotali;
}

// Sconto per weekend (sabato = 5, domenica = 6)
float calcolaSconto(float prezzo, int giornoInizio, int giornoFine) {
    if ((giornoInizio == 5 || giornoInizio == 6) && (giornoFine == 5 || giornoFine == 6)) {
        return prezzo * 0.9f;  // 10% di sconto
    }
    return prezzo;
}

// Sconto per prenotazioni lunghe (>= 10 ore)
float calcolaScontoOre(float prezzo, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
    if (oreTotali >= 10) {
        return prezzo * 0.8f;  // 20% di sconto
    }
    return prezzo;
}

// Sconto per fascia oraria notturna (tutta la prenotazione deve essere notturna)
float calcolaScontoFasciaOraria(float prezzo, int oraInizio, int oraFine) {
    if (oraInizio >= 20 || oraFine <= 8) {
        return prezzo * 0.85f;  // 15% di sconto
    }
    return prezzo;
}

// Prezzo finale dopo tutti gli sconti
float calcolaPrezzoFinale(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzo = calcolaPrezzo(a, giornoInizio, giornoFine, oraInizio, oraFine);
    prezzo = calcolaSconto(prezzo, giornoInizio, giornoFine);
    prezzo = calcolaScontoOre(prezzo, giornoInizio, giornoFine, oraInizio, oraFine);
    prezzo = calcolaScontoFasciaOraria(prezzo, oraInizio, oraFine);
    return prezzo;
}

// Calcolo per tutte le prenotazioni di un utente
float calcolaPrezziPrenotazioni(Lista prenotazioni, Utente u, AutoHashTB ht) {
    int giornoInizio, giornoFine, oraInizio, oraFine;

    if (!u) {
        printf(ROSSO "Utente non valido.\n" RESET);
        return -1.0f;  // Errore
    }

    const char *cf = ottieniCF(u);
    Lista listaUtente = filtraPrenotazioniPerCF(prenotazioni, cf);

    if (ListaVuota(listaUtente)) {
        printf(ROSSO "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, cf);
        return -1.0f;  // Errore
    }

    printf(GIALLO "Prezzi delle prenotazioni per l'utente con CF: %s\n" RESET, cf);

    float totale = 0.0f;
    Lista temp = listaUtente;

    while (!ListaVuota(temp)) {
        Prenotazione p = ottieniPrimo(temp);
        const char *targa = ottieniTargaPrenotazione(p);
        Auto a = cercaAuto(ht, targa);

        if (!a) {
            printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        } else {
            ottieniPeriodoPrenotazione(p, &giornoInizio, &giornoFine, &oraInizio, &oraFine);

            int oreTotali = calcolaOreTotali(giornoInizio, giornoFine, oraInizio, oraFine);
            float prezzoFinale = calcolaPrezzoFinale(a, giornoInizio, giornoFine, oraInizio, oraFine);
            totale += prezzoFinale;

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

    return totale;
    distruggiLista(listaUtente);
}


