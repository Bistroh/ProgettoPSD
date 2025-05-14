#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utente.h"
#include "uthash.h"

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
//funzione per stampare la tabella
void stampaHashTableUtenti(HashTable h) {
    HashEntry *current;
    for (current = h; current != NULL; current = current->hh.next) {
        printf("CF: %s\n", current->cf);
        stampaUtente(current->utente); // Assicurati di avere una funzione per stampare Utente
    }
}

Utente loginRegisterUtente(HashTable *h) {
    char CF[17];
    char nome[20];
    char cognome[20];
    char email[30];
    char telefono[15];
    char password[20];

    printf("Inserisci il tuo Codice Fiscale: ");
    scanf("%16s", CF);

    Utente u = cercaUtente(*h, CF);

    if (u != NULL) {
        printf("Benvenuto, %s %s!\n", getNome(u), getCognome(u));
        char passwordInserita[20];
        printf("Inserisci la tua password: ");
        scanf("%19s", passwordInserita);

        if (strcmp(getPassword(u), passwordInserita) == 0) {
            printf("Login riuscito!\n");
            return u;
        } else {
            printf("Password errata. Riprova.\n");
            return NULL;
        }
    } else {
        printf("Utente non trovato. Procedi con la registrazione.\n");

        printf("Inserisci il tuo nome: ");
        scanf("%19s", nome);

        printf("Inserisci il tuo cognome: ");
        scanf("%19s", cognome);

        printf("Inserisci la tua email: ");
        scanf("%29s", email);

        printf("Inserisci il tuo numero di telefono: ");
        scanf("%14s", telefono);

        printf("Crea una password: ");
        scanf("%19s", password);

        Utente nuovoUtente = creaUtente(CF, nome, cognome, email, password, telefono);

        if (insertUtente(h, nuovoUtente)) {
            printf("Registrazione completata con successo! Benvenuto, %s %s!\n",
                   getNome(nuovoUtente), getCognome(nuovoUtente));
            return nuovoUtente;
        } else {
            printf("Errore nella registrazione, riprova.\n");
            return NULL;
        }
    }
}

