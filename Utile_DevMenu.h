#ifndef UTILE_DEVMENU_H
#define UTILE_DEVMENU_H
#include "HashTbAuto.h"
#include "List_Prenotazione.h"
#include "HashTbUtenti.h"

/*
    * Funzione: gestisciMenuSviluppatore
* --------------------------------
* Parametri:
* - `scelta`: l'opzione scelta dallo sviluppatore.
* - `ht`: puntatore alla tabella hash delle auto.
* * - `l`: lista delle prenotazioni.
* * - `tabUtenti`: tabella hash degli utenti.
* ---------------------------------
* Precondizioni:
* - `scelta` deve essere un intero compreso tra 1 e 7.
* * - `ht` deve essere un puntatore valido a una tabella hash delle auto.
* * - `l` deve essere una lista valida delle prenotazioni.
* * - `tabUtenti` deve essere una tabella hash valida degli utenti.
* ---------------------------------
* * Postcondizioni:
* - Esegue l'azione corrispondente all'opzione scelta dallo sviluppatore.
* * Le opzioni includono l'aggiunta di un'auto, la rimozione di un'auto,
* * la visualizzazione delle auto, la visualizzazione delle prenotazioni,
* * la visualizzazione dello storico delle prenotazioni e l'avanzamento di una settimana.
* ---------------------------------
 */
Lista gestisciMenuSviluppatore(int scelta, AutoHashTB *ht, Lista l, UtentiHashTB tabUtenti);

/*
 * Funzione: mostraMenuSviluppatore
 * ---------------------------------
 * Parametri:
 * - Nessuno.
 * ---------------------------------
 * Precondizioni:
 * - Nessuna.
 * ---------------------------------
 * Postcondizioni:
 * - Mostra il menu dello sviluppatore e restituisce l'opzione scelta.
 * ---------------------------------
 * Restituisce:
 * - Un intero che rappresenta l'opzione scelta dallo sviluppatore.
 * ---------------------------------
 */
int mostraMenuSviluppatore();

/*
 * Funzione: selezionaRuolo
 * -----------------------------
 * Parametri:
 * - Nessuno.
 * -----------------------------
 * Precondizioni:
 * - Nessuna.
 * -----------------------------
 * Postcondizioni:
 * - Mostra un menu per la selezione del ruolo (Sviluppatore o Utente).
 * - Restituisce 1 se l'utente sceglie il ruolo di Sviluppatore, 2 se sceglie il ruolo di Utente.
 * -----------------------------
 * Restituisce:
 * - Un intero che rappresenta il ruolo selezionato.
 * -----------------------------
 */
int selezionaRuolo();

#endif //UTILE_DEVMENU_H
