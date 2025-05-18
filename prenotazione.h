#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

typedef struct s_prenotazione* Prenotazione;


Prenotazione creaPrenotazione(char *CF, char *targa, int giornoInizio, int giornoFine, int oraInizio, int oraFine);

/**
 * Restituisce l’ID della prenotazione
 */
int getIDPrenotazione(Prenotazione prenotazione);

/**
 * Restituisce il codice fiscale associato alla prenotazione
 */
char *getCFPrenotazione(Prenotazione prenotazione);

/**
 * Restituisce la targa del veicolo prenotato
 */
char *getTargaPrenotazione(Prenotazione prenotazione);

/**
 * Restituisce il periodo della prenotazione (giorni e ore)
 */
void getPeriodoPrenotazione(Prenotazione p, int *giornoInizio, int *giornoFine, int *oraInizio, int *oraFine);

/**
 * Stampa i dettagli della prenotazione
 */
void stampaPrenotazione(Prenotazione prenotazione);

Prenotazione copiaPrenotazione(Prenotazione originale);

void distruggiPrenotazione(Prenotazione p);

#endif // PRENOTAZIONE_H
