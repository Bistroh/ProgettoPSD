#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

typedef struct s_prenotazione* Prenotazione;
#include <stdio.h>


Prenotazione creaPrenotazione(char *CF, char *targa, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/**
 * Restituisce l’ID della prenotazione
 */
int ottieniIDPrenotazione(Prenotazione prenotazione);

/**
 * Restituisce il codice fiscale associato alla prenotazione
 */
char *ottieniCFPrenotazione(Prenotazione prenotazione);

/**
 * Restituisce la targa del veicolo prenotato
 */
char *ottieniTargaPrenotazione(Prenotazione prenotazione);

void stampaPrenotazione(Prenotazione prenotazione);
/**
 * Restituisce il periodo della prenotazione (giorni e ore)
 */
void ottieniPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine);

/**
 * Stampa i dettagli della prenotazione
 */
void stampaPrenotazione(Prenotazione prenotazione);

void stampaPrenotazioneSuFile(Prenotazione prenotazione, FILE *fp);

Prenotazione copiaPrenotazione(Prenotazione originale);

void distruggiPrenotazione(Prenotazione p);

#endif // PRENOTAZIONE_H
