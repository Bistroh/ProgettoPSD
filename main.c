#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utente.h"
#include "Utile_UtenteMenu.h"
#include "Utile_DevMenu.h"
#include "HashTbUtenti.h"
#include "HashTbAuto.h"
#include "List_Prenotazione.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define CYAN    "\x1b[36m"



int main() {
    // Con UTHash inizializziamo a NULL
    HashTable tabUtenti = newHashtableUtenti();
    AutoHashTable tabAuto = creaHashTableAuto();
    List listaPrenotazioni = newList();
    int sceltaMenu = 0;
    int scelta = 0;

    do{
        scelta = selezionaRuolo(); // 1 per utente, 2 per sviluppatore

        Utente u = NULL;

        if (scelta == 1) {
            u = loginRegisterUtente(&tabUtenti);
            if (u != NULL) {
                do {
                    sceltaMenu = menuUtente();
                    listaPrenotazioni = switchUtente(sceltaMenu, u, listaPrenotazioni, tabAuto);
                    system("pause");
                    system("cls");
                } while (sceltaMenu != 6);
            }
        } else if (scelta == 2) {
          do {
                sceltaMenu = mostraMenuDeveloper();
                gestisciMenuDeveloper(sceltaMenu, &tabAuto, listaPrenotazioni);
                system("pause");
                system("cls");
            } while (sceltaMenu != 5);
        }
    } while (scelta != 0);

    printf(CYAN "*------------------------------------------------------*\n");
    printf("|Grazie per aver usufruito del servizio di Car Sharing.|\n");
    printf("*------------------------------------------------------*\n" RESET);

    // Alla fine distruggiamo la tabella
    distruggiHashTableUtenti(&tabUtenti);
    distruggiHashTableAuto(&tabAuto);
    distruggiLista(listaPrenotazioni);
    return 0;
}
