//
// Created by extra on 06/05/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List_Prenotazione.h"
#include "prenotazione.h"
#include "Utile_UtenteMenu.h"
#include "Auto.h"
#include "Utente.h"

/*int codiceFiscaleValido(const char *CF) {
    if (strlen(CF) != 16) {
        return 0; // deve essere lungo esattamente 16 caratteri
    }

    for (int i = 0; i < 16; i++) {
        if (!isalnum(CF[i]) || !isupper(CF[i])) {
            return 0; // deve contenere solo caratteri alfanumerici maiuscoli
        }
    }

    return 1; // valido
}*/
void switchUtente(int scelta){
  // Funzione per gestire le scelte dell'utente
  switch(scelta){
    case 1:
      printf("Prenotazione auto...\n");
      break;
    case 2:
      printf("Visualizzazione auto disponibili...\n");
      break;
    case 3:
      printf("Visualizzazione prenotazioni...\n");
      break;
    case 4:
      printf("Visualizzazione prenotazioni precedenti...\n");
      break;
    case 5:
      printf("Uscita...\n");
      exit(0);
      break;
    default:
      printf("Opzione non valida. Riprova.\n");
      break;
  }
}

int menuUtente(){
  // Funzione per visualizzare il menu principale e restituire l'opzione scelta
  int scelta;
  printf("\n========== Car Sharing ==========\n");
  printf("1. Prenotazione Auto\n");
  printf("2. Visualizza auto disponibili\n");
  printf("3. Visualizza prenotazioni\n");
  printf("4. Visualizza prenotazioni precedenti\n");
  printf("5. Esci\n");
  printf("==================================\n");
  scanf("%d", &scelta);
  return scelta;
}

void prenotazioneAuto(list l, Utente u) {
    // Funzione per prenotare un'auto
    char CF[17], targa[10];
    int giorno, mese, anno, oraInizio, oraFine;

    strcpy(CF, getCF(u));
    printf("Inserisci la targa dell'auto: ");
    scanf("%s", targa);
    printf("Inserisci la data di prenotazione (giorno mese anno): ");
    scanf("%d %d %d", &giorno, &mese, &anno);
    printf("Inserisci l'ora di inizio e fine (oraInizio oraFine): ");
    scanf("%d %d", &oraInizio, &oraFine);

    Prenotazione nuovaPrenotazione = creaPrenotazione(1, CF, targa, giorno, mese, anno, oraInizio, oraFine);
    l = consList(nuovaPrenotazione, l);
}
void visualizzaAutoDisponibili() {
    // Funzione per visualizzare le auto disponibili
    printf("Visualizzazione auto disponibili...\n");
    // Implementa la logica per visualizzare le auto disponibili
}
void visualizzaPrenotazioni(list l) {
    // Funzione per visualizzare le prenotazioni
    printf("Visualizzazione prenotazioni...\n");
    while (!emptyList(l)) {
        Prenotazione p = getFirst(l);
        stampaPrenotazione(p);
        l = tailList(l);
    }
}
void visualizzaStorico() {
    // Funzione per visualizzare le prenotazioni precedenti
    printf("Visualizzazione prenotazioni precedenti...\n");
    // Implementa la logica per visualizzare le prenotazioni precedenti
}


