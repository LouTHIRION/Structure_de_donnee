/* jeu_test.c */

#include "jeu_test.h"


void test_nouvelle_biblio(void) {
	printf("test fonction nouvelle_biblio:\n");
	Biblio *B = nouvelle_biblio();
	affiche_biblio(B);
}

void test_insere(int num, char *titre, char *artiste) {
	Biblio *B = nouvelle_biblio();
	insere(B, 0, titre, artiste );
	affiche_biblio(B);
}

void test_charge_entrees(const char *nom_fichier, int n) {
	printf("test fonction charge_n_entrees:\n");
	Biblio *B = charge_n_entrees(nom_fichier, n);
	affiche_biblio(B);
}

void test_libere(void) {
	Biblio *b = nouvelle_biblio();
	insere(b, 0, "ciel", "george");
	affiche_biblio(b);
	CellMorceau *L = b->L;
	libere_biblio(b);
}

void test_recherche(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	printf("test recherche par titre\n");
	afficheMorceau(rechercheParTitre(B, "Stuck On A Feeling"));
	printf("test recherche par num\n");
	afficheMorceau(rechercheParNum(B, 15));
}

void test_supprimeMorceau(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	printf("test supprimeMorceau\n");
	printf("%d\n", supprimeMorceau(B, 15));
	affiche_biblio(B);
}

void test_est_dans(const char *nom_fichier, int n) {
	//Biblio *B = charge_n_entrees(nom_fichier, n);
	Biblio *B = nouvelle_biblio();
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->suiv = NULL;
	L->titre = "Blue Blue Day";
	L->artiste = "Don Gibson";
	printf("est dans : %d\n", est_dans(L, B));
}
	

void test_insereSansNum(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	insereSansNum(B, "blabla", "Jean");
	printf("test insereSansNum:\n");
	affiche_biblio(B);
}
	

void test_unique(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	insereSansNum(B, "High On Love", "The Knickerbockers");
	printf("test unique: \n");
	affiche_biblio(uniques(B));
}




	