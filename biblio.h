/* biblio.h */

#ifndef biblio_h
#define biblio_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.h"

typedef struct Biblio Biblio;

Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche(Biblio *B);
Biblio *uniques(Biblio *B);

#endif /* biblio.h */
