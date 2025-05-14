//
// Created by extra on 14/05/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "Utile_DevMenu.h"
#include "HashTbUtenti.h"
void InputAuto(HashTable *h) {
    char targa[10], marca[20], modello[20];
    int anno;
    float prezzo;
    Auto a = NULL;
    printf("Inserisci la targa dell'auto: ");
    scanf("%s", targa);
    printf("Inserisci la marca dell'auto: ");
    scanf("%s", marca);
    printf("Inserisci il modello dell'auto: ");
    scanf("%s", modello);
    printf("Inserisci l'anno dell'auto: ");
    scanf("%d", &anno);
    printf("Inserisci il prezzo per ora dell'auto: ");
    scanf("%f", &prezzoXOra);

    a = creaAuto(targa, marca, modello, anno, prezzo);
    if (a == NULL) {
        printf("Errore nella creazione dell'auto.\n");
        return;
    }
    insertAuto(h, a);
    printf("Auto inserita con successo.\n");
}

void switchDeveloper(int scelta, HashTable *h) {
    switch(scelta) {
        case 1:
            inputAuto(h);
            stampaHashTable(*h);
        break;
        case 2:
            printf("Eliminazione auto...\n");
        break;
        case 3:
            printf("Visualizza prenotazioni di tutti gli utenti...\n");
        break;
        case 4:
            printf("Visualizza storico prenotazioni...\n");
        break;
        case 5:
            printf("Uscita...\n");
        exit(0);
        default:
            printf("Opzione non valida. Riprova.\n");
        break;
    }
}

int menuDeveloper() {
    int scelta;
    printf("\n========== Car Sharing - Developer Menu ==========\n");
    printf("1. Aggiungi auto\n");
    printf("2. Elimina auto\n");
    printf("3. Visualizza prenotazioni\n");
    printf("4. Visualizza prenotazioni precedenti\n");
    printf("5. Esci\n");
    printf("==================================\n");
    scanf("%d", &scelta);
    return scelta;
}

int sceltaUtenteDeveloper() {
    int scelta;
    do {
        printf("Clicca la corripettiva opzione per scegliere il ruolo:\n");
        printf("1. Utente\n");
        printf("2. Developer\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
    } while (scelta != 1 && scelta != 2);
    return scelta;
}

