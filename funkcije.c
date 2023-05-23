#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"

struct Parfem skladiste[MAX_PARFEMA];
int brojParfema = 0;

void kreirajDatoteku(const char* imeDatoteke) {
    FILE* datoteka = fopen(imeDatoteke, "w");

    if (datoteka == NULL) {
        printf("Greška pri otvaranju datoteke.\n");
        return;
    }

    for (int i = 0; i < brojParfema; i++) {
        fprintf(datoteka, "Naziv: %s\n", skladiste[i].naziv);
        fprintf(datoteka, "Marka: %s\n", skladiste[i].marka);
        fprintf(datoteka, "Cijena: %.2f\n", skladiste[i].cijena);
        fprintf(datoteka, "Miris: %s\n", skladiste[i].miris);
        fprintf(datoteka, "Koli?ina: %d\n\n", skladiste[i].kolicina);
    }

    fclose(datoteka);

    printf("Podaci o parfemima uspješno spremljeni u datoteku '%s'.\n", imeDatoteke);
}

void provjeriKreirajDatoteku(const char* imeDatoteke) {
    FILE* datoteka = fopen(imeDatoteke, "r");
    if (datoteka == NULL) {
        kreirajDatoteku(imeDatoteke);
    }
    else {
        fclose(datoteka);
    }
}


void dodajParfem() {
    if (brojParfema >= MAX_PARFEMA) {
        printf("Skladiste parfema je puno. Nije moguce dodati vise parfema.\n");
        return;
    }

    struct Parfem noviParfem;

    printf("Unesite naziv parfema: ");
    scanf("%s", noviParfem.naziv);

    printf("Unesite marku parfema: ");
    scanf("%s", noviParfem.marka);

    printf("Unesite cijenu parfema: ");
    scanf("%f", &noviParfem.cijena);

    printf("Unesite miris parfema: ");
    scanf("%s", noviParfem.miris);

    printf("Unesite kolicinu parfema: ");
    scanf("%d", &noviParfem.kolicina);

    skladiste[brojParfema++] = noviParfem;

    printf("Parfem uspjesno dodan u skladiste.\n");
}

void spremiPodatkeUDatoteku(const char* imeDatoteke) {
    FILE* datoteka = fopen(imeDatoteke, "w");

    if (datoteka == NULL) {
        printf("Greška pri otvaranju datoteke.\n");
        return;
    }

    for (int i = 0; i < brojParfema; i++) {
        fprintf(datoteka, "Naziv: %s\n", skladiste[i].naziv);
        fprintf(datoteka, "Marka: %s\n", skladiste[i].marka);
        fprintf(datoteka, "Cijena: %.2f\n", skladiste[i].cijena);
        fprintf(datoteka, "Miris: %s\n", skladiste[i].miris);
        fprintf(datoteka, "Koli?ina: %d\n\n", skladiste[i].kolicina);
    }

    fclose(datoteka);

    printf("Podaci o parfemima uspješno spremljeni u datoteku '%s'.\n", imeDatoteke);
}

void ispisiParfeme() {
    if (brojParfema == 0) {
        printf("Skladiste parfema je prazno.\n");
        return;
    }

    printf("Popis parfema:\n");
    printf("---------------------------\n");

    for (int i = 0; i < brojParfema; i++) {
        printf("Parfem %d:\n", i + 1);
        printf("Naziv: %s\n", skladiste[i].naziv);
        printf("Marka: %s\n", skladiste[i].marka);
        printf("Cijena: %.2f\n", skladiste[i].cijena);
        printf("Miris: %s\n", skladiste[i].miris);
        printf("Kolicina: %d\n", skladiste[i].kolicina);
        printf("---------------------------\n");
    }
}

