#ifndef HEADER_H
#define HEADER_H

#define MAX_NAZIV 50
#define MAX_PROIZVODJAC 50

typedef struct {
    int id;
    char naziv[MAX_NAZIV];
    char proizvodjac[MAX_PROIZVODJAC];
    float cijena;
    int kolicina;
} Parfem;

void kreiranjeDatoteke(const char* const ime);
void dodajParfem(const char* const ime);
void ispisiPodatke(const char* const ime);


#endif 
