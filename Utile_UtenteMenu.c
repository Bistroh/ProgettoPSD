#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
#include "prenotazione.h"
#include "Utile_UtenteMenu.h"
#include "Auto.h"
#include "Utente.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta.*/
#define RESET  "\x1b[0m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE   "\x1b[34m"
#define CYAN   "\x1b[36m"

List switchUtente(int scelta, Utente u, List l, AutoHashTable tabAuto) {
    // Funzione per gestire le scelte dell'utente
    switch (scelta) {
        case 1:
            printf(BLUE "Prenotazione auto...\n" RESET);
            l = prenotazioneAuto(l, u, tabAuto);
            break;
        case 2:
            printf(BLUE "Calcolo tariffa per auto prenotata...\n" RESET);
            break;
        case 3:
            printf(BLUE "Visualizzazione auto disponibili...\n" RESET);
            visualizzaAutoDisponibili(tabAuto);
            break;
        case 4:
            printf(BLUE "Visualizzazione prenotazioni...\n" RESET);
            visPrenotazioniPerUtente(l, getCF(u));
            break;
        case 5:
            printf(BLUE "Visualizzazione prenotazioni precedenti...\n" RESET);
            break;
        case 6:
            printf(GREEN "Uscita menu utente...\n" RESET);
            break;
        default:
            printf(RED "Opzione non valida. Riprova.\n" RESET);
            break;
    }
    return l;
}

int menuUtente() {
    int scelta;

    printf("\n" CYAN "*----------------------------------------------------*\n");
    printf(        "|                Car Sharing - Utente                |\n");
    printf(        "*----------------------------------------------------*\n");

    printf(        "| " RESET YELLOW "1." RESET " Prenotazione auto                               " CYAN "|\n");
    printf(        "| " RESET YELLOW "2." RESET " Calcolo tariffa per auto prenotata              " CYAN "|\n");
    printf(        "| " RESET YELLOW "3." RESET " Visualizza auto disponibili                     " CYAN "|\n");
    printf(        "| " RESET YELLOW "4." RESET " Visualizza prenotazioni                         " CYAN "|\n");
    printf(        "| " RESET YELLOW "5." RESET " Visualizza prenotazioni precedenti              " CYAN "|\n");
    printf(        "| " RESET RED "6." RESET " Esci                                            " CYAN "|\n");

    printf(        "*----------------------------------------------------*\n");
    printf(BLUE "Scelta: " RESET);

    scanf("%d", &scelta);\
    return scelta;
}


List prenotazioneAuto(List l, Utente u, AutoHashTable tabAuto) {
    char CF[17], targa[10];
    Auto a;
    int giornoInizio, giornoFine, oraInizio, oraFine;

    strcpy(CF, getCF(u));

    do {
        printf(YELLOW "Inserisci la targa dell'auto: " RESET);
        scanf("%s", targa);
        a = cercaAuto(tabAuto, targa);
        if (a == NULL) {
            printf(RED "Targa non trovata. Riprova.\n" RESET);
        }
    } while (a == NULL);

    do {
        printf(YELLOW "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
        scanf("%d", &giornoInizio);
        if (giornoInizio < 1 || giornoInizio > 7) {
            printf(RED "Errore: il giorno deve essere un numero da 1 a 7.\n" RESET);
        }
    } while (giornoInizio < 1 || giornoInizio > 7);

    do {
        printf(YELLOW "Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): " RESET);
        scanf("%d", &giornoFine);
        if (giornoFine < giornoInizio || giornoFine > 7) {
            printf(RED "Errore: il giorno di fine deve essere compreso tra %d e 7.\n" RESET, giornoInizio);
        }
    } while (giornoFine < giornoInizio || giornoFine > 7);

    do {
        printf(YELLOW "Inserisci l'ora di inizio (1-24): " RESET);
        scanf("%d", &oraInizio);
        if (oraInizio < 1 || oraInizio > 24) {
            printf(RED "Errore: l'ora di inizio deve essere compresa tra 1 e 24 (1 = 01:00, 24 = mezzanotte).\n" RESET);
        }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
        printf(YELLOW "Inserisci l'ora di fine (>= ora inizio, max 24): " RESET);
        scanf("%d", &oraFine);
        if (oraFine < oraInizio || oraFine > 24) {
            printf(RED "Errore: l'ora di fine deve essere compresa tra %d e 24.\n" RESET, oraInizio);
        }
    } while (oraFine < oraInizio || oraFine > 24);

    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    if (verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
        setDisponibile(a, giornoInizio, giornoFine, oraInizio, oraFine, true);
        printf(GREEN "Prenotazione registrata con successo!\n" RESET);
    } else {
        printf(RED "Auto non disponibile nel periodo selezionato.\n" RESET);
        exit(1);
    }

    Prenotazione nuovaPrenotazione = creaPrenotazione(CF, targa, giornoInizio, giornoFine, oraInizio, oraFine);
    l = consList(nuovaPrenotazione, l);
    return l;
}

void visualizzaAutoDisponibili(AutoHashTable ht) {
    if (!ht) {
        printf(RED "Nessuna auto registrata.\n" RESET);
        return;
    }

    int giornoInizio, giornoFine, oraInizio, oraFine;

    do {
        printf(YELLOW "Inserisci il giorno di inizio della fascia (1=lun, ..., 7=dom): " RESET);
        scanf("%d", &giornoInizio);
        if (giornoInizio < 1 || giornoInizio > 7) {
            printf(RED "Errore: giorno valido è tra 1 e 7.\n" RESET);
        }
    } while (giornoInizio < 1 || giornoInizio > 7);

    do {
        printf(YELLOW "Inserisci il giorno di fine della fascia (>= inizio, max 7): " RESET);
        scanf("%d", &giornoFine);
        if (giornoFine < giornoInizio || giornoFine > 7) {
            printf(RED "Errore: giorno di fine deve essere tra %d e 7.\n" RESET, giornoInizio);
        }
    } while (giornoFine < giornoInizio || giornoFine > 7);

    do {
        printf(YELLOW "Inserisci l'ora di inizio (1-24): " RESET);
        scanf("%d", &oraInizio);
        if (oraInizio < 1 || oraInizio > 24) {
            printf(RED "Errore: ora di inizio deve essere tra 1 e 24.\n" RESET);
        }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
        printf(YELLOW "Inserisci l'ora di fine (>= inizio, max 24): " RESET);
        scanf("%d", &oraFine);
        if (oraFine < oraInizio || oraFine > 24) {
            printf(RED "Errore: ora di fine deve essere tra %d e 24.\n" RESET, oraInizio);
        }
    } while (oraFine < oraInizio || oraFine > 24);

    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    stampaHashTablePerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}


void visualizzaStorico() {
    printf(YELLOW "Visualizzazione prenotazioni precedenti...\n" RESET);
    // TODO: Aggiungere logica di visualizzazione storico
}



