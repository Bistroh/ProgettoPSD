//
// Created by extra on 30/04/2025.
//

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

typedef struct s_prenotazione *Prenotazione;

Prenotazione creaPrenotazione(char *CF, char *targa, int giorno, int mese, int anno, int oraInizio, int oraFine);
int getIDPrenotazione(Prenotazione prenotazione);
char *getCFPrenotazione(Prenotazione prenotazione);
char *getTargaPrenotazione(Prenotazione prenotazione);
char *getDataPrenotazione(Prenotazione prenotazione);
void stampaPrenotazione(Prenotazione prenotazione);


#endif //PRENOTAZIONE_H
