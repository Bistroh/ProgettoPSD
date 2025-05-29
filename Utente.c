#include "Utente.h"
#include "Coda_StoricoUtente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define BLU    "\x1b[34m"
#define CIANO    "\x1b[36m"

/* * La struttura `s_utente` contiene i seguenti campi:
 * - `CF`: codice fiscale dell'utente.
 * - `nome`: nome dell'utente.
 * - `cognome`: cognome dell'utente.
 * - `email`: email dell'utente.
 * - `telefono`: numero di telefono dell'utente.
 * - `password`: password dell'utente.
 * - `storico`: coda che contiene lo storico delle prenotazioni dell'utente.
* * La struttura `s_utente` è utilizzata per rappresentare un utente del sistema di noleggio auto.
 */
struct s_utente {
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char password[20];
    Coda storico;
};

/* * Funzione per creare un nuovo utente.
 * La funzione alloca memoria per un nuovo utente e inizializza i campi con i valori forniti.
 * Se l'allocazione della memoria fallisce, il programma termina con un errore.
 * Parametri:
 * - `CF`: codice fiscale dell'utente.
 * - `nome`: nome dell'utente.
 * - `cognome`: cognome dell'utente.
 * - `email`: email dell'utente.
 * - `password`: password dell'utente.
 * - `telefono`: numero di telefono dell'utente.
 * Restituisce un puntatore a una nuova struttura `s_utente` allocata dinamicamente.
 */
Utente creaUtente(char *CF, char *nome, char *cognome, char *email, char *password, char *telefono) {
    Utente nuovoUtente = malloc(sizeof(struct s_utente));
    if (nuovoUtente == NULL) {
        fprintf(stderr, ROSSO "Errore di allocazione memoria\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Copia i dati nelle rispettive variabili
    strncpy(nuovoUtente->CF, CF, sizeof(nuovoUtente->CF) - 1);
    nuovoUtente->CF[sizeof(nuovoUtente->CF) - 1] = '\0'; // Assicurati che la stringa sia terminata

    strncpy(nuovoUtente->nome, nome, sizeof(nuovoUtente->nome) - 1);
    nuovoUtente->nome[sizeof(nuovoUtente->nome) - 1] = '\0';

    strncpy(nuovoUtente->cognome, cognome, sizeof(nuovoUtente->cognome) - 1);
    nuovoUtente->cognome[sizeof(nuovoUtente->cognome) - 1] = '\0';

    strncpy(nuovoUtente->email, email, sizeof(nuovoUtente->email) - 1);
    nuovoUtente->email[sizeof(nuovoUtente->email) - 1] = '\0';

    strncpy(nuovoUtente->password, password, sizeof(nuovoUtente->password) - 1);
    nuovoUtente->password[sizeof(nuovoUtente->password) - 1] = '\0';

    strncpy(nuovoUtente->telefono, telefono, sizeof(nuovoUtente->telefono) - 1);
    nuovoUtente->telefono[sizeof(nuovoUtente->telefono) - 1] = '\0';

    nuovoUtente->storico = nuovaCoda();

    return nuovoUtente;
}

/*
* Funzione per ottenere il codice fiscale di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta il codice fiscale dell'utente.
 */
char *ottieniCF(Utente utente) {
    return utente->CF;
}

/*
* Funzione per ottenere il nome di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta il nome dell'utente.
 */
char *ottieniNome(Utente utente) {
    return utente->nome;
}

/*
* Funzione per ottenere il cognome di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta il cognome dell'utente.
 */
char *ottieniCognome(Utente utente) {
    return utente->cognome;
}

/*
* Funzione per ottenere l'email di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta l'email dell'utente.
 */
char *ottieniEmail(Utente utente) {
    return utente->email;
}

/*
* Funzione per ottenere il numero di telefono di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta il numero di telefono dell'utente.
 */
char *ottieniTelefono(Utente utente) {
    return utente->telefono;
}

/*
* Funzione per ottenere la password di un utente.
* Parametri:
* - `utente`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla stringa che rappresenta la password dell'utente.
 */
char *ottieniPassword(Utente utente) {
    return utente->password;
}

/*
* Funzione per ottenere lo storico delle prenotazioni di un utente.
* Parametri:
* - `u`: puntatore alla struttura `Utente`.
* * Restituisce un puntatore alla coda che rappresenta lo storico delle prenotazioni dell'utente.
 */
Coda ottieniStorico(Utente u) {
    return u->storico;
}

/*
* Funzione per distruggere un utente e liberare la memoria allocata.
* Parametri:
* - `u`: puntatore alla struttura `Utente` da distruggere.
* * La funzione libera la memoria allocata per l'utente e per lo storico delle prenotazioni.
* * Nota: è importante chiamare questa funzione quando l'utente non è più necessario
 */
void distruggiUtente(Utente u) {
    free(u);
}

/*
* Funzione per stampare i dettagli di un utente.
* Parametri:
* - `u`: puntatore alla struttura `Utente` da stampare.
* * La funzione stampa i campi dell'utente, inclusi codice fiscale, nome, cognome, email e telefono.
 */
void stampaUtente(Utente u) {
    printf(CIANO "CF: " RESET "%s\n", u->CF);
    printf(CIANO "Nome: " RESET "%s\n", u->nome);
    printf(CIANO "Cognome: " RESET "%s\n", u->cognome);
    printf(CIANO "Email: " RESET "%s\n", u->email);
    printf(CIANO "Telefono: " RESET "%s\n", u->telefono);
}

