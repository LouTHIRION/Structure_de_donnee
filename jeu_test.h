/* jeu_test.h */

#ifndef jeu_test_h
#define jeu_test_h

#include "biblio.h"
#include "biblio_arbrelex.h"

void test_nouvelle_biblio(void);
void test_insere(int num, char *titre, char *artiste);
void test_charge_entrees(const char *nom_fichier, int n);
void test_libere(void);
void test_recherche(const char *nom_fichier, int n);
void test_supprimeMorceau(const char *nom_fichier, int n);
void test_est_dans(const char *nom_fichier, int n);
void test_insereSansNum(const char *nom_fichier, int n);
void test_unique(const char *nom_fichier, int n);

#endif
