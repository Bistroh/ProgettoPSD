#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_Prenotazione.h"
#include "prenotazione.h"
#include "Utile_UtenteMenu.h"
#include "Auto.h"
#include "Utente.h"

void switchUtente(int scelta){
  // Funzione per gestire le scelte dell'utente
  switch(scelta){
    case 1:
      printf("Prenotazione auto...\n");
      break;
    case 2:
      printf("Calcolo tariffa per auto prenotata...\n");
      break;
    case 3:
      printf("Visualizzazione auto disponibili...\n");
      break;
    case 4:
      printf("Visualizzazione prenotazioni...\n");
      break;
    case 5:
      printf("Visualizzazione prenotazioni precedenti...\n");
      break;
    case 6:
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
  printf("2. Calcolo tariffa per auto prenotata");
  printf("3. Visualizza auto disponibili\n");
  printf("4. Visualizza prenotazioni\n");
  printf("5. Visualizza prenotazioni precedenti\n");
  printf("6. Esci\n");
  printf("==================================\n");
  scanf("%d", &scelta);
  return scelta;
}

void prenotazioneAuto(list l, Utente u) {
    // Funzione per prenotare un'auto
    char CF[17], targa[10];
    int giornoInizio, giornoFine, oraInizio, oraFine;

    strcpy(CF, getCF(u));
    printf("Inserisci la targa dell'auto: ");
    scanf("%s", targa);

    printf("Quale giorno di inizio/fine della settimana vuoi prenotare l'auto: ");
    scanf("%d %d", &giornoInizio, &giornoFine);
    printf("Inserisci l'ora di inizio e fine: ");
    scanf("%d %d", &oraInizio, &oraFine);

    Prenotazione nuovaPrenotazione = creaPrenotazione(CF, targa, giornoInizio, giornoFine, oraInizio, oraFine);
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


