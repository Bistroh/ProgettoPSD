#ifndef HASHTBUTENTI_H
#define HASHTBUTENTI_H

#include "Utente.h"
#include "Coda_StoricoUtente.h"
#include "List_Prenotazione.h"

// Struttura opaca per la tabella hash
typedef struct HashRecord HashRecord;
typedef HashRecord* UtentiHashTB;

/*
* Funzione: nuovaHashTBUtenti
* -----------------------------
* Parametri:
* - Nessuno.
* -----------------------------
* Precondizioni:
* - Nessuna.
* -----------------------------
* Postcondizioni:
* - Restituisce un nuovo puntatore a una tabella hash degli utenti, inizialmente vuota (NULL).
* -----------------------------
 */
UtentiHashTB nuovaHashTBUtenti();

/*
 * Funzione: inserisciUtente
 * -----------------------------
 * Parametri:
 * - `h`: puntatore alla tabella hash degli utenti.
 * - `u`: l'utente da inserire.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * - `u` deve essere un puntatore valido a una struttura Utente.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce 1 se l'inserimento è avvenuto con successo, 0 se il codice fiscale era già presente.
* -----------------------------
* Side Effects:
* Modifica la tabella hash degli utenti aggiungendo un nuovo record.
* -----------------------------
 */
int inserisciUtente(UtentiHashTB *h, Utente u);

/*
 * Funzione: loginRegistrazioneUtente
 * -----------------------------
 * Parametri:
 * - `h`: puntatore alla tabella hash degli utenti.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * -----------------------------
 * Postcondizioni:
 * - Gestisce il login o la registrazione di un utente.
 * - Restituisce un puntatore all'utente registrato o loggato, o NULL in caso di errore.
 * -----------------------------
 */
Utente loginRegistrazioneUtente(UtentiHashTB *h);

/*
 * Funzione: cercaUtente
 * -----------------------------
 * Parametri:
 * - `h`: la tabella hash degli utenti.
 * - `CF`: il codice fiscale dell'utente da cercare.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * - `CF` deve essere una stringa valida (non NULL).
 * -----------------------------
 * Postcondizioni:
 * - Restituisce il puntatore all'utente se trovato, altrimenti NULL.
 * -----------------------------
* Side Effects:
* Nessuno.
* -----------------------------
 */
Utente cercaUtente(UtentiHashTB h, const char *CF);

/*
 * Funzione: eliminaUtente
 * -----------------------------
 * Parametri:
 * - `h`: puntatore alla tabella hash degli utenti.
 * - `CF`: il codice fiscale dell'utente da eliminare.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * - `CF` deve essere una stringa valida (non NULL).
 * -----------------------------
 * Postcondizioni:
 * - Elimina l'utente dalla tabella hash e restituisce l'utente eliminato, o NULL se non trovato.
 * -----------------------------
 */
Utente eliminaUtente(UtentiHashTB *h, const char *CF);

/*
 * Funzione: distruggiHashTBUtenti
 * -----------------------------
 * Parametri:
 * - `h`: puntatore alla tabella hash degli utenti da distruggere.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * -----------------------------
 * Postcondizioni:
 * - Dealloca la memoria utilizzata dalla tabella hash e dai suoi record.
 * -----------------------------
 */
void distruggiHashTBUtenti(UtentiHashTB *h);

/*
 * Funzione: stampaUtentiHashTBUtenti
 * -----------------------------
 * Parametri:
 * - `h`: la tabella hash degli utenti da stampare.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * -----------------------------
 * Postcondizioni:
 * - Stampa le informazioni di tutti gli utenti nella tabella hash.
 * -----------------------------
 */
void stampaUtentiHashTBUtenti(UtentiHashTB h);

/*
 * Funzione: aggiungiPrenotazioniAStoricoUtenti
 * -----------------------------
 * Parametri:
 * - `h`: la tabella hash degli utenti.
 * - `listaPrenotazioni`: la lista delle prenotazioni da aggiungere allo storico degli utenti.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * - `listaPrenotazioni` deve essere una lista valida di prenotazioni.
 * -----------------------------
 * Postcondizioni:
 * - Aggiunge le prenotazioni alla coda di storico di ciascun utente corrispondente.
 * -----------------------------
 */
void aggiungiPrenotazioniAStoricoUtenti(UtentiHashTB h, Lista listaPrenotazioni);

/*
 * Funzione: stampaStoricoTuttiUtenti
 * -----------------------------
 * Parametri:
 * - `h`: la tabella hash degli utenti.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * -----------------------------
 * Postcondizioni:
 * - Stampa lo storico di tutte le prenotazioni per ogni utente nella tabella hash.
 * -----------------------------
 */
void stampaStoricoTuttiUtenti(UtentiHashTB h);

/*
 * Funzione: stampaStoricoTuttiUtentiSuFile
 * -----------------------------
 * Parametri:
 * - `h`: la tabella hash degli utenti.
 * - `output_fp`: il file su cui scrivere lo storico.
 * -----------------------------
 * Precondizioni:
 * - `h` deve essere un puntatore valido a una tabella hash degli utenti.
 * - `output_fp` deve essere un file aperto in modalità scrittura.
 * -----------------------------
 * Postcondizioni:
 * - Scrive lo storico di tutte le prenotazioni per ogni utente nel file specificato.
 * -----------------------------
 */
void stampaStoricoTuttiUtentiSuFile(UtentiHashTB h, FILE *output_fp);

#endif // HASHTBUTENTI_H
