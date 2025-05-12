//
// Created by extra on 06/05/2025.
//

#ifndef UTILE_UTENTEMENU_H
#define UTILE_UTENTEMENU_H
#include "utente.h"
#include "list_prenotazione.h"
int codiceFiscaleValido(const char *CF);
void prenotazioneAuto(list l, Utente u);
void visualizzaAutoDisponibili();
void visualizzaPrenotazioni(list l);
void visualizzaStorico();
void switchUtente(int scelta);
int menuUtente();

#endif //UTILE_UTENTEMENU_H
