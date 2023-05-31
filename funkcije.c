#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojArtikala = 0;
static int i;
static int j;
static int br = 0;

int izbornik() {
	int uvijet = 0;
	static ARTIKL* polje = NULL;

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
	case 1:	ucitavanjeArtikala();
		if (brojArtikala == 0) {
			kreiranjeDat();
		}
		dodavanjeArt();
		break;

	case 2: azuriranje(); break;

	case 3: if (polje != NULL) {
		free(polje);
		polje = NULL;
	}
		  polje = (ARTIKL*)ucitavanjeArtikala();
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
		printf("Nema unesenih artikala\n\n");
		  else
		brisanjeArt(polje);
		break;

	case 7: brisanjeDat(polje);
		return 99;
		break;
	default: printf("\nPogresan unos!\n\n");
	}

	return uvijet;
}

int izbornikPret() {
	int uvijet = 0;
	ARTIKL* polje = NULL;
	polje = (ARTIKL*)ucitavanjeArtikala();
	printf("Pretrazivanje.\n\n");
	printf("Opcija 1: Cijena\n");
	printf("Opcija 2: Kategorija\n");
	printf("Opcija 3: Ime\n");
	printf("Opcija 4: Povratak\n");
	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1: pretragaCijena(polje); break;
	case 2: pretragaKategorija(polje); break;
	case 3:	pretragaIme(polje); break;
	case 4: return 90;
	default: printf("\nPogresan unos!\n");

	}

	return uvijet;
}

int izbornikSort() {
	int uvijet = 0;
	ARTIKL* polje = NULL;
	polje = (ARTIKL*)ucitavanjeArtikala();
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
	fp = fopen("artikli.bin", "wb");

	if (fp == NULL) {
		perror("Kreiranje");
	}

	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

void dodavanjeArt() {
	FILE* fp = NULL;
	fp = fopen("artikli.bin", "rb+");

	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Trenutni broj artikala: %d", brojArtikala);

	ARTIKL artikli;
	artikli.id = brojArtikala + 1;
	br++;
	getchar();
	printf("\nUnesite kategoriju artikla: ");
	scanf("%24[^\n]", artikli.kategorija);
	getchar();
	printf("\nUnesite ime artikla: ");
	scanf("%24[^\n]", artikli.ime);
	printf("\nUnesite cijenu artikla: ");
	scanf("%d", &artikli.cijena);
	printf("\nUnesite kolicinu artikla: ");
	scanf("%d", &artikli.kolicina);
	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&artikli, sizeof(ARTIKL), 1, fp);
	rewind(fp);
	brojArtikala++;
	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

void azuriranje() {
	FILE* fp = NULL;
	int ispravak;
	fp = fopen("artikli.bin", "rb+");
	if (fp == NULL)
		printf("Nema unesenih artikala\n\n");
	else {
		printf("Unesi broj artikla koji zelite ispraviti.\n");
		scanf("%d", &ispravak);
		fseek(fp, sizeof(int) + (sizeof(ARTIKL) * (ispravak - 1)), SEEK_SET);
		ARTIKL ispravljenArtikl;
		ispravljenArtikl.id = ispravak;
		getchar();
		printf("\nUnesite ispravljenu kategoriju artikla: ");
		scanf("%24[^\n]", ispravljenArtikl.kategorija);
		getchar();
		printf("\nUnesite ime artikla: ");
		scanf("%24[^\n]", ispravljenArtikl.ime);
		printf("\nUnesite cijenu artikla: ");
		scanf("%d", &ispravljenArtikl.cijena);
		printf("\nUnesite kolicinu artikla: ");
		scanf("%d", &ispravljenArtikl.kolicina);
		fwrite(&ispravljenArtikl, sizeof(ARTIKL), 1, fp);
		rewind(fp);
		fwrite(&brojArtikala, sizeof(int), 1, fp);
		fclose(fp);

	}
}

void* ucitavanjeArtikala() {
	FILE* fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		printf("Nema unesenih artikala\n\n");
		return NULL;
	}
	fread(&brojArtikala, sizeof(int), 1, fp);
	ARTIKL* polje = NULL;
	polje = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(ARTIKL), brojArtikala, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(ARTIKL* polje) {
	for (i = 0; i < brojArtikala; i++)
	{
		printf("Artikl broj %d:\tID: %d\tKategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", i + 1, (polje + i)->id, (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
	}
}

void* pretragaIme(ARTIKL* polje) {
	char trazenoIme[25]={0};
	int brojac = 0;

	printf("Upisite ime artikla koje zelite pronaci.\n");
	getchar();
	scanf("%24[^\n]", trazenoIme);

	for (i = 0; i < brojArtikala; i++) {
		if (!strcmp(trazenoIme, (polje + i)->ime)) {
			printf("\nIme artikla je pronadeno!\n\n");
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nIme artikla nije pronadeno!\n\n");
	return NULL;
}

void* pretragaKategorija(ARTIKL* polje) {
	char trazenaKategorija[25]={0};
	int brojac = 0;

	printf("Upisite kategoriju artikla koju zelite pronaci.\n");
	getchar();
	scanf("%24[^\n]", trazenaKategorija);

	for (i = 0; i < brojArtikala; i++) {
		if (!strcmp(trazenaKategorija, (polje + i)->kategorija)) {
			printf("\nKategorija artikla je pronadena!\n\n");
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nKategorija artikla nije pronadena!\n\n");
	return NULL;
}

void* pretragaCijena(ARTIKL* polje) {
	int trazenaCijena;
	int brojac = 0;

	printf("Upisite cijenu artikla koju zelite pronaci.\n");
	scanf("%d", &trazenaCijena);

	for (i = 0; i < brojArtikala; i++) {
		if (trazenaCijena == (polje + i)->cijena) {
			printf("\nCijena artikla je pronadena!\n\n");
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nCijena artikla nije pronadena!\n\n");
	return NULL;
}

void zamjena(ARTIKL* veci, ARTIKL* manji) {
	ARTIKL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortNajjefCijena(ARTIKL* polje) {
	int min = -1;
	printf("Sortirani artikli po cijeni od najjeftinijeg do najskupljeg.\n");
	for (i = 0; i < brojArtikala - 1; i++)
	{
		min = i;
		for (j = i + 1; j < brojArtikala; j++)
		{
			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	for (i = 0; i < brojArtikala; i++)
	{
		if (i == 0) {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else if (i > 0 && i < brojArtikala - 1) {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
	}
	printf("\n");
}

void selectionSortNajskupCijena(ARTIKL* polje) {
	int min = -1;
	printf("Sortirani artikli po cijeni od najskupljeg do najjeftinijeg.\n");
	for (i = 0; i < brojArtikala - 1; i++)
	{
		min = i;
		for (j = i + 1; j < brojArtikala; j++)
		{
			if ((polje + j)->cijena > (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	for (i = 0; i < brojArtikala; i++)
	{
		if (i == 0) {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else if (i > 0 && i < brojArtikala - 1) {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
		else {
			printf("Kategorija: %s\tIme: %s\tCijena: %d\tKolicina: %d\n", (polje + i)->kategorija, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);

		}
	}
	printf("\n");
}

void brisanjeArt(ARTIKL* polje) {
	FILE* fp = NULL;
	fp = fopen("artikli.bin", "wb");
	if (fp == NULL) {
		perror("  Brisanje artikala");
	}

	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int brojac = 0;
	int trazeniArt;

	printf("\nUnesi ID artikla koji zelite obrisati\n");
	scanf("%d", &trazeniArt);

	for (i = 0; i < brojArtikala; i++) {
		if (trazeniArt != (polje + i)->id) {
			fwrite((polje + i), sizeof(ARTIKL), 1, fp);
			brojac++;
		}
	}
	rewind(fp);
	fwrite(&brojac, sizeof(int), 1, fp);
	fclose(fp);
}

void brisanjeDat(ARTIKL* polje) {
	printf("Zelite li pri izlasku programa izbrisati datoteku ili zadrzati?\n");
	printf("Ako zelite izbrisati datoteku upisite \"da\", u suprotnome upisite \"ne\" te datoteku zadrzavate.\n\n");

	char upit[3] = { '\0' };
	scanf("%2s", upit);

	if (!strcmp("da", upit)) {
		remove("artikli.bin") == 0 ? printf("\nUspjesno obrisana datoteka!\n") : printf("\nNeuspjesno brisanje datoteke ili datoteka uopce ne postoji!\n");
		printf("\nIzlaz iz programa!!\n");
		free(polje);

	}
	else printf("\nDatoteka zadrzana.\n\nIzlaz iz programa!!\n");
}
