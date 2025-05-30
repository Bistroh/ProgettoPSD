#ifndef TEST_H
#define TEST_H
#include "List_Prenotazione.h"
#include "HashTbUtenti.h"
#include "HashTbAuto.h"
#include <stdio.h>



int run_test_case(char *tc_id, char *test_type);
void eseguiPrenotazioneSimulata(Lista prenotazioni, UtentiHashTB tabUtenti, AutoHashTB tabAuto, int g_inizio, int g_fine, int ora_inizio, int ora_fine, char*targa, char*CF, FILE *output_fp);
void caricaUtentiTest(UtentiHashTB *tabUtenti);
void caricaAutoTest(AutoHashTB *tabAuto);
void eseguiDisponibilitaSimulata(AutoHashTB tabAuto, const char* targa, int g_inizio, int g_fine, int ora_inizio, int ora_fine);
void eseguiCalcoloCostoSimulato(UtentiHashTB tabUtenti, AutoHashTB tabAuto, Lista prenotazioni, char * CF, FILE *output_fp);
void eseguiVisualizzaStoricoSimulato(UtentiHashTB tabUtenti, Lista prenotazioni, AutoHashTB tabAuto);


#endif //TEST_H
