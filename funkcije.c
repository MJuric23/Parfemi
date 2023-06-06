#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojParfema = 0;
static int i;
static int j;
static int br = 0;

int izbornik() {
	int uvijet = 0;
	static PARFEM* polje = NULL;

	printf("Odaberite jednu od opcija.");
	printf("\n***************************\n");
	printf("Opcija 1: Dodaj parfem\n");
	printf("Opcija 2: Azuriranje parfema\n");
	printf("Opcija 3: Ispisivanje parfema\n");
	printf("Opcija 4: Pretrazivanje parfema\n");
	printf("Opcija 5: Sortiranje parfema\n");
	printf("Opcija 6: Brisanje parfema\n");
	printf("Opcija 7: Izlaz iz programa\n");
	printf("***************************\n");

	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1:	ucitavanjeParfema();
		if (brojParfema == 0) {
			kreiranjeDat();
		}
		dodavanjePar();
		break;

	case 2: azuriranje(); break;

	case 3: if (polje != NULL) {
		free(polje);
		polje = NULL;
	}
		  polje = (PARFEM*)ucitavanjeParfema();
		  ispisivanje(polje);
		  break;

	case 4:
		while (uvijet != 90) {
			uvijet = izbornikPret();
		}
		break;

	case 5: while (uvijet != 89)
		uvijet = izbornikSort();
		break;

	case 6: if (polje == NULL)
		printf("Nema unesenih parfema\n\n");
		  else
		brisanjePar(polje);
		break;

	case 7:
		printf("Zelite li izaci iz programa? (da/ne)\n");
		char odgovor[3] = { '\0' };
		scanf("%2s", odgovor);
		if (strcmp("da", odgovor) == 0) {
			free(polje);
			return 99;

		}
		break;

	default:
		printf("\nPogresan unos!\n\n");
	}

	return uvijet;
}

int izbornikPret() {
	int uvijet = 0;
	PARFEM* polje = NULL;
	polje = (PARFEM*)ucitavanjeParfema();
	printf("Pretrazivanje.\n\n");
	printf("Opcija 1: Cijena\n");
	printf("Opcija 2: Spol\n");
	printf("Opcija 3: Ime\n");
	printf("Opcija 4: Povratak\n");
	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1: pretragaCijena(polje); break;
	case 2: pretragaSpol(polje); break;
	case 3:	pretragaIme(polje); break;
	case 4: return 90;
	default: printf("\nPogresan unos!\n");

	}

	return uvijet;
}

int izbornikSort() {
	int uvijet = 0;
	PARFEM* polje = NULL;
	polje = (PARFEM*)ucitavanjeParfema();
	printf("Sortiranje.\n\n");
	printf("Opcija 1: Cijena od najjeftinijeg do najskupljeg\n");
	printf("Opcija 2: Cijena od najskupljeg do najjeftinijeg\n");
	printf("Opcija 3: Povratak\n");
	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1: selectionSortNajjefCijena(polje); break;
	case 2: selectionSortNajskupCijena(polje); break;
	case 3: return 89;
	default: printf("\nPogresan unos!\n");

	}

	return uvijet;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("parfemi.bin", "wb");

	if (fp == NULL) {
		perror("Kreiranje");
	}
	else {
		fwrite(&brojParfema, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void dodavanjePar() {
	FILE* fp = NULL;
	fp = fopen("parfemi.bin", "rb+");

	if (fp == NULL) {
		perror("Dodavanje");
		exit(1);
	}

	fread(&brojParfema, sizeof(int), 1, fp);
	printf("Trenutni broj parfema: %d", brojParfema);

	PARFEM parfemi;
	parfemi.id = brojParfema + 1;
	br++;
	getchar();
	printf("\nUnesite spol parfema: ");
	scanf("%24[^\n]", parfemi.spol);
	getchar();
	printf("\nUnesite ime parfema: ");
	scanf("%24[^\n]", parfemi.ime);
	printf("\nUnesite cijenu parfema: ");
	scanf("%d", &parfemi.cijena);
	printf("\nUnesite kolicinu parfema: ");
	scanf("%d", &parfemi.kolicina);
	fseek(fp, sizeof(PARFEM) * brojParfema, SEEK_CUR);
	fwrite(&parfemi, sizeof(PARFEM), 1, fp);
	rewind(fp);
	brojParfema++;
	fwrite(&brojParfema, sizeof(int), 1, fp);
	fclose(fp);
}

void azuriranje() {
	FILE* fp = NULL;
	int ispravak;
	fp = fopen("parfemi.bin", "rb+");
	if (fp == NULL)
		printf("Nema unesenih parfema\n\n");
	else {
		printf("Unesi broj parfema koji zelite ispraviti.\n");
		scanf("%d", &ispravak);
		fseek(fp, sizeof(int) + (sizeof(PARFEM) * (ispravak - 1)), SEEK_SET);
		PARFEM ispravljenParfem;
		ispravljenParfem.id = ispravak;
		getchar();
		printf("\nUnesite ispravljeni spol parfema: ");
		scanf("%24[^\n]", ispravljenParfem.spol);
		getchar();
		printf("\nUnesite ime parfema: ");
		scanf("%24[^\n]", ispravljenParfem.ime);
		printf("\nUnesite cijenu parfema: ");
		scanf("%d", &ispravljenParfem.cijena);
		printf("\nUnesite kolicinu parfema: ");
		scanf("%d", &ispravljenParfem.kolicina);
		fwrite(&ispravljenParfem, sizeof(PARFEM), 1, fp);
		rewind(fp);
		fwrite(&brojParfema, sizeof(int), 1, fp);
		fclose(fp);

	}
}

void* ucitavanjeParfema() {
	FILE* fp = fopen("parfemi.bin", "rb");
	if (fp == NULL) {
		printf("Nema unesenih parfema\n\n");
		return NULL;
	}
	fread(&brojParfema, sizeof(int), 1, fp);
	PARFEM* polje = NULL;
	polje = (PARFEM*)calloc(brojParfema, sizeof(PARFEM));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(PARFEM), brojParfema, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(PARFEM* polje) {
	for (i = 0; i < brojParfema; i++)
	{
		printf("Parfem broj %d:\tID: %d\tspol: %s\tIme: %s\tCijena:  %d\tKolicina: %d\n", i + 1, (polje + i)->id, (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
	}
}

void* pretragaIme(PARFEM* polje) {
	char trazenoIme[25] = { 0 };
	int brojac = 0;

	printf("Upisite ime parfema koje zelite pronaci.\n");
	getchar();
	scanf("%24[^\n]", trazenoIme);

	for (i = 0; i < brojParfema; i++) {
		if (!strcmp(trazenoIme, (polje + i)->ime)) {
			printf("\nIme parfema je pronadeno!\n\n");
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nIme parfema nije pronadeno!\n\n");
	return NULL;
}

void* pretragaSpol(PARFEM* polje) {
	char trazenaSpol[25] = { 0 };
	int brojac = 0;

	printf("Upisite spol (Muski/Zenski/Unisex) koju zelite pronaci.\n");
	getchar();
	scanf("%24[^\n]", trazenaSpol);

	for (i = 0; i < brojParfema; i++) {
		if (!strcmp(trazenaSpol, (polje + i)->spol)) {
			printf("\npronadeno!\n\n");
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nnije pronadeno!\n\n");
	return NULL;
}

void* pretragaCijena(PARFEM* polje) {
	int trazenaCijena;
	int brojac = 0;

	printf("Upisite cijenu parfema koju zelite pronaci.\n");
	scanf("%d", &trazenaCijena);

	for (i = 0; i < brojParfema; i++) {
		if (trazenaCijena == (polje + i)->cijena) {
			printf("\nCijena parfema je pronadena!\n\n");
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nCijena parfema nije pronadena!\n\n");
	return NULL;
}

void zamjena(PARFEM* veci, PARFEM* manji) {
	PARFEM temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortNajjefCijena(PARFEM* polje) {
	int min = -1;
	printf("Sortirani parfemi po cijeni od najjeftinijeg do najskupljeg.\n");
	for (i = 0; i < brojParfema - 1; i++)
	{
		min = i;
		for (j = i + 1; j < brojParfema; j++)
		{
			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	for (i = 0; i < brojParfema; i++)
	{
		if (i == 0) {
			printf("Spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else if (i > 0 && i < brojParfema - 1) {
			printf("Spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else {
			printf("Spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
	}
	printf("\n");
}

void selectionSortNajskupCijena(PARFEM* polje) {
	int min = -1;
	printf("Sortirani parfemi po cijeni od najskupljeg do najjeftinijeg.\n");
	for (i = 0; i < brojParfema - 1; i++)
	{
		min = i;
		for (j = i + 1; j < brojParfema; j++)
		{
			if ((polje + j)->cijena > (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	for (i = 0; i < brojParfema; i++)
	{
		if (i == 0) {
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else if (i > 0 && i < brojParfema - 1) {
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else {
			printf("spol: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->spol, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
	}
	printf("\n");
}

void brisanjePar(PARFEM* polje) {
	FILE* fp = NULL;
	fp = fopen("parfemi.bin", "wb");
	if (fp == NULL) {
		perror("  Brisanje parfema");
		exit(1);
	}

	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int brojac = 0;
	int trazeniPar;

	printf("\nUnesi ID parfema koji zelite obrisati\n");
	scanf("%d", &trazeniPar);

	for (i = 0; i < brojParfema; i++) {
		if (trazeniPar != (polje + i)->id) {
			fwrite((polje + i), sizeof(PARFEM), 1, fp);
			brojac++;
		}
	}
	rewind(fp);
	fwrite(&brojac, sizeof(int), 1, fp);
	fclose(fp);
}

