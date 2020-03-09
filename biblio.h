/* biblio.h */

#ifndef biblio_h
#define biblio_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.h"

typedef struct CellMorceau CellMorceau;
typedef struct Biblio Biblio;

/* alloue la memoire pour une nouvelle biblio */
Biblio *nouvelle_biblio(void);

/* charge n entree dans une nouvelle biblio */
Biblio *charge_n_entrees(const char *nom_fichier, int n);

/* libere la memoire d'une biblio */
void libere_biblio(Biblio *B);

/* insere un morceau dans une biblio */
void insere(Biblio *B, int num, char *titre, char *artiste);

/* affiche une biblio */
void affiche_biblio(Biblio *B);

/* affiche un morceau */
void afficheMorceau(CellMorceau *L);

/* nouvelle version de B sans doublon */
Biblio *uniques(Biblio *B);

/* recherche un morceau dans B par son numero */
CellMorceau *rechercheParNum(Biblio *B, int num);

/*                             par son titre */
CellMorceau *rechercheParTitre(Biblio *B, char *titre);

/* retourne une biblio avec tous les morceau d'un artiste */
Biblio *extraireMorceauxDe(Biblio *B, char *artiste);

/* insere un morceau dans B, l'algo dois choisir un num qui n'est pas deja pris */
void insereSansNum(Biblio *B, char *titre, char *artiste);

/* supprime un morceau de B */
int supprimeMorceau(Biblio *B, int num);

int est_dans(CellMorceau *L, Biblio *B);

#endif
