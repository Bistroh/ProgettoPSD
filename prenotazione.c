#include "prenotazione.h"
#include "Auto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define BLU    "\x1b[34m"
#define GIALLO  "\x1b[33m"
#define CIANO    "\x1b[36m"

/*
    * La struttura `Periodo` rappresenta un periodo di prenotazione
* con i seguenti campi:
* - `giornoInizio`: il giorno di inizio del periodo (0 = Lunedì, 6 = Domenica).
* - `giornoFine`: il giorno di fine del periodo (0 = Lunedì, 6 = Domenica).
* - `oraInizio`: l'ora di inizio del periodo (0-23).
* - `oraFine`: l'ora di fine del periodo (1-24, dove 24 indica la mezzanotte del giorno successivo).
 */
typedef struct {
    int giornoInizio;
    int giornoFine;
    int oraInizio;
    int oraFine;
} Periodo;

/*
    * La struttura `s_prenotazione` rappresenta una prenotazione con i seguenti campi:
* - `ID_prenotazione`: un identificatore univoco per la prenotazione.
* - `CF`: il codice fiscale del cliente associato alla prenotazione.
* - `targa`: la targa del veicolo prenotato.
* - `periodo`: un oggetto di tipo `Periodo` che rappresenta il periodo di prenotazione.
 */
struct s_prenotazione {
    int ID_prenotazione;
    char CF[17];
    char targa[10];
    Periodo periodo;
};

/*
    * Funzione per creare una nuova prenotazione.
* * La funzione assegna un ID univoco alla prenotazione, copia il codice fiscale e la targa,
* * e imposta il periodo di prenotazione.
* * Parametri:
* - `CF`: il codice fiscale del cliente.
* - `targa`: la targa del veicolo prenotato.
* - `giornoInizio`: il giorno di inizio del periodo di prenotazione.
* - `giornoFine`: il giorno di fine del periodo di prenotazione.
* - `oraInizio`: l'ora di inizio del periodo di prenotazione.
* - `oraFine`: l'ora di fine del periodo di prenotazione.
* * Restituisce un puntatore a una nuova struttura `s_prenotazione` allocata dinamicamente.
 */
Prenotazione creaPrenotazione(char *CF, char *targa, int giornoInizio, int giornoFine, int oraInizio, int oraFine) {
    static int id_contatore = 0;
    Prenotazione nuovaPrenotazione = malloc(sizeof(struct s_prenotazione));
    if (nuovaPrenotazione == NULL) {    // Controllo se l'allocazione della memoria è riuscita
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Controllo validità intervallo giorno/ora
    nuovaPrenotazione->ID_prenotazione = id_contatore++;
    strncpy(nuovaPrenotazione->CF, CF, sizeof(nuovaPrenotazione->CF) - 1);
    nuovaPrenotazione->CF[sizeof(nuovaPrenotazione->CF) - 1] = '\0';

    strncpy(nuovaPrenotazione->targa, targa, sizeof(nuovaPrenotazione->targa) - 1);
    nuovaPrenotazione->targa[sizeof(nuovaPrenotazione->targa) - 1] = '\0';

    nuovaPrenotazione->periodo.giornoInizio = giornoInizio;
    nuovaPrenotazione->periodo.giornoFine = giornoFine;
    nuovaPrenotazione->periodo.oraInizio = oraInizio;
    nuovaPrenotazione->periodo.oraFine = oraFine;

    return nuovaPrenotazione;
}

/*
    * Funzione per ottenere l'ID della prenotazione.
* * Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere l'ID.
* * * Restituisce l'ID della prenotazione.
 */
int ottieniIDPrenotazione(Prenotazione prenotazione) {
    return prenotazione->ID_prenotazione;
}

/*
    * Funzione per ottenere il codice fiscale associato alla prenotazione.
* * Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere il codice fiscale.
* * * Restituisce un puntatore alla stringa che rappresenta il codice fiscale della prenotazione.
 */
char *ottieniCFPrenotazione(Prenotazione prenotazione) {
    return prenotazione->CF;
}

/*
    * Funzione per ottenere la targa del veicolo prenotato.
* * Parametri:
* - `prenotazione`: puntatore alla prenotazione da cui ottenere la targa.
* * * Restituisce un puntatore alla stringa che rappresenta la targa del veicolo prenotato.
 */
char *ottieniTargaPrenotazione(Prenotazione prenotazione) {
    return prenotazione->targa;
}

/*
    * Funzione per ottenere il periodo di prenotazione.
* * Parametri:
* - `p`: puntatore alla prenotazione da cui ottenere il periodo.
* * * Restituisce i valori del periodo di prenotazione attraverso i puntatori `giornoInizio`,
 * `giornoFine`, `oraInizio` e `oraFine`.
 */
void ottieniPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine) {
    if (p) {
        *giornoInizio = p->periodo.giornoInizio;
        *giornoFine = p->periodo.giornoFine;
        *oraInizio = p->periodo.oraInizio;
        *oraFine = p->periodo.oraFine;
    }
}

/*
 * Funzione per convertire un giorno della settimana in una stringa.
 * Parametri:
 * - `giorno`: il giorno della settimana (0 = Lunedì, 6 = Domenica).
 * Restituisce una stringa che rappresenta il giorno della settimana.
 */
const char* giornoToString(int giorno) {
    switch (giorno) {
        case 0: return "Lunedi'";
        case 1: return "Martedi'";
        case 2: return "Mercoledi'";
        case 3: return "Giovedi'";
        case 4: return "Venerdi'";
        case 5: return "Sabato";
        case 6: return "Domenica";
        default: return "Giorno sconosciuto";
    }
}

/*
 * Funzione per stampare i dettagli di una prenotazione.
 * Parametri:
 * - `prenotazione`: puntatore alla prenotazione da stampare.
 * Stampa i dettagli della prenotazione, inclusi ID, codice fiscale, targa e periodo.
 */
void stampaPrenotazione(Prenotazione prenotazione) {
    printf(CIANO "ID Prenotazione: " RESET "%d\n", prenotazione->ID_prenotazione);
    printf(CIANO "CF: " RESET "%s\n", prenotazione->CF);
    printf(CIANO "Targa: " RESET "%s\n", prenotazione->targa);
    if ((prenotazione->periodo.giornoInizio == 5 || prenotazione->periodo.giornoInizio == 6 || prenotazione->periodo.giornoFine == 5   || prenotazione->periodo.giornoFine == 6)) {
        printf(CIANO "Periodo: da %s ore %d:00 a %s ore %d:00\n" RESET,
                 // Controllo se il periodo include il weekend
               giornoToString(prenotazione->periodo.giornoInizio),
               prenotazione->periodo.oraInizio,
               giornoToString(prenotazione->periodo.giornoFine),
               prenotazione->periodo.oraFine);
    }
    else {
        printf(CIANO "Periodo: dal %s ore %d:00 al %s ore %d:00\n" RESET,
                // Controllo se il periodo non include il weekend
               giornoToString(prenotazione->periodo.giornoInizio),
               prenotazione->periodo.oraInizio,
               giornoToString(prenotazione->periodo.giornoFine),
               prenotazione->periodo.oraFine);
    }
}

/*
    * Funzione per stampare i dettagli di una prenotazione su un file.
    * Parametri:
    * - `prenotazione`: puntatore alla prenotazione da stampare.
    * - `fp`: puntatore al file in cui scrivere i dettagli della prenotazione.
    * Stampa i dettagli della prenotazione, inclusi ID, codice fiscale, targa e periodo,
*  nel file specificato.
 */
void stampaPrenotazioneSuFile(Prenotazione prenotazione, FILE *fp) {
    fprintf(fp, "ID Prenotazione: %d\n", prenotazione->ID_prenotazione);
    fprintf(fp, "CF: %s\n", prenotazione->CF);
    fprintf(fp, "Targa: %s\n", prenotazione->targa);

    // Controllo se il periodo include il weekend
    if ((prenotazione->periodo.giornoInizio == 5 || prenotazione->periodo.giornoInizio == 6 ||
            prenotazione->periodo.giornoFine == 5   || prenotazione->periodo.giornoFine == 6)) {
        fprintf(fp, "Periodo: da %s ore %d:00 a %s ore %d:00\n",
                giornoToString(prenotazione->periodo.giornoInizio),
                prenotazione->periodo.oraInizio,
                giornoToString(prenotazione->periodo.giornoFine),
                prenotazione->periodo.oraFine);
        } else {
            fprintf(fp, "Periodo: dal %s ore %d:00 al %s ore %d:00\n",
                    giornoToString(prenotazione->periodo.giornoInizio),
                    prenotazione->periodo.oraInizio,
                    giornoToString(prenotazione->periodo.giornoFine),
                    prenotazione->periodo.oraFine);
        }
}


/*
 * Funzione per creare una copia di una prenotazione.
 * Parametri:
 * - `originale`: puntatore alla prenotazione da copiare.
 * Restituisce un puntatore a una nuova prenotazione che è una copia dell'originale.
 */
Prenotazione copiaPrenotazione(Prenotazione originale)
{
    if (originale == NULL) return NULL;

    Prenotazione copia = malloc(sizeof(struct s_prenotazione));
    // Controllo se l'allocazione della memoria è riuscita
    if (copia == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria nella copia.\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Copia dei dati
    copia->ID_prenotazione = originale->ID_prenotazione;
    strncpy(copia->CF, originale->CF, sizeof(copia->CF));
    copia->CF[sizeof(copia->CF) - 1] = '\0';

    // Copia della targa
    strncpy(copia->targa, originale->targa, sizeof(copia->targa));
    copia->targa[sizeof(copia->targa) - 1] = '\0';

    // Copia del periodo
    copia->periodo.giornoInizio = originale->periodo.giornoInizio;
    copia->periodo.giornoFine = originale->periodo.giornoFine;
    copia->periodo.oraInizio = originale->periodo.oraInizio;
    copia->periodo.oraFine = originale->periodo.oraFine;

    return copia;
}

/*
 * Funzione per distruggere una prenotazione e liberare la memoria allocata.
 * Parametri:
 * - `p`: puntatore alla prenotazione da distruggere.
 * Se `p` è NULL, non fa nulla.
 */
void distruggiPrenotazione(Prenotazione p)
{
    if (p != NULL) {
        free(p);
    }
}