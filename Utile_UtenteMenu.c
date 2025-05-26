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

List switchUtente(int scelta, Utente u, List l, AutoHashTable tabAuto) {
    // Funzione per gestire le scelte dell'utente
    switch (scelta) {
        case 1:
            printf(BLU "Prenotazione auto...\n" RESET);
            if(tabAuto == NULL) {
                printf(ROSSO "ERRORE! Non sono presenti auto disponibili per prenotare.\n" RESET);
                break;
            }
            else{
            	l = prenotazioneAuto(l, u, tabAuto);
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
            visPrenotazioniPerUtente(l, getCF(u));
            break;
        case 5:
            printf(BLU "Visualizzazione prenotazioni precedenti...\n" RESET);
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
            buffer[strcspn(buffer, "\n")] = '\0';  // Rimuove newline

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


List prenotazioneAuto(List l, Utente u, AutoHashTable tabAuto) {
    char CF[17], targa[10], buffer[100];
    Auto a;
    int giornoInizio, giornoFine, oraInizio, oraFine;
    bool flag = true;

    strcpy(CF, getCF(u));

    do {
        printf(BLU "Inserisci la targa dell'auto (formato: 2 lettere + 3 cifre + 2 lettere, es: AB123CD): " RESET);
        scanf("%7s", targa);

        if (!validaTarga(targa)) {
            printf(ROSSO "Errore: formato targa non valido. Riprova.\n" RESET);
        }
    } while (!validaTarga(targa));
    while ((getchar()) != '\n');  // Pulisce il buffer

    a = cercaAuto(tabAuto, targa);
    if (a == NULL) {
      printf(ROSSO "Errore: auto con targa %s non trovata.\n" RESET, targa);
	  while ((getchar()) != '\n');  // Pulisce il buffer
	  return l;
    }

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
        	printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 0 e 23 (0 = mezzanotte, 23 = 23:00).\n" RESET);
    	} else {
        	break;
    	}
	}

	// Ora fine
	while (1) {
    	printf(GIALLO "Inserisci l'ora di fine (0-23): " RESET);
    	fgets(buffer, sizeof(buffer), stdin);

    	if (sscanf(buffer, "%d", &oraFine) != 1 || oraFine < 0 || oraFine > 23) {
        	printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 0 e 23.\n" RESET);
    	} else if (giornoInizio == giornoFine && oraFine < oraInizio) {
        	printf(ROSSO "Errore: per prenotazioni nello stesso giorno, l'ora di fine deve essere >= ora di inizio.\n" RESET);
    	} else {
        	break;
    	}
	}

	giornoInizio--, giornoFine--;

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
        	printf(ROSSO "Errore: l'ora di inizio deve essere compresa tra 0 e 23 (0 = mezzanotte, 23 = 23:00).\n" RESET);
    	} else {
        	break;
    	}
	}

	// Ora fine
	while (1) {
		printf(GIALLO "Inserisci l'ora di fine (0-23): " RESET);
    	fgets(buffer, sizeof(buffer), stdin);

    	if (sscanf(buffer, "%d", &oraFine) != 1 || oraFine < 0 || oraFine > 23) {
        	printf(ROSSO "Errore: l'ora di fine deve essere compresa tra 0 e 23.\n" RESET);
    	} else if (giornoInizio == giornoFine && oraFine < oraInizio) {
        	printf(ROSSO "Errore: per prenotazioni nello stesso giorno, l'ora di fine deve essere >= ora di inizio.\n" RESET);
    	} else {
        	break;
    	}
	}

	giornoInizio--, giornoFine--;

    stampaHashTablePerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}

// Calcolo ore effettive
int calcolaOreTotali(int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int oreInizio = giornoInizio * 24 + oraInizio;
    int oreFine = giornoFine * 24 + oraFine;

    int oreTotali = oreFine - oreInizio + 1;  // Inclusivo
    return oreTotali;
}

// Funzione per calcolare il prezzo base della prenotazione
float calcolaPrezzo(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    float prezzoOrario = getPrezzo(a);
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
void calcolaPrezziPrenotazioni(List prenotazioni, Utente u, AutoHashTable ht) {
    int giornoInizio, giornoFine, oraInizio, oraFine;

    if (!u) {
        printf(ROSSO "Utente non valido.\n" RESET);
        return;
    }

    const char *cf = getCF(u);
    List listaUtente = filtraPrenotazioniPerCF(prenotazioni, cf);

    if (emptyList(listaUtente)) {
        printf(ROSSO "Nessuna prenotazione trovata per l'utente con CF: %s\n" RESET, cf);
        return;
    }

    printf(GIALLO "Prezzi delle prenotazioni per l'utente con CF: %s\n" RESET, cf);

    float totale = 0.0f;
    List temp = listaUtente;

    while (!emptyList(temp)) {
        Prenotazione p = getFirst(temp);
        const char *targa = getTargaPrenotazione(p);
        Auto a = cercaAuto(ht, targa);

        if (!a) {
            printf(ROSSO "Auto con targa %s non trovata.\n" RESET, targa);
        } else {
            getPeriodoPrenotazione(p, &giornoInizio, &giornoFine, &oraInizio, &oraFine);

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

        temp = tailList(temp);
    }

    printf("\n" GIALLO "Totale complessivo per tutte le prenotazioni dell'utente: %.2f\n" RESET, totale);

    distruggiLista(listaUtente);
}


