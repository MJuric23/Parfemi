#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

int main() {
    const char* datoteka = "skladiste_parfema.bin";
    int opcija;

    do {
        printf("\t\t----------------------------------------\n\n");
        printf("\t\tOdaberite opciju: \n\n");
        printf("\t\t\n\n");
        printf("\t\tOpcija 1: Dodavanje parfema\n");
        printf("\t\tOpcija 2: Ispis podataka o parfemu\n");
        printf("\t\tOpcija 3: Sortiranje po cijeni parfema\n");
        printf("\t\tOpcija 4: Pretraga parfema\n");
        printf("\t\tOpcija 5: Ažuriranje parfema\n");
        printf("\t\tOpcija 6: Brisanje parfema\n");
        printf("\t\tOpcija 7: Izlaz iz programa\n");
        printf("\t\t----------------------------------------\n\n");
        printf("Unesite opciju: ");
        scanf("%d", &opcija);

        switch (opcija) {
        case 1:
            dodajParfem(datoteka);
            break;
        case 2:
            ispisiPodatke(datoteka);
            break;
        case 3:
            //sortirajPoCijeni(datoteka);
            break;
        case 4:
            //pretraziParfem(datoteka);
            break;
        case 5:
            //azurirajParfem(datoteka);
            break;
        case 6:
            //obrisiParfem(datoteka);
            break;
        case 7:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Neispravna opcija. Pokušajte ponovno.\n");
            break;
        }

        printf("\n");
    } while (opcija != 7);

    return 0;
}
