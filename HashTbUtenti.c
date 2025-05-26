#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Utente.h"
#include "uthash.h"
#include "Controlli.h"
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

typedef struct {
    char *cf;       // Chiave (codice fiscale)
    Utente utente;  // Valore
    UT_hash_handle hh;
} HashEntry;

typedef HashEntry* HashTable;

HashTable newHashtableUtenti() {
    return NULL; // Uthash usa una variabile inizializzata a NULL
}

int insertUtente(HashTable *h, Utente u) {
    const char *cf = getCF(u);
    if (!cf || !u) return 0;

    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, cf, entry);
    if (entry) {
        return 0; // già presente
    }

    entry = malloc(sizeof(HashEntry));
    entry->cf = strdup(cf);  // duplica la chiave
    entry->utente = u;
    HASH_ADD_KEYPTR(hh, *h, entry->cf, strlen(entry->cf), entry);
    return 1;
}

Utente cercaUtente(HashTable h, const char *CF) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(h, CF, entry);
    return entry ? entry->utente : NULL;
}

Utente eliminaUtente(HashTable *h, const char *CF) {
    HashEntry *entry = NULL;
    HASH_FIND_STR(*h, CF, entry);
    if (entry) {
        Utente u = entry->utente;
        HASH_DEL(*h, entry);
        free(entry->cf);
        free(entry);
        return u; // Utente non distrutto qui, restituito al chiamante
    }
    return NULL;
}

void distruggiHashTableUtenti(HashTable *h) {
    HashEntry *current, *tmp;
    HASH_ITER(hh, *h, current, tmp) {
        HASH_DEL(*h, current);
        distruggiUtente(current->utente); // distrugge Utente
        free(current->cf);                // libera chiave
        free(current);                    // libera nodo
    }
    *h = NULL;
}
// Funzione per stampare la tabella utenti
void stampaHashTableUtenti(HashTable h) {
    HashEntry *current;
    for (current = h; current != NULL; current = current->hh.next) {
        printf(CIANO "CF: %s\n" RESET, current->cf);
        stampaUtente(current->utente); // Assicurati di avere una funzione per stampare Utente
    }
}

void to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

Utente loginRegisterUtente(HashTable *h) {
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
        CF[strcspn(CF, "\n")] = '\0';  // rimuovo newline
        to_upper(CF);
        if (!validaCodiceFiscale(CF)) printf(ROSSO "Codice fiscale non valido.\n" RESET);
    } while (!validaCodiceFiscale(CF));

    Utente u = cercaUtente(*h, CF);

    if (scelta == 1) {
        // LOGIN
        if (u != NULL) {
            printf(GIALLO "Inserisci la tua password: " RESET);
            while (getchar() != '\n');  // pulizia buffer
            if (fgets(passwordInserita, sizeof(passwordInserita), stdin) != NULL) {
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';  // rimuovo newline
            } else {
                printf(ROSSO "Errore nella lettura della password.\n" RESET);
                return NULL;
            }

            if (strcmp(getPassword(u), passwordInserita) == 0) {
                printf(VERDE "Login riuscito! Benvenuto, %s %s!\n" RESET, getNome(u), getCognome(u));
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
            nome[strcspn(nome, "\n")] = '\0';  // rimuovo newline
            if(!validaNome(nome)) {
                printf(ROSSO "Nome non valido. Utilizza solo lettere e spazi\n" RESET);
            }
            } while (!validaNome(nome));
			capitalizza(nome);  // prima lettera maiuscola

			do{
            printf(GIALLO "Inserisci il tuo cognome: " RESET);
            fgets(cognome, sizeof(cognome), stdin);
            cognome[strcspn(cognome, "\n")] = '\0';  // rimuovo newline
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

            if (insertUtente(h, nuovoUtente)) {
                printf(VERDE "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                       getNome(nuovoUtente), getCognome(nuovoUtente));
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
                passwordInserita[strcspn(passwordInserita, "\n")] = '\0';  // rimuovo newline
            } else {
                printf(ROSSO "Errore nella lettura della password.\n" RESET);
                return NULL;
            }

            if (strcmp(getPassword(u), passwordInserita) == 0) {
                printf(VERDE "Login riuscito! Benvenuto, %s %s!\n" RESET, getNome(u), getCognome(u));
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
            	nome[strcspn(nome, "\n")] = '\0';  // rimuovo newline
            	if(!validaNome(nome)) {
                	printf(ROSSO "Nome non valido. Utilizza solo lettere e spazi\n" RESET);
            	}
            } while (!validaNome(nome));
			capitalizza(nome);  // prima lettera maiuscola

			do{
            	printf(GIALLO "Inserisci il tuo cognome: " RESET);
            	fgets(cognome, sizeof(cognome), stdin);
            	cognome[strcspn(cognome, "\n")] = '\0';  // rimuovo newline
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

            if (insertUtente(h, nuovoUtente)) {
                printf(VERDE "Registrazione completata con successo! Benvenuto, %s %s!\n" RESET,
                       getNome(nuovoUtente), getCognome(nuovoUtente));
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



void aggiungiPrenotazioniAStoricoUtenti(HashTable h, List listaPrenotazioni) {
    List current = listaPrenotazioni;

    while (!emptyList(current)) {
        Prenotazione p = getFirst(current);
        const char *cf = getCFPrenotazione(p);
        Utente u = cercaUtente(h, cf);

        if (u != NULL) {
            Queue storico = getStorico(u);
            Prenotazione copia = copiaPrenotazione(p); // crea una copia della prenotazione
            enqueue(copia, storico);
        } else {
            printf(ROSSO "Utente con CF %s non trovato. Prenotazione ignorata.\n" RESET, cf);
        }

        current = tailList(current);
    }
}

void stampaStoricoTuttiUtenti(HashTable h) {
    HashEntry *current = h;

	if(current == NULL) {
		printf(ROSSO "Nessun utente trovato, non posso stampare lo storico\n" RESET);
		return;
	}

    for (current; current != NULL; current = current->hh.next) {
        Utente u = current->utente;
        printf(CIANO "Utente: %s %s (CF: %s)\n" RESET, getNome(u), getCognome(u), current->cf);

        Queue storico = getStorico(u);

        if (emptyQueue(storico)) {
            printf(GIALLO "  Nessuna prenotazione nello storico.\n\n" RESET);
            continue;
        }

        Queue copia = copiaQueue(storico); // funzione da implementare se non c'è
        if (copia == NULL) {
            printf(ROSSO "  Errore nella copia dello storico.\n\n" RESET);
            continue;
        }

        int i = 1;
        while (!emptyQueue(copia)) {
            Prenotazione p = dequeue(copia);
            printf(GIALLO "  Prenotazione #%d:\n" RESET, i++);
            stampaPrenotazione(p);
        }

        free(copia); // libera solo la struttura coda, non le prenotazioni (se sono condivise)
        printf("\n");
    }
}

