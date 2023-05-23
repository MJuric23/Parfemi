#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"


int izbornik() {
    printf("\t\t----------------------------------------\n\n");
    printf("\t\tOdaberite opciju: \n\n");
    printf("\t\t\n\n");

    printf("\t\tOpcija 1: Dodavanje parfema\n");
    printf("\t\tOpcija 2: Ispisi podatke o parfemu\n");
    printf("\t\tOpcija 3: Sortiraj po cijeni parfema\n");
    printf("\t\tOpcija 4: Pretrazivanje parfema po \n");
    printf("\t\tOpcija 5: Azuriraj parfem!\n");
    printf("\t\tOpcija 6: Obrisi parfem!\n");
    printf("\t\tOpcija 7: Izlaz iz programa\n");

    printf("\t\t----------------------------------------\n\n");

    int odabir;
    printf("Unesite broj opcije: ");
    scanf("%d", &odabir);

    switch (odabir) {
    case 1:
        dodajParfem();
        break;
    case 2:
        ispisiParfeme();
        break;
    case 3:
        // Logika za sortiranje parfema po cijeni
        break;
    case 4:
        // Logika za pretraživanje parfema
        break;
    case 5:
        // Logika za ažuriranje parfema
        break;
    case 6:
        // Logika za brisanje parfema
        break;
    case 7:
        printf("Izlaz iz programa.\n");
        break;
    default:
        printf("Pogresan odabir. Molimo odaberite valjanu opciju.\n");
        break;
    }

    return 0;
}