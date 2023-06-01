#ifndef HEADER_H
#define HEADER_H

typedef struct parfem {
	int id;
	char spol[25];
	char ime[25];
	int cijena;
	int kolicina;
}PARFEM;

int izbornik();
int izbornikPret();
int izbornikSort();
void kreiranjeDat();
void dodavanjePar();
void azuriranje();
void* ucitavanjeParfema();
void ispisivanje(PARFEM*);
void* pretragaIme(PARFEM*);
void* pretragaCijena(PARFEM*);
void* pretragaSpol(PARFEM*);
void zamjena(PARFEM*, PARFEM*);
void selectionSortNajjefCijena(PARFEM*);
void selectionSortNajskupCijena(PARFEM*);

void brisanjePar(PARFEM*);
void brisanjeDat(PARFEM*);


#endif // HEADER_H

