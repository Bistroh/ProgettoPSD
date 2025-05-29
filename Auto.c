#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Auto.h"
#define MAX_GIORNI_LAVORATIVI 7
#define MAX_ORA_LAVORATIVI 24
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define CIANO    "\x1b[36m"

/*
*    La struttura `s_auto` contiene i seguenti campi:
* - `targa`: una stringa che rappresenta la targa dell'auto.
* - `marca`: una stringa che rappresenta la marca dell'auto.
* - `modello`: una stringa che rappresenta il modello dell'auto.
* - `posizione`: una stringa che rappresenta la posizione dell'auto.
* - `anno`: un intero che rappresenta l'anno di produzione dell'auto.
* - `prezzoXOra`: un float che rappresenta il prezzo per ora di noleggio dell'auto.
* - `disponibile`: una matrice booleana che indica la disponibilità dell'auto
*    in un determinato giorno e ora.
*    La matrice ha dimensioni MAX_GIORNI_LAVORATIVI x MAX_ORA_LAVORATIVI,
*    dove MAX_GIORNI_LAVORATIVI è il numero di giorni lavorativi
*    MAX_ORA_LAVORATIVI è il numero di ore lavorative in un giorno.
*/
struct s_auto {
    char targa[10];
    char marca[20];
    char modello[20];
    char posizione[35];
    int anno;
    float prezzoXOra;
	bool disponibile[MAX_GIORNI_LAVORATIVI][MAX_ORA_LAVORATIVI];
};

/*
* Funzione per creare una nuova auto.
* La funzione inizializza anche la matrice `disponibile` a `false` per tutti i giorni e le ore.
* Parametri:
* - `targa`: la targa dell'auto.
* - `marca`: la marca dell'auto.
* - `modello`: il modello dell'auto.
* - `posizione`: la posizione dell'auto.
* - `anno`: l'anno di produzione dell'auto.
* - `prezzoXOra`: il prezzo per ora di noleggio dell'auto.
* Restituisce un puntatore a una nuova struttura `s_auto` allocata dinamicamente.
* Se l'allocazione della memoria fallisce, il programma termina con un errore.
 */
Auto creaAuto(char *targa, char *marca, char *modello, char*posizione, int anno, float prezzoXOra) {
    Auto a = malloc(sizeof(struct s_auto));
    // Controlla se l'allocazione della memoria è riuscita
    if (a == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
        exit(EXIT_FAILURE);
    }
    // Copia le stringhe nei campi dell'auto, assicurandosi di non superare i limiti
    strncpy(a->targa, targa, sizeof(a->targa) - 1);
    a->targa[sizeof(a->targa) - 1] = '\0';
    strncpy(a->marca, marca, sizeof(a->marca) - 1);
    a->marca[sizeof(a->marca) - 1] = '\0';
    strncpy(a->modello, modello, sizeof(a->modello) - 1);
    a->modello[sizeof(a->modello) - 1] = '\0';
    strncpy(a->posizione, posizione, sizeof(a->posizione) - 1);
    a->posizione[sizeof(a->posizione) - 1] = '\0';
    // Inizializza la matrice di disponibilità a false
    for (int g = 0; g < MAX_GIORNI_LAVORATIVI; g++) {
        for (int o = 0; o < MAX_ORA_LAVORATIVI; o++) {
            a->disponibile[g][o] = false;
        }
    }
    a->anno = anno;
    a->prezzoXOra = prezzoXOra;
    return a;
}
// Le seguenti funzioni accedono ai campi marca, modello, posizione, anno e prezzoXOra della struttura Auto
char *ottieniTarga(Auto a) {
    return a->targa;
}

char *ottieniMarca(Auto a) {
    return a->marca;
}

char *ottieniModello(Auto a) {
    return a->modello;
}

char *ottieniPosizione(Auto a) {
    return a->posizione;
}

int ottieniAnno(Auto a) {
    return a->anno;
}

float ottieniPrezzo(Auto a) {
    return a->prezzoXOra;
}

// Funzione per distruggere un'auto e liberare la memoria
void distruggiAuto(Auto a) {
 	// Controlla se l'auto è NULL prima di liberare la memoria
    if (a != NULL) {
        free(a);
    }
}

/*
* Imposta la disponibilità dell'auto in un intervallo di giorni e ore.
* Parametri:
* - `a`: puntatore all'auto da modificare.
* - `giornoInizio`: il giorno di inizio dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `giornoFine`: il giorno di fine dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `oraInizio`: l'ora di inizio dell'intervallo (0-23).
* - `oraFine`: l'ora di fine dell'intervallo (1-24, dove 24 indica la mezzanotte del giorno successivo).
* - `stato`: lo stato di disponibilità da impostare (true = disponibile, false = non disponibile).
* La funzione verifica che l'intervallo di giorni e ore sia valido e che l'auto sia disponibile in quell'intervallo.
* Se l'intervallo non è valido o l'auto non è disponibile, stampa un messaggio di errore.
 */
void impostaDisponibile(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine, bool stato) {
    if (!a || !a->disponibile) return;	    // Controllo se l'auto è NULL o non disponibile

    // Verifica che l'intervallo sia valido e disponibile
    if (!verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
        fprintf(stderr, ROSSO "Intervallo giorno/ora non valido o non disponibile\n" RESET);
        return;
    }
	// Controllo validità intervallo giorno/ora
    for (int g = giornoInizio; g <= giornoFine; g++) {
        int oraStart = (g == giornoInizio) ? oraInizio : 0;
        int oraEnd   = (g == giornoFine)  ? oraFine    : 24;

        // Se l'ultimo giorno ha oraFine == 0, non occupare nulla
        if (g == giornoFine && oraFine == 0) continue;

        // Controllo validità intervallo minimo: almeno 1 ora
        for (int o = oraStart; o < oraEnd; o++) {
            a->disponibile[g][o] = stato;
        }
    }
}

/*
* Funzione per verificare la disponibilità dell'auto in un intervallo di giorni e ore.
* Parametri:
* - `a`: puntatore all'auto da verificare.
* - `giornoInizio`: il giorno di inizio dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `giornoFine`: il giorno di fine dell'intervallo (0 = Lunedì, 6 = Domenica).
* - `oraInizio`: l'ora di inizio dell'intervallo (0-23).
* - `oraFine`: l'ora di fine dell'intervallo (1-24, dove 24 indica la mezzanotte del giorno successivo).
* La funzione restituisce 1 se l'auto è disponibile nell'intervallo specificato,
* 0 altrimenti.
 */
int verificaDisponibilita(Auto a, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    if (!a) return 0;	// Controllo se l'auto è NULL

    // Controllo validità intervallo giorno/ora
    if (giornoInizio < 0 || giornoFine >= MAX_GIORNI_LAVORATIVI ||
        oraInizio < 0 || oraInizio > 23 || oraFine < 1 || oraFine > 24 ||
        giornoInizio > giornoFine) {
        fprintf(stderr, ROSSO "Intervallo giorno/ora non valido nella verifica disponibilita'\n" RESET);
        return 0;
        }

    // Controllo validità intervallo minimo: almeno 1 ora
    if (giornoInizio == giornoFine && oraFine <= oraInizio) {
        fprintf(stderr, ROSSO "Intervallo orario non valido nello stesso giorno\n" RESET);
        return 0;
    }

    // Controllo se l'auto è disponibile nell'intervallo specificato
    for (int g = giornoInizio; g <= giornoFine; g++) {
        int oraStart = (g == giornoInizio) ? oraInizio : 0;
        int oraEnd   = (g == giornoFine)  ? oraFine : MAX_ORA_LAVORATIVI;

        // Special case: se giornoInizio == giornoFine e oraFine == 24,
        // allora va bene; ma se giornoFine == giornoInizio + 1 e oraFine == 0,
        // non deve fare nulla
        if (giornoInizio != giornoFine && g == giornoFine && oraFine == 0) {
            continue; // niente da controllare in quel giorno
        }

        for (int o = oraStart; o < oraEnd; o++) {
            if (a->disponibile[g][o]) return 0; // già occupato
        }
    }

    return 1; // tutto disponibile
}

/*
* Funzione per stampare le informazioni di un'auto.
* Parametri:
* - `a`: puntatore all'auto da stampare.
* La funzione stampa i campi dell'auto, inclusa la targa, marca, modello,
 */
void stampaAuto(Auto a) {
    printf(CIANO "Targa:           " RESET "%s\n", a->targa);
    printf(CIANO "Marca:           " RESET "%s\n", a->marca);
    printf(CIANO "Modello:         " RESET "%s\n", a->modello);
    printf(CIANO "Posizione:       " RESET "%s\n", a->posizione);
    printf(CIANO "Anno:            " RESET "%d\n", a->anno);
    printf(CIANO "Prezzo per ora:  " RESET "%.2f\n", a->prezzoXOra);
}

/*
* Funzione per reimpostare la disponibilità di un'auto.
* Questa funzione imposta tutti i giorni e le ore come non disponibili (false).
* Parametri:
* - `a`: puntatore all'auto da reimpostare.
* La funzione non restituisce nulla.
 */
void reimpostaDisponibileAuto(Auto a) {
    if (!a) return;

    for (int g = 0; g < MAX_GIORNI_LAVORATIVI; g++) {
        for (int o = 0; o < MAX_ORA_LAVORATIVI; o++) {
            a->disponibile[g][o] = false;
        }
    }
}

