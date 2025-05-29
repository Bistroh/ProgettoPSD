#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "test/Test.h"
#include "HashTbUtenti.h"
#include "HashTbAuto.h"
#include "List_Prenotazione.h"
#include "test/Utile_UtenteMenu.h"

#define M 64
#define ROSSO "\x1b[31m"
#define VERDE "\x1b[32m"
#define RESET "\x1b[0m"

void caricaUtentiTest(UtentiHashTB *tab) {
    inserisciUtente(tab, creaUtente("DNTCRL65S67M126L", "Carla", "Danti", "carla@gmail.com", "3331234567", "Password123!"));
}

void caricaAutoTest(AutoHashTB *tab) {
    inserisciAuto(tab, creaAuto("AB123CD", "Fiat", "Panda", "Via Roma 10", 2000, 15.00));
}

Lista caricaPrenotazioni(Lista prenotazioni){
    // Aggiungi una prenotazione di esempio
    prenotazioni = consLista(creaPrenotazione("DNTCRL65S67M126L", "AB123CD", 0, 0, 15, 18), prenotazioni);
    prenotazioni = consLista(creaPrenotazione("DNTCRL65S67M126L", "AB123CD", 5, 5, 15, 18), prenotazioni);
    prenotazioni = consLista(creaPrenotazione("DNTCRL65S67M126L", "AB123CD", 0, 0, 21, 23), prenotazioni);
    prenotazioni = consLista(creaPrenotazione("DNTCRL65S67M126L", "AB123CD", 5, 6, 20, 6), prenotazioni);
    prenotazioni = consLista(creaPrenotazione("DNTCRL65S67M126L", "AB123CD", 0, 6, 1, 24), prenotazioni);

    return prenotazioni;
}

void eseguiPrenotazioneSimulata(Lista prenotazioni, UtentiHashTB tabUtenti, AutoHashTB tabAuto, int g_inizio, int g_fine, int ora_inizio, int ora_fine, FILE *output_fp) {
    int stato = 1;
    Utente u = cercaUtente(tabUtenti, "DNTCRL65S67M126L");
    if (!u) {
        fprintf(output_fp, ROSSO "Utente non trovato!\n" RESET);
        return;
    }

    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, ottieniCF(u), "AB123CD", &g_inizio, &g_fine, &ora_inizio, &ora_fine, &stato);

    if (prenotazioni == NULL) {
        fprintf(output_fp, "Prenotazione non riuscita.\n");
    } else {
        if(stato){
            Prenotazione p = ottieniPrimo(prenotazioni);
            stampaPrenotazioneSuFile(p, output_fp);
        }
    }
    return;
}

void eseguiCalcoloCostoSimulato(UtentiHashTB tabUtenti, AutoHashTB tabAuto, Lista prenotazioni) {
    // Cerca l’utente di test
    Utente u = cercaUtente(tabUtenti, "DNTCRL65S67M126L");
    if (!u) {
        printf("Utente non trovato.\n");
        return;
    }

    // Calcola il prezzo totale delle prenotazioni associate all'utente
    float costoTotale = calcolaPrezziPrenotazioni(prenotazioni, u, tabAuto);

    // Stampa il costo totale (con due cifre decimali)
    printf("Costo totale per %s %s: €%.2f\n", u->nome, u->cognome, costoTotale);
}


int run_test_case(char *tc_id, char *test_type) {
    char input_fname[M], output_fname[M], oracle_fname[M];

    snprintf(input_fname, M,  "test/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fname, M, "test/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, M, "test/%s/%s_oracle.txt", tc_id, tc_id);

    FILE *input_fp = fopen(input_fname, "r");
    FILE *output_fp = fopen(output_fname, "w");
    FILE *oracle_fp = fopen(oracle_fname, "r");

    if (!input_fp || !output_fp || !oracle_fp) {
        printf(ROSSO "Errore apertura file: %s, %s o %s\n" RESET, input_fname, output_fname, oracle_fname);
        if (input_fp) fclose(input_fp);
        if (output_fp) fclose(output_fp);
        if (oracle_fp) fclose(oracle_fp);
        return 0;
    }

    UtentiHashTB tabUtenti = nuovaHashTBUtenti();
    AutoHashTB tabAuto = creaAutoHashTB();
    Lista prenotazioni = nuovaLista();

    caricaUtentiTest(&tabUtenti);
    caricaAutoTest(&tabAuto);

    if (strcmp(test_type, "PRENOTA") == 0) {
    char line[256];
    while (fgets(line, sizeof(line), input_fp)) {
        // Rimuove newline finale, se presente
        line[strcspn(line, "\n")] = '\0';

        int g1, g2, o1, o2;
        if (sscanf(line, "%d %d %d %d", &g1, &g2, &o1, &o2) == 4) {
            eseguiPrenotazioneSimulata(prenotazioni, tabUtenti, tabAuto, g1, g2, o1, o2, output_fp);
        } else {
            fprintf(output_fp, "Riga input ignorata (formato non valido): %s\n", line);
        }
    }
    if(strcmp(test_type, "CALCOLO") == 0) {
        fprintf(output_fp, "Test di prenotazione completato.\n");
    }
} else {
    fprintf(output_fp, "Tipo test non supportato: %s\n", test_type);
}


    fclose(input_fp);
    fclose(output_fp);

    // Ora riapri output in lettura per il confronto
    output_fp = fopen(output_fname, "r");
    if (!output_fp) {
        printf(ROSSO "Errore apertura file output in lettura: %s\n" RESET, output_fname);
        fclose(oracle_fp);
        return 0;
    }

    // Confronto riga per riga
    char r1[256], r2[256];
    int pass = 1;
    while (1) {
        char *out_line = fgets(r1, sizeof(r1), output_fp);
        char *orc_line = fgets(r2, sizeof(r2), oracle_fp);

        if (!out_line && !orc_line) {
            // entrambi EOF
            break;
        }
        if (!out_line || !orc_line || strcmp(r1, r2) != 0) {
            pass = 0;
            break;
        }
    }

    fclose(output_fp);
    fclose(oracle_fp);

    return pass;
}


void esegui_test_suite(const char *suite_file, const char *result_file) {
    char path_suite[M];
    char path_result[M];
    snprintf(path_suite, M, "test/%s", suite_file);
    snprintf(path_result, M, "test/%s", result_file);
    FILE *suite = fopen(path_suite, "r");
    FILE *result = fopen(path_result, "w");

    if (suite == NULL || result == NULL) {
        printf(ROSSO "Errore apertura test suite o risultati\n" RESET);
        return;
    }

    char tc_id[M], test_type[M];
    while (fscanf(suite, "%s %s", tc_id, test_type) == 2) {
        int pass = run_test_case(tc_id, test_type);
        printf("%s [%s]: %s\n", tc_id, test_type, pass ? VERDE "PASS" RESET : ROSSO "FAIL" RESET);
        fprintf(result, "%s - %s - %s\n", tc_id, test_type, pass ? "PASS" : "FAIL");
    }

    fclose(suite);
    fclose(result);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(ROSSO "Uso corretto: %s <file_suite> <file_risultati>\n" RESET, argv[0]);
        return 1;
    }

    esegui_test_suite(argv[1], argv[2]);
    return 0;
}
