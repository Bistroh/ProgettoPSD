#include <glib.h>
#include "Utente.h"
#include "HashTbUtenti.h"

typedef GHashTable* HashTable;

HashTable newHashtableUtenti() {
    // Usa string hash + confronto stringhe
    return g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)distruggiUtente);
}

int insertUtente(HashTable h, Utente u) {
    const char *cf = getCF(u);
    if (g_hash_table_contains(h, cf)) {
        return 0; // già presente
    }
    // Inserisce il puntatore Utente (copiato fuori, distruggiUtente chiamato alla fine)
    g_hash_table_insert(h, (gpointer)cf, u);
    return 1;
}

Utente cercaUtente(HashTable h, const char *CF) {
    return (Utente)g_hash_table_lookup(h, CF);
}

Utente eliminaUtente(HashTable h, const char *CF) {
    Utente u = g_hash_table_lookup(h, CF);
    if (u) {
        // rimuove senza chiamare distruggiUtente automaticamente
        g_hash_table_steal(h, CF);
        return u;
    }
    return NULL;
}

void distruggiHashTable(HashTable h) {
    g_hash_table_destroy(h);  // libera anche tutti gli Utenti (grazie a GDestroyNotify)
}
