#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

void kreiranjeDatoteke(const char* const ime) {
    FILE* fp = fopen(ime, "rb");

   
    if (fp == NULL) {
        fclose(fp);
        fp = fopen(ime, "wb");

        int brojParfema = 0; 

        fwrite(&brojParfema, sizeof(int), 1, fp);

        fclose(fp);
    }
    else {
        fclose(fp);
    }
}
void dodajParfem(const char* const ime) {
    FILE* fp = fopen(ime, "rb+");

    if (fp == NULL) {
        perror("Dodavanje parfema u datoteku");
        exit(EXIT_FAILURE);
    }

    int brojParfema=0;
    fread(&brojParfema, sizeof(int), 1, fp);
    printf("Broj parfema: %d\n\n", brojParfema);

    Parfem noviParfem;
    noviParfem.id = brojParfema + 1;

    printf("Unesite naziv parfema: ");
    scanf("%49s", noviParfem.naziv);

    printf("Unesite proizvodjaca parfema: ");
    scanf("%49s", noviParfem.proizvodjac);

    printf("Unesite cijenu parfema: ");
    scanf("%f", &noviParfem.cijena);

    printf("Unesite kolicinu parfema: ");
    scanf("%d", &noviParfem.kolicina);

    fseek(fp, sizeof(int), SEEK_SET);  
    fwrite(&noviParfem, sizeof(Parfem), 1, fp);
    printf("Novi parfem dodan.\n\n");

    rewind(fp);
    brojParfema++;

    fwrite(&brojParfema, sizeof(int), 1, fp);

    fclose(fp);
}

void ispisiPodatke(const char* const ime) {
    FILE* fp = fopen(ime, "rb");

    if (fp == NULL) {
        perror("Otvaranje datoteke za ispis podataka");
        exit(EXIT_FAILURE);
    }

    int brojParfema;
    fread(&brojParfema, sizeof(int), 1, fp);

    printf("Broj parfema: %d\n\n", brojParfema);

    printf("------ Podaci o parfemima ------\n");

    for (int i = 0; i < brojParfema; i++) {
        Parfem parfem;

        fread(&parfem, sizeof(Parfem), 1, fp);

        printf("ID: %d\n", parfem.id);
        printf("Naziv: %s\n", parfem.naziv);
        printf("Proizvo?a?: %s\n", parfem.proizvodjac);
        printf("Cijena: %.2f\n", parfem.cijena);
        printf("Koli?ina: %d\n", parfem.kolicina);
        printf("-----------------------------\n");
    }

    fclose(fp);
}



