#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define MAX_PARFEMA 100

struct Parfem {
    char naziv[50];
    char marka[50];
    float cijena;
    char miris[50];
    int kolicina;
};

extern struct Parfem skladiste[MAX_PARFEMA];
extern int brojParfema;

int izbornik();
void dodajParfem();
void spremiPodatkeUDatoteku(const char* imeDatoteke);
int izbornik();
void ispisiParfeme();
void kreirajDatoteku(const char* imeDatoteke);
void provjeriKreirajDatoteku(const char* imeDatoteke);
#endif
