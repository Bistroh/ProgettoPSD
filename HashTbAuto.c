#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auto.h"
#include "HashTbAuto.h"
#include "uthash.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define CIANO    "\x1b[36m"
#define BIANCO   "\x1b[37m"

/*
    * La struttura AutoRecord rappresenta un record nella tabella hash per le auto.
* Contiene:
* - `targa`: una stringa che funge da chiave per identificare l'auto.
* - `autoPtr`: un puntatore all'oggetto Auto associato a quella targa.
* - `hh`: un handler per uthash che permette di gestire la tabella hash.
* * La tabella hash è utilizzata per memorizzare e gestire le auto in modo efficiente,
 */
typedef struct AutoRecord {
    char *targa;
    Auto autoPtr;
    UT_hash_handle hh;
} AutoRecord;

typedef AutoRecord* AutoHashTB;  // Tipo alias

// Crea una nuova hash table (inizializzata a NULL)
AutoHashTB creaAutoHashTB() {
    return NULL;
}

/*
* Funzione per inserire un'auto nella tabella hash.
* * Parametri:
* - `ht`: puntatore alla tabella hash in cui inserire l'auto.
* - `a`: l'auto da inserire.
* * Restituisce 1 se l'inserimento è riuscito, 0 se l'auto è già presente.
* * Controlla se la tabella hash o l'auto sono NULL, e se la targa dell'auto è valida.
* * Se l'auto è già presente nella tabella, non la inserisce e restituisce 0.
 */
int inserisciAuto(AutoHashTB *ht, Auto a) {
    // Controlla se la tabella hash o l'auto sono NULL
    if (!a || !ht) return 0;

    const char *targa = ottieniTarga(a);
    if (!targa) return 0;

    AutoRecord *record = NULL;
    HASH_FIND_STR(*ht, targa, record);
    if (record) return 0;

    // Crea un nuovo record per l'auto e controlla l'allocazione
    record = malloc(sizeof(AutoRecord));
    if (!record) {
        fprintf(stderr, ROSSO "Errore allocazione memoria AutoRecord\n" RESET);
        exit(EXIT_FAILURE);
    }

    //strdup per copiare la targa
    record->targa = strdup(targa);
    record->autoPtr = a;
    HASH_ADD_KEYPTR(hh, *ht, record->targa, strlen(record->targa), record);

    return 1;
}


/*
* Funzione per cercare un'auto nella tabella hash per targa.
* * Parametri:
* - `ht`: la tabella hash in cui cercare l'auto.
* - `targa`: la targa dell'auto da cercare.
* * Restituisce un puntatore all'auto se trovata, altrimenti NULL.
 */
Auto cercaAuto(AutoHashTB ht, const char *targa) {
    if (!targa) return NULL;

    AutoRecord *record = NULL;
    // Cerca il record nella tabella hash usando la targa come chiave
    HASH_FIND_STR(ht, targa, record);
    return record ? record->autoPtr : NULL;
}

/*
* Funzione per rimuovere un'auto dalla tabella hash per targa.
* * Parametri:
* - `ht`: puntatore alla tabella hash da cui rimuovere l'auto.
* - `targa`: la targa dell'auto da rimuovere.
* * Restituisce un puntatore all'auto rimossa se trovata, altrimenti NULL.
 */
Auto rimuoviAuto(AutoHashTB *ht, const char *targa) {
    // Controlla se la tabella hash o la targa sono NULL
    if (!ht || !targa) return NULL;

    AutoRecord *record = NULL;
    // Cerca il record nella tabella hash usando la targa come chiave
    HASH_FIND_STR(*ht, targa, record);
    if (!record) return NULL;

    // Rimuove il record dalla tabella hash e libera la memoria
    Auto a = record->autoPtr;
    HASH_DEL(*ht, record);
    free(record->targa);
    free(record);
    return a;
}

/*
* Funzione per distruggere la tabella hash delle auto.
* * Parametri:
* - `ht`: puntatore alla tabella hash da distruggere.
* * Side Effects:
* Libera la memoria allocata per la tabella hash e per ogni auto.
 */
void distruggiAutoHashTB(AutoHashTB *ht) {
    // Controlla se la tabella hash è NULL
    if (!ht) return;

    // Itera su tutti i record nella tabella hash e libera la memoria
    AutoRecord *curr, *tmp;
    HASH_ITER(hh, *ht, curr, tmp) {
        HASH_DEL(*ht, curr);
        distruggiAuto(curr->autoPtr);
        free(curr->targa);
        free(curr);
    }

    *ht = NULL;
}

/*
* Funzione per stampare tutte le auto nella tabella hash.
* * Parametri:
* - `ht`: la tabella hash da cui stampare le auto.
* * Side Effects:
 */
void stampaAutoHashTB(AutoHashTB ht) {
    AutoRecord *record;
	if (!ht) {
        printf(ROSSO "Non sono presenti auto da stampare.\n" RESET);
        return;
    }
    printf("\n" CIANO "Auto presenti nel CarSharing:\n" RESET);
    for (record = ht; record != NULL; record = record->hh.next) {
        printf(BIANCO "------------------------\n" RESET);
        stampaAuto(record->autoPtr);
        printf(BIANCO "------------------------\n" RESET);
    }
}

/*
* Funzione per stampare le auto disponibili in un intervallo di giorni e ore.
* * Parametri:
* - `ht`: la tabella hash da cui stampare le auto.
* - `giornoInizio`: il giorno di inizio dell'intervallo.
* - `giornoFine`: il giorno di fine dell'intervallo.
* - `oraInizio`: l'ora di inizio dell'intervallo.
* - `oraFine`: l'ora di fine dell'intervallo.
* * Side Effects:
* Stampa le informazioni delle auto disponibili nella fascia oraria specificata.
 */
void stampaTabellaDiHashPerDisp(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    int almenoUna = 0;

    printf("\n" CIANO "Auto disponibili nella fascia selezionata:\n" RESET);

    AutoRecord *record;
    for (record = ht; record != NULL; record = record->hh.next) {
        Auto a = record->autoPtr;
        if (verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
            printf(BIANCO "------------------------\n" RESET);
            stampaAuto(a);
            printf(BIANCO "------------------------\n" RESET);
            almenoUna = 1;
        }
    }

    // Se non è stata trovata nessuna auto disponibile, stampa un messaggio
    if (!almenoUna) {
        printf(ROSSO "Nessuna auto disponibile per questa fascia.\n" RESET);
    }
}

/*
* Funzione per reimpostare la disponibilità di tutte le auto nella tabella hash.
* * Parametri:
* - `ht`: la tabella hash delle auto.
* * Side Effects:
* Reimposta la disponibilità di tutte le auto, impostando tutti i giorni e le ore come non disponibili (false).
 */
void reimpostaDisponibilitaTutteLeAuto(AutoHashTB ht) {
    AutoRecord *record;

    // Controlla se la tabella hash è NULL
    for (record = ht; record != NULL; record = record->hh.next) {
        reimpostaDisponibileAuto(record->autoPtr);
    }

    printf(CIANO "Tutte le disponibilita' sono state reinizializzate.\n" RESET);
}

/* Funzione per stampare le auto disponibili in un intervallo di giorni e ore su un file.
 * Parametri:
 * - `ht`: la tabella hash da cui stampare le auto.
 * - `giornoInizio`: il giorno di inizio dell'intervallo.
 * - `giornoFine`: il giorno di fine dell'intervallo.
 * - `oraInizio`: l'ora di inizio dell'intervallo.
 * - `oraFine`: l'ora di fine dell'intervallo.
 * - `fp`: il file su cui scrivere le informazioni delle auto disponibili.
 * La funzione itera su tutti i record nella tabella hash, verifica la disponibilità di ogni auto
    * nell'intervallo specificato e scrive le informazioni delle auto disponibili nel file.
    */
void stampaTabellaDiHashPerDispFile(AutoHashTB ht, int giornoInizio, int giornoFine, int oraInizio, int oraFine, FILE *fp) {
    int almenoUna = 0;

    fprintf(fp, "Auto disponibili nella fascia selezionata:\n");

    AutoRecord *record;
    // Controlla se la tabella hash è NULL
    for (record = ht; record != NULL; record = record->hh.next) {
        Auto a = record->autoPtr;
        // Verifica la disponibilità dell'auto nell'intervallo specificato
         // Se l'auto è disponibile, stampa le informazioni nel file
        if (verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)) {
            fprintf(fp, "------------------------\n");
            // Stampa dettagli auto direttamente
            fprintf(fp, "Targa: %s\n", ottieniTarga(a));
            fprintf(fp, "Marca: %s\n", ottieniMarca(a));
            fprintf(fp, "Modello: %s\n", ottieniModello(a));
            fprintf(fp, "Indirizzo: %s\n", ottieniPosizione(a));
            fprintf(fp, "Anno: %d\n", ottieniAnno(a));
            fprintf(fp, "Costo orario: %.2f €\n", ottieniPrezzo(a));
            fprintf(fp, "------------------------\n");
            almenoUna = 1;
        }
    }

    if (!almenoUna) {
        fprintf(fp, "Nessuna auto disponibile per questa fascia/Fascia gioranliera-oraria errata.\n");
    }
}
