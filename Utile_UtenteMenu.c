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
#define BLUE   "\x1b[34m"
#define CIANO   "\x1b[36m"

List switchUtente(int scelta, Utente u, List l, AutoHashTable tabAuto) {
    // Funzione per gestire le scelte dell'utente
    switch (scelta) {
        case 1:
            printf(BLUE "Prenotazione auto...\n" RESET);
            l = prenotazioneAuto(l, u, tabAuto);
            break;
        case 2:
            printf(BLUE "Calcolo tariffa per auto prenotata...\n" RESET);
            calcolaPrezziPrenotazioni(l, u, tabAuto);
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
            stampaStorico(getStorico(u));
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
    int scelta;

    printf("\n" CIANO "*----------------------------------------------------*\n");
    printf(        "|                Car Sharing - Utente                |\n");
    printf(        "*----------------------------------------------------*\n");

    printf(        "| " RESET GIALLO "1." RESET " Prenotazione auto                               " CIANO "|\n");
    printf(        "| " RESET GIALLO "2." RESET " Calcolo tariffa per auto prenotata              " CIANO "|\n");
    printf(        "| " RESET GIALLO "3." RESET " Visualizza auto disponibili                     " CIANO "|\n");
    printf(        "| " RESET GIALLO "4." RESET " Visualizza prenotazioni                         " CIANO "|\n");
    printf(        "| " RESET GIALLO "5." RESET " Visualizza prenotazioni precedenti              " CIANO "|\n");

    printf(        "| " RESET ROSSO "6." RESET " Esci                                            " CIANO "|\n");

    printf(        "*----------------------------------------------------*\n");
    printf(BLUE "Scelta: " RESET);

    scanf("%d", &scelta);\
    return scelta;
}


List prenotazioneAuto(List l, Utente u, AutoHashTable tabAuto) {
    char CF[17], targa[10];
    Auto a;
    int giornoInizio, giornoFine, oraInizio, oraFine;
    bool flag = true;

    strcpy(CF, getCF(u));

    do {
        printf(GIALLO "Inserisci la targa dell'auto: " RESET);
        scanf("%s", targa);
        a = cercaAuto(tabAuto, targa);
        if (a == NULL) {
            printf(ROSSO "Targa non trovata. Riprova.\n" RESET);
        }
    } while (a == NULL);

    do {
        printf(GIALLO "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
        scanf("%d", &giornoInizio);
        if (giornoInizio < 1 || giornoInizio > 7) {
            printf(ROSSO "Errore: il giorno deve essere un numero da 1 a 7.\n" RESET);
        }
    } while (giornoInizio < 1 || giornoInizio > 7);

    do {
        printf(GIALLO "Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): " RESET);
        scanf("%d", &giornoFine);
        if (giornoFine < giornoInizio || giornoFine > 7) {
            printf(ROSSO "Errore: il giorno di fine deve essere compreso tra %d e 7.\n" RESET, giornoInizio);
        }
    } while (giornoFine < giornoInizio || giornoFine > 7);

    do {
        printf(GIALLO "Inserisci l'ora di inizio (1-24): " RESET);
        scanf("%d", &oraInizio);
        if (oraInizio < 1 || oraInizio > 24) {
            printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 1 e 24 (1 = 01:00, 24 = mezzanotte).\n" RESET);
        }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
        printf(GIALLO "Inserisci l'ora di fine (max 24): " RESET);
        scanf("%d", &oraFine);
        if (oraFine < 1 || oraFine > 24) {
            printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 1 e 24.\n" RESET);
        } else if (giornoInizio == giornoFine && oraFine < oraInizio) {
            printf(ROSSO "Errore: per prenotazioni nello stesso giorno, l'ora di fine deve essere >= ora di inizio.\n" RESET);
        } else {
            break;  // orario valido
        }
    } while (1);


    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    if (verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
        setDisponibile(a, giornoInizio, giornoFine, oraInizio, oraFine, true);
        printf(VERDE "Prenotazione registrata con successo!\n" RESET);
    } else {
        printf(ROSSO "Auto non disponibile nel periodo selezionato.\n" RESET);
        flag = false;
    }

    if(flag){
    Prenotazione nuovaPrenotazione = creaPrenotazione(CF, targa, giornoInizio, giornoFine, oraInizio, oraFine);
    l = consList(nuovaPrenotazione, l);
    }
    return l;
}

void visualizzaAutoDisponibili(AutoHashTable ht) {
    if (!ht) {
        printf(ROSSO "Nessuna auto registrata.\n" RESET);
        return;
    }

    int giornoInizio, giornoFine, oraInizio, oraFine;

    do {
    printf(GIALLO "Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): " RESET);
    scanf("%d", &giornoInizio);
    if (giornoInizio < 1 || giornoInizio > 7) {
        printf(ROSSO "Errore: il giorno deve essere un numero da 1 a 7.\n" RESET);
    }
} while (giornoInizio < 1 || giornoInizio > 7);

    do {
        printf(GIALLO "Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): " RESET);
        scanf("%d", &giornoFine);
        if (giornoFine < giornoInizio || giornoFine > 7) {
            printf(ROSSO "Errore: il giorno di fine deve essere compreso tra %d e 7.\n" RESET, giornoInizio);
        }
    } while (giornoFine < giornoInizio || giornoFine > 7);

    do {
        printf(GIALLO "Inserisci l'ora di inizio (1-24): " RESET);
        scanf("%d", &oraInizio);
        if (oraInizio < 1 || oraInizio > 24) {
            printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 1 e 24 (1 = 01:00, 24 = mezzanotte).\n" RESET);
        }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
        printf(GIALLO "Inserisci l'ora di fine (max 24): " RESET);
        scanf("%d", &oraFine);
        if (oraFine < 1 || oraFine > 24) {
            printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 1 e 24.\n" RESET);
        } else if (giornoInizio == giornoFine && oraFine < oraInizio) {
            printf(ROSSO "Errore: per prenotazioni nello stesso giorno, l'ora di fine deve essere >= ora di inizio.\n" RESET);
        } else {
            break;  // orario valido
        }
    } while (1);


    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    stampaHashTablePerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}

//funzione per calcolare il prezzo della prenotazione
float calcolaPrezzo(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzo = getPrezzo(a);
    int giorni = giornoFine - giornoInizio + 1;
    // Calcola il numero di ore prenotate 24/24 da 0 a 24
    int ore = oraFine - oraInizio;
    if(ore <= 0) {
        ore += 24; // Se l'ora di fine è minore dell'ora di inizio, aggiungi 24 ore
    }
    return prezzo * giorni * ore;
}
//funzione per calcolare uno sconto sulla prenotazione su determinati orari
float calcolaSconto(float prezzo, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    // Sconto del 10% se la prenotazione è per il weekend (sabato e domenica)
    if ((giornoInizio == 5 || giornoInizio == 6) && (giornoFine == 5 || giornoFine == 6)) {
        return prezzo * 0.9; // Sconto del 10%
    }
    return prezzo;
}
//funzione per calcolare lo sconto in base alla fascia oraria della prenotazione
float calcolaScontoFasciaOraria(float prezzo, int oraInizio, int oraFine) {
    // Sconto del 15% se la prenotazione è effettuata tra le 20:00 e le 8:00
    if ((oraInizio >= 20 || oraFine <= 8)) {

        return prezzo * 0.85; // Sconto del 15%
    }
    return prezzo;
}

//funzione per calcolare lo sconto in base alla quantità di ore prenotate
float calcolaScontoOre(float prezzo, int oraInizio, int oraFine, int giornoInizio, int giornoFine) {
  float ore = oraFine - oraInizio;
  int giorni = giornoFine - giornoInizio + 1;
    if(ore <= 0) {
        ore += 24; // Se l'ora di fine è minore dell'ora di inizio, aggiungi 24 ore
    }
    if (ore >= 10 || giorni > 1) {

        return prezzo * 0.8; // Sconto del 20% per 10 o più ore
    }
    return prezzo;
}

//funzione per calcolare il prezzo finale della prenotazione
float calcolaPrezzoFinale(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzo = calcolaPrezzo(a, giornoInizio, giornoFine, oraInizio, oraFine);
    prezzo = calcolaSconto(prezzo, giornoInizio, giornoFine, oraInizio, oraFine);
    prezzo = calcolaScontoOre(prezzo, oraInizio, oraFine, giornoInizio, giornoFine);
    prezzo = calcolaScontoFasciaOraria(prezzo, oraInizio, oraFine);
    return prezzo;
}

void calcolaPrezziPrenotazioni(List prenotazioni, Utente u, AutoHashTable ht) {
    int giornoInizio, giornoFine, oraInizio, oraFine;
    float ore= oraFine - oraInizio;
    if(ore <= 0) {
        ore += 24; // Se l'ora di fine è minore dell'ora di inizio, aggiungi 24 ore
    }
    int giorni = giornoFine - giornoInizio + 1;
    if (!u) {
        printf(ROSSO "Utente non valido.\n" RESET);
        return;
    }

    const char *cf = getCF(u);  // recupera il codice fiscale dell'utente
    List listaUtente = filtraPrenotazioniPerCF(prenotazioni, cf);

    if (emptyList(listaUtente)) {
        printf(ROSSO "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, cf);
        return;
    }

    printf(GIALLO "Prezzi delle prenotazioni per l'utente con CF: %s\n" RESET, cf);

    float totale = 0.0;

    List temp = listaUtente;  // puntatore per scorrere senza perdere la testa

    while (!emptyList(temp)) {
        Prenotazione p = getFirst(temp);
        const char *targa = getTargaPrenotazione(p);

        Auto a = cercaAuto(ht, targa);
        if (!a) {
            printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        } else {
            getPeriodoPrenotazione(p, &giornoInizio, &giornoFine, &oraInizio, &oraFine);

            float prezzoFinale = calcolaPrezzoFinale(a, giornoInizio, giornoFine, oraInizio, oraFine);
            totale += prezzoFinale;

            printf("\n--------------------------\n");
            stampaPrenotazione(p);  // stampa dettagli prenotazione
            if ((oraInizio >= 20 || oraFine <= 8)) {
      printf(VERDE "Sconto del 15%% per prenotazioni notturne.\n" RESET);

    }
            if (ore >= 10 || giorni > 1) {
      printf(VERDE "Sconto del 20%% per prenotazioni di 10 ore o piu'.\n" RESET);

    }
             if ((giornoInizio == 5 || giornoInizio == 6) && (giornoFine == 5 || giornoFine == 6)) {
             printf(VERDE "Sconto del 10%% per prenotazioni nel weekend.\n" RESET);
    }
            printf(GIALLO "Prezzo finale per questa prenotazione: %.2f\n" RESET, prezzoFinale);


        }

        temp = tailList(temp);
    }

    printf("\n" GIALLO "Totale complessivo per tutte le prenotazioni dell'utente: %.2f\n" RESET, totale);

    distruggiLista(listaUtente);  // distruggi la lista temporanea
}


