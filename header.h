#ifndef HEADER_H
#define HEADER_H

typedef struct artikl {
	int id;
	char kategorija[25];
	char ime[25];
	int cijena;
	int kolicina;
}ARTIKL;

int izbornik();
int izbornikPret();
int izbornikSort();
void kreiranjeDat();
void dodavanjeArt();
void azuriranje();
void* ucitavanjeArtikala();
void ispisivanje(ARTIKL*);
void* pretragaIme(ARTIKL*);
void* pretragaCijena(ARTIKL*);
void* pretragaKategorija(ARTIKL*);
void zamjena(ARTIKL*, ARTIKL*);
void selectionSortNajjefCijena(ARTIKL*);
void selectionSortNajskupCijena(ARTIKL*);

void brisanjeArt(ARTIKL*);

void brisanjeDat(ARTIKL*);


#endif // HEADER_H

