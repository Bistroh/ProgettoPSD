
## Informazioni sul Progetto

Il sistema di Car Sharing gestisce il noleggio di auto da parte di vari clienti impone all'utente di fare un login per differenziarsi da un possibile Sviluppatore e accedere come cliente, subito dopo viene visualizzato un menù che permette di scegliere tra varie opzioni per creare, gestire e visualizzare: prenotazioni, auto e le tariffe. Nel caso in cui si accede come Sviluppatore viene visualizzato un menù diverso che permette di gestire la Listaa delle auto e delle prenotazioni, ha accesso allo storico dei vari utenti e può modificare i valori delle varie tariffe.

## Prodotto usando

- [JetBrains](https://www.jetbrains.com)

## Prerequisiti
### DA VEDERE

## Installazione
### DA VEDERE

## Documentazione
### Da aggiornare
Link di riferimento per la [Documentazione](https://example.com)

## Roadmap

- [X] Creare e codificare i vari source file con header file collegato
  - [X] Auto.c/h
  - [X] prenotazione.c/h
  - [X] Utente.c/h
  - [X] Uthash.h
    - [X] HashTbUtenti.c/h
    - [X] HashTbAuto.c/h
  - [X] List_Prenotazione.c/h
  - [X] Utile_Utente_Menu.c/h
  - [X] Utile_DevMenu.c/h
  - [X] Coda_StoricoUtente.c/h //parzialmente finito
  - [X] Calcolo_Tariffa (incluso in Utile_UtenteMenù)
  - [X] Controlli.c/h
        
- [X] Funzioni menù utente
  - [X] Prenotazione
  - [X] Calcolo tariffa
  - [X] Visualizza auto disponibili
  - [X] Visualizza prenotazioni attuali
  - [X] Visualizza storico
     
- [X] Funzioni menù Sviluppatore
  - [X] Aggiungi auto
  - [X] Rimuovi auto
  - [X] Visualizza tutte le auto
  - [X] Visualizza tutte le prenotazioni
  - [X] Visualizza storico utente
  - [X] Avanza settimana (gestione storico)
        
        
- [X] Scelta dei vari ADT
- [X] Implementazione ADTs
  - [X] Lista prenotazione 
  - [X] Coda storico
  - [X] Hash table utenti
  - [X] Hash table auto
        
- [X] Main
- [X] Makefile
      
- [ ] Commenti  //scommenti sparsi da sistemare
  - [ ] Auto
  - [ ] prenotazione
  - [ ] Hash_Tb_Utenti
  - [ ] List_Prenotazione
  - [ ] Utile_Utente_Menu
  - [ ] Coda_StoricoUtente
  - [ ] Controlli
     
- [ ] Ottimizzazioni
  - [X] Colore sui messaggi a schermo
  - [ ] Migliorare la leggibilità codice generale
  - [X] "Italianizzare" il programma 
     
- [ ] Calcolo costo totale del progetto //rivedere lezione su elearning
     
- [ ] Testing
  - [ ] Prenotazione e aggiornamento disponibilità
    - [ ] TEST FUNZIONALI
      - [ ] Prenotazione normale con utente e auto validi 
      - [ ] Prenotazione in uno slot orario libero 
    - [ ] INPUT NON VALIDI
      - [ ] Codice fiscale non esistente 
      - [ ] Auto non presente nella tabella di hash 
      - [ ] Prenotazione con orari invalidi 
      - [ ] Giorni o orari fuori range 
    - [ ] EDGE CASE
      - [ ] Prenotazione che inizia alle 23 e finisce alle 1 di notte 
      - [ ] Prenotazione su confine orario 
      - [ ] Prenotazione multiple per stessa auto, stesso utente, orari diversi per verifica aggiornamento corretto disponibilità
            
  - [ ] Calcolo costo del noleggio
    - [ ] TEST FUNZIONALI
      - [ ] Prenotazione senza sconti 
      - [ ] Prenotazione con sconto weekend 10% 
      - [ ] Prenotazione con sconto fascia oraria 15% 
      - [ ] Prenotazione con sconto oreTotali maggiore di 10 20%
      - [ ] Verifica che venga letto correttamente il costo
    - [ ] INPUT NON VALIDI
      - [ ] Tariffa negativa 
    - [ ] EDGE CASE
      - [ ] Prenotazione molto lunga
      - [ ] Costo con cifre decimali ripetute
            
  - [ ] Visualizzazione veicoli disponibili
    - [ ] TEST FUNZIONALI
      - [ ] Visualizzzazione con range temporale valido e auto disponibile
      - [ ] Visualizzazione con auto non disponibile nel range     
    - [ ] INPUT NON VALIDI
      - [ ] Orari fuori dal range
      - [ ] Giorni negativi
      - [ ] OraInizio > OraFine
    - [ ] EDGE CASE
      - [ ] Range esatto sovrapposto a una prenotazione
      - [ ] Range incluso dentro una prenotazione
      - [ ] Range completamente fuori da tutte le prenotazioni
            
  - [ ] Gestione storico prenotazioni
    - [ ] TEST FUNZIONALI
      - [ ] Prenotazione -> aggiunta allo storico -> stampa corretta
      - [ ] Storico con più prenotazioni per lo stesso utente
    - [ ] INPUT NON VALIDI
      - [ ] Utente inesistente (nessuno storico)
      - [ ] Storico vuoto
    - [ ] EDGE CASE
      - [ ] Storico con molte prenotazioni
      - [ ] Prenotazioni con dati uguali (verifica che non ci siano state duplicazioni)
     
      
### DA FARE


## Contatti

email: 
- p.senatore32@studenti.unisa.it
- g.sarlo2@studenti.unisa.it
- l.sorrentino80@studenti.unisa.it

Link del progetto: [https://github.com/Bistroh/ProgettoPSD]

## Riconoscimenti

Questo readme è stato prodotto usando le risorse elencate sotto 
- [makeread.me](https://github.com/ShaanCoding/ReadME-Generator)
- [othneildrew](https://github.com/othneildrew/Best-README-Template)
- [uthash.h](https://troydhanson.github.io/uthash/)
