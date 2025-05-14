#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utente.h"
#include "Utile_UtenteMenu.h"
#include "Utile_DevMenu.h"
#include "HashTbUtenti.h"
#include "HashTbAuto.h"



int main() {
    int scelta = selezionaRuolo(); // 1 per utente, 2 per sviluppatore

    // Con UTHash inizializziamo a NULL
    HashTable tabUtenti = newHashtableUtenti();
    AutoHashTable tabAuto = creaHashTableAuto();

    Utente u;

    if (scelta == 1) {
        u = loginRegisterUtente(&tabUtenti);
        if (u != NULL) {
            do {
                scelta = menuUtente();
                switchUtente(scelta);
                system("pause");
                system("cls");
            } while (scelta != 6);
        }
    } else if (scelta == 2) {
      do {
            scelta = mostraMenuDeveloper();
            gestisciMenuDeveloper(scelta, &tabAuto);
            system("pause");
            system("cls");
        } while (scelta != 5);
    }

    // Alla fine distruggiamo la tabella
    distruggiHashTableUtenti(&tabUtenti);
    distruggiHashTableAuto(&tabAuto);
    return 0;
}
