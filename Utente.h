#ifndef UTENTE_H
#define UTENTE_H
#include "Coda_StoricoUtente.h"


typedef struct s_utente *Utente;

/*
 * Funzione: creaUtente
 * -----------------------------
 * Crea un nuovo utente con i dati specificati.
 * -----------------------------
 * Parametri:
 * - `CF`: codice fiscale dell'utente.
 * - `nome`: nome dell'utente.
 * - `cognome`: cognome dell'utente.
 * - `email`: email dell'utente.
 * - `password`: password dell'utente.
 * - `telefono`: numero di telefono dell'utente.
 * -------------------------------
 * Precondizioni:
 * - `CF`, `nome`, `cognome`, `email`, `password`, `telefono` devono essere stringhe non vuote.
 * -------------------------------
 * Postcondizioni:
 *    'u' è un puntatore a una struttura (Utente) inizializzata con i valori forniti in input.
 * ---------------------------------
 * Side Effects:
 * la variabile struttura u viene allocata dinamicamente in memoria.
 *
 */
Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password,char *telefono);

/*
 * Funzione: ottieniCF
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta il codice fiscale dell'utente.
 * -----------------------------
 */
char *ottieniCF(Utente utente);

/*
 * Funzione: ottieniNome
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta il nome dell'utente.
 * -----------------------------
 */
char *ottieniNome(Utente utente);

/*
 * Funzione: ottieniCognome
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta il cognome dell'utente.
 * -----------------------------
 */
char *ottieniCognome(Utente utente);

/*
 * Funzione: ottieniEmail
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta l'email dell'utente.
 * -----------------------------
 */
char *ottieniEmail(Utente utente);

/*
 * Funzione: ottieniTelefono
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta il numero di telefono dell'utente.
 * -----------------------------
 */
char *ottieniTelefono(Utente utente);

/*
 * Funzione: ottieniPassword
 * -----------------------------
 * Parametri:
 * - `utente`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `utente` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore alla stringa che rappresenta la password dell'utente.
 * -----------------------------
 */
char *ottieniPassword(Utente utente);

/*
 * Funzione: stampaUtente
 * -----------------------------
 * Parametri:
 * - `u`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `u` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Side Effects:
 * Stampa i dettagli di un utente.
 * -----------------------------
 */
void stampaUtente(Utente u);

/*
 * Funzione: ottieniStorico
 * -----------------------------
 * Ottiene lo storico delle prenotazioni di un utente.
 * -----------------------------
 * Parametri:
 * - `u`: puntatore alla struttura `Utente`.
 * -----------------------------
 * Precondizioni:
 * - `u` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Postcondizioni:
 * - Restituisce un puntatore a una coda che rappresenta lo storico delle prenotazioni dell'utente.
 * -----------------------------
 */
Coda ottieniStorico(Utente u);

/*
 * Funzione: distruggiUtente
 * -----------------------------
 * Distrugge un utente e libera la memoria allocata.
 * -----------------------------
 * Parametri:
 * - `u`: puntatore alla struttura `Utente` da distruggere.
 * -----------------------------
 * Precondizioni:
 * - `u` deve essere un puntatore valido a una struttura `Utente` creata con `creaUtente`.
 * -----------------------------
 * Side Effects:
 * - Libera la memoria allocata per l'utente.
 * -----------------------------
 */
void distruggiUtente(Utente u);

#endif //UTENTE_H


