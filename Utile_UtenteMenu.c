#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_Prenotazione.h"
#include "HashTbAuto.h"
#include "prenotazione.h"
#include "Utile_UtenteMenu.h"
#include "Auto.h"
#include "Utente.h"

List switchUtente(int scelta, Utente u, List l, AutoHashTable tabAuto){
  // Funzione per gestire le scelte dell'utente
  switch(scelta){
    case 1:
      printf("Prenotazione auto...\n");
      l = prenotazioneAuto(l, u, tabAuto);
      break;
    case 2:
      printf("Calcolo tariffa per auto prenotata...\n");
      break;
    case 3:
      printf("Visualizzazione auto disponibili...\n");
      visualizzaAutoDisponibili(tabAuto);
      break;
    case 4:
      printf("Visualizzazione prenotazioni...\n");
      visPrenotazioniPerUtente(l, getCF(u));
      break;
    case 5:
      printf("Visualizzazione prenotazioni precedenti...\n");
      break;
    case 6:
      printf("Uscita...\n");
      break;
    default:
      printf("Opzione non valida. Riprova.\n");
      break;
  }
  return l;
}

int menuUtente(){
  // Funzione per visualizzare il menu principale e restituire l'opzione scelta
  int scelta;
  printf("\n========== Car Sharing ==========\n");
  printf("1. Prenotazione Auto\n");
  printf("2. Calcolo tariffa per auto prenotata\n");
  printf("3. Visualizza auto disponibili\n");
  printf("4. Visualizza prenotazioni\n");
  printf("5. Visualizza prenotazioni precedenti\n");
  printf("6. Esci\n");
  printf("==================================\n");
  scanf("%d", &scelta);
  return scelta;
}

List prenotazioneAuto(List l, Utente u, AutoHashTable tabAuto) {
    // Funzione per prenotare un'auto
    char CF[17], targa[10];
    Auto a;
    int giornoInizio, giornoFine, oraInizio, oraFine;

    strcpy(CF, getCF(u));

    do {
      printf("Inserisci la targa dell'auto: ");
      scanf("%s", targa);
      a = cercaAuto(tabAuto, targa);
      if (a == NULL) {
        printf("Targa non trovata. Riprova.\n");
      }
    } while (a == NULL);

    do {
      printf("Inserisci il giorno di inizio della prenotazione (1=lun, ..., 7=dom): ");
      scanf("%d", &giornoInizio);
      if (giornoInizio < 1 || giornoInizio > 7) {
        printf("Errore: il giorno deve essere un numero da 1 a 7.\n");
      }
    } while (giornoInizio < 1 || giornoInizio > 7);

    do {
      printf("Inserisci il giorno di fine della prenotazione (>= giorno inizio, max 7): ");
      scanf("%d", &giornoFine);
      if (giornoFine < giornoInizio || giornoFine > 7) {
        printf("Errore: il giorno di fine deve essere compreso tra %d e 7.\n", giornoInizio);
      }
    } while (giornoFine < giornoInizio || giornoFine > 7);


    do {
      printf("Inserisci l'ora di inizio (1-24): ");
      scanf("%d", &oraInizio);
      if (oraInizio < 1 || oraInizio > 24) {
        printf("Errore: l'ora di inizio deve essere compresa tra 1 e 24 (1 = 01:00, 24 = mezzanotte).\n");
      }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
      printf("Inserisci l'ora di fine (>= ora inizio, max 24): ");
      scanf("%d", &oraFine);
      if (oraFine < oraInizio || oraFine > 24) {
        printf("Errore: l'ora di fine deve essere compresa tra %d e 24.\n", oraInizio);
      }
    } while (oraFine < oraInizio || oraFine > 24);

    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    if(verificaDisponibilita(a, giornoInizio, giornoFine, oraInizio, oraFine)){
      setDisponibile(a, giornoInizio, giornoFine, oraInizio, oraFine, true);
    }
    else{ exit(1); }

    Prenotazione nuovaPrenotazione = creaPrenotazione(CF, targa, giornoInizio, giornoFine, oraInizio, oraFine);

    l = consList(nuovaPrenotazione, l);
    return l;
}

void visualizzaAutoDisponibili(AutoHashTable ht) {
    if (!ht) {
        printf("Nessuna auto registrata.\n");
        return;
    }

    int giornoInizio, giornoFine, oraInizio, oraFine;

    // Input con validazioni
    do {
        printf("Inserisci il giorno di inizio della fascia (1=lun, ..., 7=dom): ");
        scanf("%d", &giornoInizio);
        if (giornoInizio < 1 || giornoInizio > 7) {
            printf("Errore: giorno valido è tra 1 e 7.\n");
        }
    } while (giornoInizio < 1 || giornoInizio > 7);

    do {
        printf("Inserisci il giorno di fine della fascia (>= inizio, max 7): ");
        scanf("%d", &giornoFine);
        if (giornoFine < giornoInizio || giornoFine > 7) {
            printf("Errore: giorno di fine deve essere tra %d e 7.\n", giornoInizio);
        }
    } while (giornoFine < giornoInizio || giornoFine > 7);

    do {
        printf("Inserisci l'ora di inizio (1-24): ");
        scanf("%d", &oraInizio);
        if (oraInizio < 1 || oraInizio > 24) {
            printf("Errore: ora di inizio deve essere tra 1 e 24.\n");
        }
    } while (oraInizio < 1 || oraInizio > 24);

    do {
        printf("Inserisci l'ora di fine (>= inizio, max 24): ");
        scanf("%d", &oraFine);
        if (oraFine < oraInizio || oraFine > 24) {
            printf("Errore: ora di fine deve essere tra %d e 24.\n", oraInizio);
        }
    } while (oraFine < oraInizio || oraFine > 24);

    giornoInizio--; giornoFine--;
    oraInizio--; oraFine--;

    stampaHashTablePerDisp(ht, giornoInizio, giornoFine, oraInizio, oraFine);
}

void visualizzaStorico() {
    // Funzione per visualizzare le prenotazioni precedenti
    printf("Visualizzazione prenotazioni precedenti...\n");
    // Implementa la logica per visualizzare le prenotazioni precedenti
}


