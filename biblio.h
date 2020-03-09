/* biblio.h */

#ifndef biblio_h
#define biblio_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.h"

typedef struct CellMorceau CellMorceau;
typedef struct Biblio Biblio;

Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche_biblio(Biblio *B);
void afficheMorceau(CellMorceau *L);
Biblio *uniques(Biblio *B);
CellMorceau *rechercheParNum(Biblio *B, int num);
CellMorceau *rechercheParTitre(Biblio *B, char *titre);
Biblio *extraireMorceauxDe(Biblio *B, char *artiste);
void insereSansNum(Biblio *B, char *titre, char *artiste);
int supprimeMorceau(Biblio *B, int num);

#endif
