#ifndef CONTROLLI_H
#define CONTROLLI_H

/* Funzione: stringaValida
 * ------------------------------
 * Parametri:
 * - `str`: la stringa da verificare.
 * ------------------------------
 * Precondizioni:
 * - `str` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se la stringa è valida, 0 altrimenti.
 * ------------------------------
 */
int stringaValida(const char *str);

/* Funzione: confrontaCaseInsensitive
 * ------------------------------
 * Parametri:
 * - `a`: la prima stringa da confrontare.
 * - `b`: la seconda stringa da confrontare.
 * ------------------------------
 * Precondizioni:
 * - `a` e `b` devono essere stringhe non nulle.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 0 se le stringhe sono uguali (ignorando il caso), un valore negativo se `a` è minore di `b`,
 *   un valore positivo se `a` è maggiore di `b`.
 * ------------------------------
 */
int confrontaCaseInsensitive(const char *a, const char *b);

/* Funzione: validaPassword
 * ------------------------------
 * Parametri:
 * - `pwd`: la password da verificare.
 * ------------------------------
 * Precondizioni:
 * - `pwd` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se la password è valida, 0 altrimenti.
 * ------------------------------
 */
int validaPassword(const char *pwd);

/* Funzione: validaTarga
 * ------------------------------
 * Parametri:
 * - `targa`: la targa da verificare.
 * ------------------------------
 * Precondizioni:
 * - `targa` deve essere una stringa non vuota di 7 caratteri (3 lettere + 4 numeri).
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se la targa è valida, 0 altrimenti.
 * ------------------------------
 */
int validaTarga(const char *targa);

/* Funzione: validaEmail
 * ------------------------------
 * Parametri:
 * - `email`: l'email da verificare.
 * ------------------------------
 * Precondizioni:
 * - `email` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se l'email è valida, 0 altrimenti.
 * ------------------------------
 */
int validaEmail(const char *email);

/* Funzione: validaCodiceFiscale
 * ------------------------------
 * Parametri:
 * - `cf`: il codice fiscale da verificare.
 * ------------------------------
 * Precondizioni:
 * - `cf` deve essere una stringa non vuota di 16 caratteri.
 * --------------------------------
 * Postcondizioni:
 * - Restituisce 1 se il codice fiscale è valido, 0 altrimenti.
 * ------------------------------
 */
int validaCodiceFiscale(const char *cf);

/* Funzione: validaViaStradale
 * ------------------------------
 * Parametri:
 * - `input`: la via stradale da verificare.
 * ------------------------------
 * Precondizioni:
 * - `input` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se la via stradale è valida, 0 altrimenti.
 * ------------------------------
 */
int validaViaStradale(const char* input);

/* Funzione: validaTelefono
 * ------------------------------
 * Parametri:
 * - `numero`: il numero di telefono da verificare.
 * ------------------------------
 * Precondizioni:
 * - `numero` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se il numero di telefono è valido, 0 altrimenti.
 * ------------------------------
 */
int validaTelefono(const char *numero);

/* Funzione: pulisciConsole
 * ------------------------------
 * Parametri:
 * - Nessuno.
 * ------------------------------
 * Precondizioni:
 * - Nessuna.
 * ------------------------------
 * Postcondizioni:
 * - Pulisce la console.
 * ------------------------------
 */
void pulisciConsole();

/* Funzione: pausaConsole
 * ------------------------------
 * Parametri:
 * - Nessuno.
 * ------------------------------
 * Precondizioni:
 * - Nessuna.
 * ------------------------------
 * Side Effect:
 * - Attende che l'utente prema un tasto per continuare.
 * ------------------------------
 */
void pausaConsole();

/* Funzione: validaCognome
 * ------------------------------
 * Parametri:
 * - `cognome`: il cognome da verificare.
 * ------------------------------
 * Precondizioni:
 * - `cognome` deve essere una stringa non vuota.
 * ------------------------------
 * Side Effect:
 * - Restituisce 1 se il cognome è valido, 0 altrimenti.
 * ------------------------------
 */
int validaCognome(const char *cognome);

/* Funzione: validaNome
 * ------------------------------
 * Parametri:
 * - `nome`: il nome da verificare.
 * ------------------------------
 * Precondizioni:
 * - `nome` deve essere una stringa non vuota.
 * ------------------------------
 * Postcondizioni:
 * - Restituisce 1 se il nome è valido, 0 altrimenti.
 * ------------------------------
 */
int validaNome(const char *nome);

/* Funzione: capitalizza
 * ------------------------------
 * Parametri:
 * - `nome`: la stringa da capitalizzare.
 * ------------------------------
 * Precondizioni:
 * - `nome` deve essere una stringa non vuota.
 * ------------------------------
 * Side Effect:
 * - Capitalizza la prima lettera di ogni parola nella stringa `nome`.
 * ------------------------------
 */
void capitalizza(char* nome);
#endif //CONTROLLI_H
