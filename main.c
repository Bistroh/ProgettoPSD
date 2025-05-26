#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utente.h"
#include "Utile_UtenteMenu.h"
#include "Utile_DevMenu.h"
#include "HashTbUtenti.h"
#include "HashTbAuto.h"
#include "List_Prenotazione.h"
#include "Controlli.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define CIANO    "\x1b[36m"
#define ROSSO     "\x1b[31m"



int main() {
    // Con UTHash inizializziamo a NULL
    UtentiHashTB tabUtenti = nuovaHashTBUtenti();
    AutoHashTB tabAuto = creaAutoHashTB();
    Lista listaPrenotazioni = nuovaLista();
    int sceltaMenu = 0;
    int scelta = 0;

    do{
        scelta = selezionaRuolo(); // 1 per utente, 2 per sviluppatore

        Utente u = NULL;

        if (scelta == 1) {
            u = loginRegistrazioneUtente(&tabUtenti);
            pulisciConsole();
            if (u != NULL) {
                do {
                    sceltaMenu = menuUtente();
                    listaPrenotazioni = switchUtente(sceltaMenu, u, listaPrenotazioni, tabAuto);
                    pausaConsole();
                    pulisciConsole();
                } while (sceltaMenu != 6);
            }
            else {
                printf(ROSSO "Login o registrazione fallita.\n" RESET);
            }
        } else if (scelta == 2) {
          do {
                sceltaMenu = mostraMenuSviluppatore();
                listaPrenotazioni = gestisciMenuSviluppatore(sceltaMenu, &tabAuto, listaPrenotazioni, tabUtenti);
                pausaConsole();
                pulisciConsole();
            } while (sceltaMenu != 7);
        }
    } while (scelta != 0);

    printf(CIANO "*------------------------------------------------------*\n");
    printf("|Grazie per aver usufruito del servizio di Car Sharing.|\n");
    printf("*------------------------------------------------------*\n" RESET);

    // Alla fine distruggiamo la tabella
    distruggiHashTBUtenti(&tabUtenti);
    distruggiAutoHashTB(&tabAuto);
    distruggiLista(listaPrenotazioni);
    return 0;
}
