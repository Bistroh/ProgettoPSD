#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "HashTbUtenti.h"
#include "HashTbAuto.h"
#include "List_Prenotazione.h"
#include "Utile_UtenteMenu.h"

// Definisce il nome del terminale in base al sistema operativo:
// - Su Windows (_WIN32), il terminale è "CON"
// - Su altri sistemi (Linux, macOS), il terminale è "/dev/tty"
#ifdef _WIN32
#define TERMINALE "CON"
#else
#define TERMINALE "/dev/tty"
#endif


#define M 64
#define ROSSO "\x1b[31m"
#define VERDE "\x1b[32m"
#define RESET "\x1b[0m"


/*
 * Funzione: caricaUtentiTest
 * -----------------------------
 * Parametri:
 * - `tab`: puntatore alla tabella hash degli utenti in cui caricare i dati di test.
 * -----------------------------
 * Precondizioni:
 * - `tab` deve essere un puntatore valido a una struttura `UtentiHashTB` inizializzata con `nuovaHashTBUtenti`.
 *-----------------------------
 * Postcondizioni:
 * - nessuna
 * -----------------------------
 * Side Effect:
 * Inserisce nella tabella hash cinque utenti predefiniti con dati anagrafici e di contatto.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
 * La funzione inizializza un insieme di strutture `Utente` con dati fittizi
 * (codice fiscale, nome, cognome) e li inserisce nella tabella hash `tabUtenti`.
 * Viene utilizzata durante i test automatici per garantire un insieme noto e stabile
 * di utenti su cui effettuare operazioni.
 * ------------------------------
 */
void caricaUtentiTest(UtentiHashTB *tab) {
    inserisciUtente(tab, creaUtente("DNTCRL65S67M126L", "Carla", "Danti", "carla@gmail.com", "Password123!", "3331234567"));
    inserisciUtente(tab, creaUtente("SRRLKR05T21F912R", "Luigi Karol", "Sorrentino", "karol.sorrentino@gmail.com", "pAssword9!.","333333333"));
    inserisciUtente(tab, creaUtente("DLTFNC00E69A294P", "Francesca", "Di Lieto", "francesca@gmail.com", "PWd_6322aaa?","333333339"));
    inserisciUtente(tab, creaUtente("NLOBTL90A11G230C","Bartolomeo", "Nola", "bartolomeo@tiscali.com", "BAR2188nol!.","333333337"));
    inserisciUtente(tab, creaUtente("SRLNCL02L18I483R", "Nicola", "Sarlo", "nicsarlo@proton.me","_18Luglio2002!","3393333357"));
}

/*
 * Funzione: caricaAutoTest
 * -----------------------------
 * Parametri:
 * - `tab`: puntatore alla tabella hash delle auto in cui caricare i dati di test.
 * -----------------------------
 * Precondizioni:
 * - `tab` deve essere un puntatore valido a una struttura `AutoHashTB` inizializzata con `creaAutoHashTB`.
 * -----------------------------
 * Postcondizioni:
 *  - nessuno.
 *  -----------------------------
 * Side effect:
 * Inserisce nella tabella hash cinque auto predefinite con dati relativi a modello, targa, indirizzo e costo.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
* La funzione crea una serie di strutture `Auto` con valori fittizi
 * (targa, marca, modello, categoria, costo orario) e le inserisce nella tabella hash `tabAuto`.
 * Questi dati vengono usati nei test automatici per simulare operazioni di prenotazione e calcolo costi.
 * -----------------------------
 */
void caricaAutoTest(AutoHashTB *tab) {
    inserisciAuto(tab, creaAuto("AB123CD", "Fiat", "Panda", "Via Roma 10", 2000, 15.00));
    inserisciAuto(tab, creaAuto("AA555BB", "Toyota", "Corolla", "Viale Salerno 23", 2015, 25.00));
    inserisciAuto(tab, creaAuto("CC777NN", "Alfa Romeo", "147", "Corso Padovano 1", 1999, 15.00));
    inserisciAuto(tab, creaAuto("VV444XX","Ford", "Kuga", "Viale Ranieri 5", 2010, 23.50));
    inserisciAuto(tab, creaAuto("BB222RR", "BMW", "X1", "Via Della Repubblica 15", 2023, 33.00));
}


/*
 * Funzione: caricaPrenotazioni
 * -----------------------------
 * Parametri:
 * - `prenotazioni`: lista esistente di prenotazioni.
 * - `g_i`: giorno di inizio prenotazione (0 = Lunedì, 6 = Domenica).
 * - `g_f`: giorno di fine prenotazione.
 * - `o_i`: ora di inizio prenotazione (0-23).
 * - `o_f`: ora di fine prenotazione (1-24).
 * - `CF`: codice fiscale dell’utente.
 * - `targa`: targa dell’auto.
 * -----------------------------
 * Precondizioni:
 * - `prenotazioni` è una lista valida (può essere vuota).
 * - `g_i`, `g_f`, `o_i`, `o_f` devono essere valori coerenti e validi.
 * - `CF` e `targa` devono essere stringhe valide e non nulle.
 * -----------------------------
 * Postcondizioni:
 * Aggiunge una prenotazione alla lista esistente.
 * -----------------------------
 * Restituisce:
 * La lista aggiornata con la nuova prenotazione in testa.
 * -----------------------------
 * La funzione crea una nuova prenotazione con i dati forniti e la aggiunge alla lista delle prenotazioni
 * esistente. Questa lista viene poi restituita aggiornata, pronta per successive elaborazioni
 * come calcolo costi o conferma disponibilità.
 * -----------------------------
 */
Lista caricaPrenotazioni(Lista prenotazioni, int g_i, int g_f, int o_i, int o_f, char * CF, char *targa){
    // Aggiungi una prenotazione di esempio
    prenotazioni = consLista(creaPrenotazione(CF, targa, g_i, g_f, o_i, o_f), prenotazioni);

    return prenotazioni;
}

/*
 * Funzione: eseguiPrenotazioneSimulata
 * -----------------------------
 * Parametri:
 * - `prenotazioni`: lista esistente di prenotazioni.
 * - `tabUtenti`: tabella hash degli utenti.
 * - `tabAuto`: tabella hash delle auto.
 * - `g_inizio`: giorno inizio prenotazione.
 * - `g_fine`: giorno fine prenotazione.
 * - `ora_inizio`: ora inizio prenotazione.
 * - `ora_fine`: ora fine prenotazione.
 * - `targa`: targa dell’auto da prenotare.
 * - `CF`: codice fiscale dell’utente che prenota.
 * - `output_fp`: puntatore al file su cui scrivere l'esito della prenotazione.
 * -----------------------------
 * Precondizioni:
 * - Le tabelle `tabUtenti` e `tabAuto` devono essere valide e inizializzate.
 * - `prenotazioni` è una lista valida.
 * - I parametri temporali devono essere coerenti.
 * - `output_fp` deve essere un file aperto in scrittura.
 * -----------------------------
 * Postcondizioni:
 * Esegue una prenotazione simulata se l’utente e l’auto esistono. Scrive l’esito nel file di output.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
 * La funzione tenta di effettuare una prenotazione simulata su `tabAuto` e `tabUtenti`
 * per l'utente con `codiceFiscale` e l'auto con `targa` nel periodo specificato.
 * Stampa sul file `output_fp` il risultato della prenotazione (successo o fallimento).
 * -----------------------------
 */
void eseguiPrenotazioneSimulata(Lista prenotazioni, UtentiHashTB tabUtenti, AutoHashTB tabAuto, int g_inizio, int g_fine, int ora_inizio, int ora_fine, char*targa, char*CF, FILE *output_fp) {
    int stato = 1;  // Flag che segnala se la prenotazione è riuscita o no
    Utente u = cercaUtente(tabUtenti, CF);
    if (!u) {
        fprintf(output_fp,  "Utente non trovato!\n");
        return; // Se l'utente non esiste, termina la funzione
    }
    Auto a = cercaAuto(tabAuto, targa);
    if (!a) {
        fprintf(output_fp, "Auto non trovata!\n");
    } // Non fa il return per gestire eventuale output

    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, ottieniCF(u), ottieniTarga(a), &g_inizio, &g_fine, &ora_inizio, &ora_fine, &stato);

    // Controlla se la prenotazione esiste
    if (prenotazioni == NULL) {
        fprintf(output_fp, "Prenotazione non riuscita.\n");
    } else {
        if(stato){
            Prenotazione p = ottieniPrimo(prenotazioni);
            stampaPrenotazioneSuFile(p, output_fp);
        }
    }
}

/*
 * Funzione: eseguiCalcoloCostoSimulato
 * -----------------------------
 * Parametri:
 * - `tabUtenti`: tabella hash contenente gli utenti registrati.
 * - `tabAuto`: tabella hash contenente le auto registrate.
 * - `prenotazioni`: lista contenente le prenotazioni effettuate.
 * - `output_fp`: puntatore a file su cui scrivere il costo totale per utente.
 * -----------------------------
 * Precondizioni:
 * - Le strutture `tabUtenti`, `tabAuto` e `prenotazioni` devono essere valide.
 * - `output_fp` deve essere un file aperto in modalità scrittura.
 * -----------------------------
 * Postcondizioni:
 * Calcola e scrive nel file il costo totale delle prenotazioni per ciascun utente distinto.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
 * La funzione calcola il costo totale di noleggio per ogni prenotazione nella lista,
 * usando le informazioni contenute in tabUtenti e tabAuto. Per ogni prenotazione,
 * scrive sul file di output il costo calcolato formattato in modo leggibile.
 * ---------------------------
 */
void eseguiCalcoloCostoSimulato(UtentiHashTB tabUtenti, AutoHashTB tabAuto, Lista prenotazioni, FILE *output_fp) {
    for (Lista p = prenotazioni; !ListaVuota(p); p = codaLista(p)) {
        Prenotazione prCorrente = ottieniPrimo(p);
        const char* CF = ottieniCFPrenotazione(prCorrente);

        // Controlla se abbiamo già stampato per questo CF (scorri i nodi precedenti)
        int giaStampato = 0;
        for (Lista q = prenotazioni; q != p; q = codaLista(q)) {
            if (strcmp(ottieniCFPrenotazione(ottieniPrimo(q)), CF) == 0) {
                giaStampato = 1;
                break;
            }
        }

        if (!giaStampato) {
            // Filtra solo le prenotazioni per questo CF
            Lista soloUtente = filtraPrenotazioniPerCF(prenotazioni, CF);

            // Cerca l’utente
            Utente u = cercaUtente(tabUtenti, CF);
            if (!u) {
                fprintf(output_fp, "Utente con CF %s non trovato.\n", CF);
                distruggiLista(soloUtente);
                continue;
            }

            // Calcola costo totale delle sue prenotazioni
            float costoTotale = calcolaPrezziPrenotazioni(soloUtente, u, tabAuto);

            // Stampa il risultato
            fprintf(output_fp, "Costo totale per %s %s (%s): %.2f €\n",
                ottieniNome(u), ottieniCognome(u), CF, costoTotale);

            distruggiLista(soloUtente);  // Pulizia memoria temporanea
        }
    }
}

/*
 * Funzione: eseguiCasoDiTest
 * -----------------------------
 * Parametri:
 * - `tc_id`: stringa che identifica il caso di test (es. "TC01").
 * - `tipo_di_test`: stringa che indica il tipo di test da eseguire. Valori validi: "PRENOTA", "CALCOLO", "VISUALIZZA", "STORICO".
 * -----------------------------
 * Precondizioni:
 * - `tc_id` e `tipo_di_test` devono essere stringhe valide non NULL.
 * - Devono esistere i file:
 *     - "test/<tc_id>/<tc_id>_input.txt" contenente i dati di input;
 *     - "test/<tc_id>/<tc_id>_oracle.txt" contenente l’output atteso.
 * -----------------------------
 * Postcondizioni:
 * Esegue un caso di test automatizzato:
 *   - Carica dati di test per utenti e auto.
 *   - Esegue operazioni simulate a seconda del tipo di test (`tipo_di_test`):
 *       - "PRENOTA": effettua prenotazioni simulate e scrive i risultati.
 *       - "CALCOLO": carica prenotazioni da file e calcola il costo complessivo.
 *       - "VISUALIZZA": stampa la disponibilità delle auto in un certo intervallo.
 *       - "STORICO": aggiorna e stampa lo storico prenotazioni degli utenti.
 *   - Confronta riga per riga l'output ottenuto con il file oracle.
 *   - Libera tutta la memoria dinamica allocata.
 * -----------------------------
 * Restituisce:
 * - `1` se il test ha avuto successo (output identico all’oracolo).
 * - `0` in caso di errore o discrepanze tra output e oracolo.
 * -----------------------------
 * La funzione apre i file di input, output e oracle corrispondenti al test specificato,
 * carica dati iniziali di utenti e auto, esegue operazioni di test in base al tipo,
 * scrive i risultati su file, confronta l'output generato con l'oracle e restituisce
 * il risultato del confronto.
 * -----------------------------
 */
int eseguiCasoDiTest(char *tc_id, char *tipo_di_test) {
    char input_fnome[M], output_fnome[M], oracle_fname[M];
    int stato = 0;
    char line[256];
    char codiceFiscale[17];  // 16 + 1 per '\0'
    char targa[8];


    // Costruisce i nomi completi dei file input, output e oracle per il test corrente
    snprintf(input_fnome, M,  "test/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fnome, M, "test/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, M, "test/%s/%s_oracle.txt", tc_id, tc_id);

    // Apre i file input in lettura, output in scrittura e oracle in lettura
    FILE *input_fp = fopen(input_fnome, "r");
    FILE *output_fp = fopen(output_fnome, "w");
    FILE *oracle_fp = fopen(oracle_fname, "r");

    // Controllo apertura file, chiude eventuali file aperti se uno fallisce
    if (!input_fp || !output_fp || !oracle_fp) {
        printf(ROSSO "Errore apertura file: %s, %s o %s\n" RESET, input_fnome, output_fnome, oracle_fname);
        if (input_fp) fclose(input_fp);
        if (output_fp) fclose(output_fp);
        if (oracle_fp) fclose(oracle_fp);
        return 0;
    }

    // Inizializza le strutture dati
    UtentiHashTB tabUtenti = nuovaHashTBUtenti();
    AutoHashTB tabAuto = creaAutoHashTB();
    Lista prenotazioni = nuovaLista();

    caricaUtentiTest(&tabUtenti);
    caricaAutoTest(&tabAuto);

    // Caso di test "PRENOTA": simula prenotazioni leggendo input e chiamando eseguiPrenotazioneSimulata
    if (strcmp(tipo_di_test, "PRENOTA") == 0) {
        while (fgets(line, sizeof(line), input_fp)) {
            line[strcspn(line, "\n")] = '\0';

            int g1, g2, o1, o2;

            // Tenta di leggere 4 interi + 2 stringhe
            if (sscanf(line, "%d %d %d %d %16s %7s", &g1, &g2, &o1, &o2, codiceFiscale, targa) == 6) {
                codiceFiscale[strcspn(codiceFiscale, "\n")] = '\0';
                targa[strcspn(targa, "\n")] = '\0';
                // Esegue la prenotazione simulata e scrive su output
                eseguiPrenotazioneSimulata(prenotazioni, tabUtenti, tabAuto, g1, g2, o1, o2, targa, codiceFiscale, output_fp);
            } else {
                fprintf(output_fp, "Riga input ignorata (formato non valido): %s\n", line);
            }
        }
        // Caso "CALCOLO": carica prenotazioni e poi esegue calcolo costi, scrivendo su output
    } else if (strcmp(tipo_di_test, "CALCOLO") == 0) {
        while (fgets(line, sizeof(line), input_fp)) {
            line[strcspn(line, "\n")] = '\0';

            int g1, g2, o1, o2;
            if (sscanf(line, "%d %d %d %d %16s %7s", &g1, &g2, &o1, &o2, codiceFiscale, targa) == 6) {
                prenotazioni = caricaPrenotazioni(prenotazioni, g1, g2, o1, o2, codiceFiscale, targa);
            } else {
                fprintf(output_fp, "Riga input ignorata (formato non valido): %s\n", line);
            }
        }

        eseguiCalcoloCostoSimulato(tabUtenti, tabAuto, prenotazioni, output_fp);

        distruggiLista(prenotazioni);
        // Caso "VISUALIZZA": mostra disponibilità auto per intervallo richiesto
    } else if (strcmp(tipo_di_test, "VISUALIZZA") == 0) {
        while (fgets(line, sizeof(line), input_fp)) {
            line[strcspn(line, "\n")] = '\0';

            int g1, g2, o1, o2;
            if (sscanf(line, "%d %d %d %d", &g1, &g2, &o1, &o2) == 4) {
                // Caso speciale per TC15: aggiunge prenotazioni manuali
                if (strcmp(input_fnome, "test/TC15/TC15_input.txt") == 0) {
                    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, "DNTCRL65S67M126L" , "AB123CD", &g1, &g2, &o1, &o2, &stato);
                    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, "SRRLKR05T21F912R", "AA555BB", &g1, &g2, &o1, &o2, &stato);
                    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, "NLOBTL90A11G230C", "CC777NN", &g1, &g2, &o1, &o2, &stato);
                    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, "NLOBTL90A11G230C", "BB222RR", &g1, &g2, &o1, &o2, &stato);
                    prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, "DNTCRL65S67M126L", "VV444XX", &g1, &g2, &o1, &o2, &stato);
                }
                stampaTabellaDiHashPerDispFile(tabAuto, g1, g2,o1, o2, output_fp);
            } else {
                fprintf(output_fp, "Riga input ignorata (formato non valido): %s\n", line);
            }
        }
        // Caso "STORICO": stampa storico prenotazioni, eventualmente filtrato per utente e auto
    } else if (strcmp(tipo_di_test, "STORICO") == 0) {
        while (fgets(line, sizeof(line), input_fp)) {
            line[strcspn(line, "\n")] = '\0';

            // Caso speciale: "nessun dato" indica di stampare tutto lo storico
            if (strcmp(line, "nessun dato") == 0) {

                stampaStoricoTuttiUtentiSuFile(tabUtenti, output_fp);
                return 1;
            }


            int g1, g2, o1, o2;

            if (sscanf(line, "%d %d %d %d %16s %7s", &g1, &g2, &o1, &o2, codiceFiscale, targa) == 6) {
                Utente u = cercaUtente(tabUtenti, codiceFiscale);
                if (!u) {
                    fprintf(output_fp, "Utente con CF %s non trovato!\n", codiceFiscale);
                    continue;
                }

                // Tenta prenotazzione e aggiunge stato
                prenotazioni = prenotazioneAuto(prenotazioni, tabAuto, codiceFiscale, targa, &g1, &g2, &o1, &o2, &stato);
                if (!stato) {
                    fprintf(output_fp, "Prenotazione non riuscita per %s - %s\n", codiceFiscale, targa);
                    continue;
                }

                // Aggiunge prenotazioni a storico utenti e resetta disponibilità auto
                aggiungiPrenotazioniAStoricoUtenti(tabUtenti, prenotazioni);
                reimpostaDisponibilitaTutteLeAuto(tabAuto);
                distruggiLista(prenotazioni);
                prenotazioni = nuovaLista();
            } else {
                fprintf(output_fp, "Riga input ignorata (formato non valido): %s\n", line);
            }
        }

        // Dopo aver elaborato tutte le righe, stampa lo storico completo
        stampaStoricoTuttiUtentiSuFile(tabUtenti, output_fp);
    }
    else {
        fprintf(output_fp, "Tipo test non supportato: %s\n", tipo_di_test);
    }



    fclose(input_fp);
    fclose(output_fp);

    // Ora riapri output in lettura per il confronto
    output_fp = fopen(output_fnome, "r");
    if (!output_fp) {
        printf(ROSSO "Errore apertura file output in lettura: %s\n" RESET, output_fnome);
        fclose(oracle_fp);
        return 0;
    }

    // Confronto riga per riga
    char r1[256], r2[256];
    int pass = 1;   // Flag che indica se passa o no
    while (1) {
        char *out_line = fgets(r1, sizeof(r1), output_fp);
        char *orc_line = fgets(r2, sizeof(r2), oracle_fp);

        if (!out_line && !orc_line) {
            // entrambi EOF test passati
            break;
        }
        if (!out_line || !orc_line || strcmp(r1, r2) != 0) {
            pass = 0;   // Test fallito
            break;
        }
    }

    fclose(output_fp);
    fclose(oracle_fp);

    distruggiLista(prenotazioni);
    distruggiAutoHashTB(&tabAuto);
    distruggiHashTBUtenti(&tabUtenti);

    return pass;
}

/*
 * Funzione: esegui_test_suite
 * -----------------------------
 * Parametri:
 * - `suite_file`: nome del file contenente l’elenco dei test case da eseguire.
 * - `result_file`: nome del file su cui scrivere i risultati (PASS/FAIL) di ogni test.
 * -----------------------------
 * Precondizioni:
 * - I file "test/<suite_file>" e "test/<result_file>" devono essere nomi validi.
 * - Il file suite deve esistere e contenere righe nel formato: <tc_id> <tipo_di_test>
 * -----------------------------
 * Postcondizioni:
<<<<<<< Updated upstream
=======
 * - nessuno.
 * -----------------------------
 * Side effect:
>>>>>>> Stashed changes
 * - Esegue in sequenza tutti i casi di test indicati nel file di suite.
 * - Scrive su standard output l’esito (PASS/FAIL) di ciascun test.
 * - Scrive su `result_file` l’esito dettagliato dei test.
 * -----------------------------
 * Restituisce:
 * Nessuno.
 * -----------------------------
 * La funzione costruisce i percorsi completi aggiungendo la cartella "test/" ai nomi dei file,
 * apre il file della suite in lettura e il file dei risultati in scrittura.
 * Per ogni riga della suite, che deve contenere un ID test e un tipo di test,
 * richiama la funzione eseguiCasoDiTest per eseguire il test,
 * stampa a video l’esito (PASS o FAIL) e lo scrive nel file dei risultati.
 */
void esegui_test_suite(const char *suite_file, const char *result_file) {
    char path_suite[M];
    char path_result[M];

    // Costruisce il percorso completo per il file passato come parametro
    snprintf(path_suite, M, "test/%s", suite_file);
    snprintf(path_result, M, "test/%s", result_file);

    FILE *suite = fopen(path_suite, "r");   // Apre il file della suite in letture
    FILE *result = fopen(path_result, "w"); // Apre il file dei risultati in scrittura


    // Controlla se i file sono stati aperti correttamente
    if (suite == NULL || result == NULL) {
        printf(ROSSO "Errore apertura test suite o risultati\n" RESET);
        return;
    }

    char tc_id[M], tipo_di_test[M];
    // Legge ogni riga del file
    while (fscanf(suite, "%s %s", tc_id, tipo_di_test) == 2) {
        int pass = eseguiCasoDiTest(tc_id, tipo_di_test);   // Esegue il test
        printf("%s [%s]: %s\n", tc_id, tipo_di_test, pass ? VERDE "PASS" RESET : ROSSO "FAIL" RESET);    // Stampa a video l'esito del test
        fprintf(result, "%s - %s - %s\n", tc_id, tipo_di_test, pass ? "PASS" : "FAIL");  // Scrive sul file il risultato
    }

    fclose(suite);
    fclose(result);
}

/*
 * Funzione: main
 * -----------------------------
 * Parametri:
 * - `argc`: variabile intera che contiene il numero dei parametri passati alla funzione.
 * - `argv[]`: nome del programma e del file risultati.txt e test_suite.txt.
 * -----------------------------
 * Precondizioni:
 * - argc deve essere diverso da 3.
 * - argv[] deve contenere 3 stringhe.
 * -----------------------------
 * Postcondizioni:
 * - la funzione fa tornare il valore 0 se è andato tutto a buon fine.
 * -----------------------------
 * Side effect:
 * - Nessuno
 * -----------------------------
 * Restituisce:
 * valore intero: 0.
 * -----------------------------
 * main chiama la funzione esegui_test_suite in modo tale da far partire
 * tutti i casi di test.
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf(ROSSO "Uso corretto: %s <file_suite> <file_risultati>\n" RESET, argv[0]);
        return 1;
    }

    esegui_test_suite(argv[1], argv[2]);
    return 0;
}
