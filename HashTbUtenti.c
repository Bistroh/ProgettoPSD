#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Utente.h"
#include "uthash.h"
#include "Controlli.h"
#include "HashTbUtenti.h"
#include "Coda_StoricoUtente.h"
#include "List_Prenotazione.h"
/*Aggiungo delle costanti per rendere più facile la colorazione
delle parole stampate su schermo. In modo da colorare i menù
di scelta. */
#define RESET   "\x1b[0m"
#define ROSSO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define GIALLO  "\x1b[33m"
#define CIANO    "\x1b[36m"

/*
    * Struttura per la tabella hash degli utenti.
    * Utilizza UTHash per gestire la tabella hash.
    * La chiave è il codice fiscale (CF) dell'utente.
 */
struct HashRecord{
    char *cf;       // Chiave (codice fiscale)
    Utente utente;  // Valore
    UT_hash_handle hh;
};

/*
    * La tabella hash degli utenti è un alias per un puntatore a HashRecord.
*   * La tabella hash è inizialmente vuota (NULL).
* *   * Le operazioni di inserimento, ricerca ed eliminazione sono gestite tramite funzioni dedicate.
 */
typedef HashRecord* UtentiHashTB;  // Tipo alias per la tabella hash degli utenti
UtentiHashTB nuovaHashTBUtenti() {
    return NULL; // Uthash usa una variabile inizializzata a NULL
}

/*
    * Inserisce un utente nella tabella hash.
* Parametri:
* *   - `h`: puntatore alla tabella hash degli utenti.
* *   - `u`: l'utente da inserire.
*   * Restituisce 1 se l'inserimento è avvenuto con successo, 0 se il codice fiscale era già presente.
 */
int inserisciUtente(UtentiHashTB *h, Utente u) {
    const char *cf = ottieniCF(u);
    if (!cf || !u) return 0;

    // Controlla se il codice fiscale è valido
    HashRecord *record = NULL;
    HASH_FIND_STR(*h, cf, record);
    if (record) {
        return 0; // già presente
    }

    record = malloc(sizeof(HashRecord));
    record->cf = strdup(cf);  // duplica la chiave
    record->utente = u;
    HASH_ADD_KEYPTR(hh, *h, record->cf, strlen(record->cf), record);
    return 1;
}

/*
    * Cerca un utente nella tabella hash tramite codice fiscale (CF).
* * Parametri:
* *   - `h`: la tabella hash degli utenti.
* *   - `CF`: il codice fiscale dell'utente da cercare.
* * Restituisce il puntatore all'utente se trovato, altrimenti NULL.
 */
Utente cercaUtente(UtentiHashTB h, const char *CF) {
    HashRecord *record = NULL;
    HASH_FIND_STR(h, CF, record);
    // Se il record è trovato, restituisce l'utente associato
    return record ? record->utente : NULL;
}

/*
    * Elimina un utente dalla tabella hash e lo restituisce senza deallocarlo.
* * Parametri:
* *   - `h`: puntatore alla tabella hash degli utenti.
* *   - `CF`: il codice fiscale dell'utente da eliminare.
* * Restituisce l'utente eliminato, o NULL se non trovato.
 */
Utente eliminaUtente(UtentiHashTB *h, const char *CF) {
    HashRecord *record = NULL;
    // Cerca il record con il codice fiscale specificato
    HASH_FIND_STR(*h, CF, record);
    // Se il record è trovato, lo elimina dalla tabella hash
    if (record) {
        Utente u = record->utente;
        HASH_DEL(*h, record);
        free(record->cf);
        free(record);
        return u; // Utente non distrutto qui, restituito al chiamante
    }
    return NULL;
}

/*
    * Distrugge completamente la tabella hash degli utenti e tutti gli utenti contenuti.
* * Parametri:
* *   - `h`: puntatore alla tabella hash degli utenti.
* * Dopo la chiamata, il puntatore viene impostato a NULL.
 */
void distruggiHashTBUtenti(UtentiHashTB *h) {
  // Controlla se la tabella hash è già vuota
    HashRecord *elAttuale, *tmp;
    HASH_ITER(hh, *h, elAttuale, tmp) {
        HASH_DEL(*h, elAttuale);
        distruggiUtente(elAttuale->utente); // distrugge Utente
        free(elAttuale->cf);                // libera chiave
        free(elAttuale);                    // libera nodo
    }
    *h = NULL;
}

/*
    * Stampa tutti gli utenti nella tabella hash.
* * Parametri:
* *   - `h`: la tabella hash degli utenti.
 */
void stampaHashTableUtenti(UtentiHashTB h) {
    HashRecord *elAttuale;
    // Controlla se la tabella hash è vuota
    for (elAttuale = h; elAttuale != NULL; elAttuale = elAttuale->hh.next) {
        printf(CIANO "CF: %s\n" RESET, elAttuale->cf);
        stampaUtente(elAttuale->utente); // Assicurati di avere una funzione per stampare Utente
    }
}

/*
* to_upper - Converte una stringa in maiuscolo.
* Parametri:
* str: La stringa da convertire.
 */
void to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

/* * Funzione per la registrazione o il login di un utente.
 * Parametri:
 * - `h`: puntatore alla tabella hash degli utenti.
 * Restituisce un puntatore all'utente registrato o loggato, o NULL in caso di errore.
* * Questa funzione gestisce sia il login che la registrazione di un utente.
* * Se l'utente esiste già, permette il login; altrimenti, procede con la registrazione.
* * Durante la registrazione, richiede all'utente di inserire i propri dati personali
* * (nome, cognome, email, telefono e password) e li valida.
* * Se la registrazione ha successo, l'utente viene inserito nella tabella hash.
* * Se l'utente non esiste e la registrazione fallisce, restituisce NULL.
 */
Utente loginRegistrazioneUtente(UtentiHashTB *h) {
    // Definizione delle variabili necessarie
    int scelta;
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char passwordInserita[20];
    char buffer[100];
    int c;

    printf(VERDE "Benvenuto!\n" RESET);
    printf(GIALLO "1. Login\n");
    printf("2. Registrazione\n");
    // Chiedo all'utente di scegliere tra login e registrazione
    while (1) {
        printf(GIALLO "Seleziona un'opzione (1 o 2): " RESET);
        fgets(buffer, sizeof(buffer), stdin);

        // Controlla che sia un numero e che sia 1 o 2
        if (sscanf(buffer, "%d", &scelta) != 1 || (scelta != 1 && scelta != 2)) {
            printf(ROSSO "Errore: inserisci 1 per Login o 2 per Registrazione.\n" RESET);
        } else {
            break;
        }
    }

    do {
        printf(GIALLO "Inserisci codice fiscale (16 caratteri): " RESET);
        fgets(CF, 17, stdin);
        CF[strcspn(CF, "\n")] = '\0';  // rimuovo nuova linea
        to_upper(CF);
        if (!validaCodiceFiscale(CF)) printf(ROSSO "Codice fiscale non valido.\n" RESET);
    } while (!validaCodiceFiscale(CF));

    // Cerco l'utente nella tabella hash
    Utente u = cercaUtente(*h, CF);

    if (scelta == 1) {
        // LOGIN
        if (u != NULL) {
            printf(GIALLO "Inserisci la tua password: " RESET);
            while (getchar() != '\n');  // pulizia buffer
            if (fgets(passwordInserita, sizeof(passwordInserita), stdin) != NULL) {
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';  // rimuovo nuova linea
            } else {
                printf(ROSSO "Errore nella lettura della password.\n" RESET);
                return NULL;
            }

            if (strcmp(ottieniPassword(u), passwordInserita) == 0) {
                printf(VERDE "Login riuscito! Benvenuto, %s %s!\n" RESET, ottieniNome(u), ottieniCognome(u));
                return u;
            } else {
                printf(ROSSO "Password errata. Riprova.\n" RESET);
                return NULL;
            }
        } else {
            printf(ROSSO "Utente non trovato. Procedo con la registrazione.\n" RESET);
			while ((c = getchar()) != '\n' && c != EOF);  // pulizia buffer
            // REGISTRAZIONE AUTOMATICA
            do{
            printf(GIALLO "Inserisci il tuo nome: " RESET);
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';  // rimuovo nuova linea
            if(!validaNome(nome)) {
                printf(ROSSO "Nome non valido. Utilizza solo lettere e spazi\n" RESET);
            }
            } while (!validaNome(nome));
			capitalizza(nome);  // prima lettera maiuscola

			do{
            printf(GIALLO "Inserisci il tuo cognome: " RESET);
            fgets(cognome, sizeof(cognome), stdin);
            cognome[strcspn(cognome, "\n")] = '\0';  // rimuovo nuova linea
            if(!validaCognome(cognome)) {
                printf(ROSSO "Cognome non valido. Utilizza solo lettere e spazi\n" RESET);
            }
            } while (!validaCognome(cognome));
            capitalizza(cognome);  // prima lettera maiuscola

            do {
                printf(GIALLO "Inserisci la tua email: " RESET);
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';
                if (!validaEmail(email)) printf(ROSSO "Email non valida.\n" RESET);
            } while (!validaEmail(email));

            do {
                printf(GIALLO "Inserisci numero di telefono (10 cifre, inizia per 3): " RESET);
                fgets(telefono, sizeof(telefono), stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                if (!validaTelefono(telefono)) printf(ROSSO "Numero non valido.\n" RESET);
            } while (!validaTelefono(telefono));

            do {
                printf(GIALLO "Inserisci password (almeno 8 caratteri, 1 maiuscola, 1 minuscola, 1 numero, 1 simbolo): " RESET);
                fgets(passwordInserita, sizeof(passwordInserita), stdin);
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';
                if (!validaPassword(passwordInserita)) printf(ROSSO "Password non valida.\n" RESET);
            } while (!validaPassword(passwordInserita));

            // Creo un nuovo utente con i dati inseriti
            Utente nuovoUtente = creaUtente(CF, nome, cognome, email, passwordInserita, telefono);

            if (inserisciUtente(h, nuovoUtente)) {
                printf(VERDE "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                       ottieniNome(nuovoUtente), ottieniCognome(nuovoUtente));
                return nuovoUtente;
            } else {
                printf(ROSSO "Errore nella registrazione, riprova.\n" RESET);
                return NULL;
            }
        }
    } else if (scelta == 2) {
        // REGISTRAZIONE
        if (u != NULL) {
            printf(ROSSO "Utente già registrato. Procedo con il login.\n" RESET);

            printf(GIALLO "Inserisci la tua password: " RESET);
            while (getchar() != '\n');  // pulizia buffer
            if (fgets(passwordInserita, sizeof(passwordInserita), stdin) != NULL) {
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';  // rimuovo nuova linea
            } else {
                printf(ROSSO "Errore nella lettura della password.\n" RESET);
                return NULL;
            }

            if (strcmp(ottieniPassword(u), passwordInserita) == 0) {
                printf(VERDE "Login riuscito! Benvenuto, %s %s!\n" RESET, ottieniNome(u), ottieniCognome(u));
                return u;
            } else {
                printf(ROSSO "Password errata. Riprova.\n" RESET);
                return NULL;
            }
        } else {
          	while ((c = getchar()) != '\n' && c != EOF);  // pulizia buffer
            do{
            	printf(GIALLO "Inserisci il tuo nome: " RESET);
            	fgets(nome, sizeof(nome), stdin);
            	nome[strcspn(nome, "\n")] = '\0';  // rimuovo nuova linea
            	if(!validaNome(nome)) {
                	printf(ROSSO "Nome non valido. Utilizza solo lettere e spazi\n" RESET);
            	}
            } while (!validaNome(nome));
			capitalizza(nome);  // prima lettera maiuscola

			do{
            	printf(GIALLO "Inserisci il tuo cognome: " RESET);
            	fgets(cognome, sizeof(cognome), stdin);
            	cognome[strcspn(cognome, "\n")] = '\0';  // rimuovo nuova linea
            	if(!validaCognome(cognome)) {
                	printf(ROSSO "Cognome non valido. Utilizza solo lettere e spazi\n" RESET);
            	}
            } while (!validaCognome(cognome));
            capitalizza(cognome);  // prima lettera maiuscola

            do {
                printf(GIALLO "Inserisci la tua email: " RESET);
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';
                if (!validaEmail(email)) printf(ROSSO "Email non valida.\n" RESET);
            } while (!validaEmail(email));

            do {
                printf(GIALLO "Inserisci numero di telefono (10 cifre, inizia per 3): " RESET);
                fgets(telefono, sizeof(telefono), stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                if (!validaTelefono(telefono)) printf(ROSSO "Numero non valido.\n" RESET);
            } while (!validaTelefono(telefono));

            do {
                printf(GIALLO "Inserisci password (almeno 8 caratteri, 1 maiuscola, 1 minuscola, 1 numero, 1 simbolo): " RESET);
                fgets(passwordInserita, sizeof(passwordInserita), stdin);
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';
                if (!validaPassword(passwordInserita)) printf(ROSSO "Password non valida.\n" RESET);
            } while (!validaPassword(passwordInserita));

            Utente nuovoUtente = creaUtente(CF, nome, cognome, email, passwordInserita, telefono);

            if (inserisciUtente(h, nuovoUtente)) {
                printf(VERDE "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                       ottieniNome(nuovoUtente), ottieniCognome(nuovoUtente));
                return nuovoUtente;
            } else {
                printf(ROSSO "Errore nella registrazione, riprova.\n" RESET);
                return NULL;
            }
        }
    } else {
        printf(ROSSO "Scelta non valida.\n" RESET);
        return NULL;
    }
}



void aggiungiPrenotazioniAStoricoUtenti(UtentiHashTB h, Lista listaPrenotazioni) {
    Lista elAttuale = listaPrenotazioni;

    while (!ListaVuota(elAttuale)) {
        Prenotazione p = ottieniPrimo(elAttuale);
        const char *cf = ottieniCFPrenotazione(p);
        Utente u = cercaUtente(h, cf);

        if (u != NULL) {
            Coda storico = ottieniStorico(u);
            Prenotazione copia = copiaPrenotazione(p); // crea una copia della prenotazione
            inserisciCoda(copia, storico);
        } else {
            printf(ROSSO "Utente con CF %s non trovato. Prenotazione ignorata.\n" RESET, cf);
        }

        elAttuale = codaLista(elAttuale);
    }
}

void stampaStoricoTuttiUtenti(UtentiHashTB h) {
    HashRecord *elAttuale = h;

	if(elAttuale == NULL) {
		printf(ROSSO "Nessun utente trovato, non posso stampare lo storico\n" RESET);
		return;
	}

    for (elAttuale; elAttuale != NULL; elAttuale = elAttuale->hh.next) {
        Utente u = elAttuale->utente;
        printf(CIANO "Utente: %s %s (CF: %s)\n" RESET, ottieniNome(u), ottieniCognome(u), elAttuale->cf);

        Coda storico = ottieniStorico(u);

        if (codaVuota(storico)) {
            printf(GIALLO "  Nessuna prenotazione nello storico.\n\n" RESET);
            continue;
        }

        Coda copia = copiaCoda(storico); // funzione da implementare se non c'è
        if (copia == NULL) {
            printf(ROSSO "  Errore nella copia dello storico.\n\n" RESET);
            continue;
        }

        int i = 1;
        while (!codaVuota(copia)) {
            Prenotazione p = prelevaCoda(copia);
            printf(GIALLO "  Prenotazione #%d:\n" RESET, i++);
            stampaPrenotazione(p);
        }

        free(copia); // libera solo la struttura coda, non le prenotazioni (se sono condivise)
        printf("\n");
    }
}

void stampaStoricoTuttiUtentiSuFile(UtentiHashTB h, FILE *output_fp) {
    HashRecord *elAttuale = h;

    if (elAttuale == NULL) {
        fprintf(output_fp, "Nessun utente trovato, non posso stampare lo storico\n");
        return;
    }

    for (; elAttuale != NULL; elAttuale = elAttuale->hh.next) {
        Utente u = elAttuale->utente;
        fprintf(output_fp, "Utente: %s %s (CF: %s)\n", ottieniNome(u), ottieniCognome(u), elAttuale->cf);

        Coda storico = ottieniStorico(u);

        if (codaVuota(storico)) {
            fprintf(output_fp, "  Nessuna prenotazione nello storico.\n\n");
            continue;
        }

        Coda copia = copiaCoda(storico);
        if (copia == NULL) {
            fprintf(output_fp, "  Errore nella copia dello storico.\n\n");
            continue;
        }

        int i = 1;
        while (!codaVuota(copia)) {
            Prenotazione p = prelevaCoda(copia);
            fprintf(output_fp, "  Prenotazione #%d:\n", i++);
            stampaPrenotazioneSuFile(p, output_fp);  // Assicurati che questa stampa su FILE *
        }

        free(copia); // se disponibile, altrimenti free(copia)
        fprintf(output_fp, "\n");
    }
}

