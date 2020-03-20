/* jeu_test.h */

#ifndef jeu_test_h
#define jeu_test_h

#include "biblio.h"
#include <time.h>
//#include "biblio_liste.h"
//#include "biblio_arbrelex.h"
//#include "biblio_tabdyn.h"
#include "biblio_hachage.h"



void test_nouvelle_biblio(void);
void test_insere(int num, char *titre, char *artiste);
void test_charge_entrees(const char *nom_fichier, int n);
void test_libere(void);
void test_recherche_parNum(const char *nom_fichier, int n);
void test_recherche_parTitre(const char *nom_fichier, int n);
void test_supprimeMorceau(const char *nom_fichier, int n);
void test_est_dans(const char *nom_fichier, int n);
void test_insereSansNum(const char *nom_fichier, int n);
void test_unique(const char *nom_fichier, int n);
void test_extraireMorceauxDe(const char *nom_fichier, int n);

#endif
