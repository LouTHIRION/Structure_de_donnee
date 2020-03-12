/* jeu_test.c */

#include "jeu_test.h"


void test_nouvelle_biblio(void) {
	printf("\ntest fonction nouvelle_biblio:\n");
	Biblio *B = nouvelle_biblio();
	affiche_biblio(B);
}

void test_insere(int num, char *titre, char *artiste) {
	Biblio *B = nouvelle_biblio();
	insere(B, 0, titre, artiste );
	affiche_biblio(B);
}

void test_charge_entrees(const char *nom_fichier, int n) {
	printf("\ntest fonction charge_n_entrees:\n");
	Biblio *B = charge_n_entrees(nom_fichier, n);
	/*insere(B, 20, "blabla", "Don Gibson");
	insere(B, 19, "blabla", "Rihanna");
	insere(B, 21, "nounou", "Don");
	insere(B, 22, "blabla", "T");*/
	affiche_biblio(B);	
	libere_biblio(B);
}

void test_libere(void) {
	Biblio *b = nouvelle_biblio();
	insere(b, 0, "ciel", "george");
	affiche_biblio(b);
	libere_biblio(b);
}

void test_recherche(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	printf("\ntest recherche par titre\n");
	afficheMorceau(rechercheParTitre(B, "Take Me"));
	printf("test recherche par num\n");
	for(int i = 0; i < 19; i++) {
		printf("%d\n", i);
		afficheMorceau(rechercheParNum(B, i));
	}
	libere_biblio(B);
}

void test_supprimeMorceau(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	printf("\test supprimeMorceau\n");
	printf("%d\n", supprimeMorceau(B, 15));
	affiche_biblio(B);
	libere_biblio(B);
}

void test_est_dans(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	//Biblio *B = nouvelle_biblio();
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->suiv = NULL;
	L->titre = "Bright";
	L->artiste = "Echosmith";
	printf("\nest dans : %d\n", est_dans(L, B));
	libere_biblio(B);
}
	

void test_insereSansNum(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	insereSansNum(B, "blabla", "Jean");
	insereSansNum(B, "salut", "bonjour");
	printf("\ntest insereSansNum:\n");
	affiche_biblio(B);
	libere_biblio(B);
}
	

void test_unique(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	insereSansNum(B, "High On Love", "The Knickerbockers");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");
	insereSansNum(B, "Stuck On A Feeling", "Prince Royce Featuring Snoop Dogg");
	printf("\ntest unique: \n");
	affiche_biblio(uniques(B));
	libere_biblio(B);
}

void test_extraireMorceauxDe(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	//insereSansNum(B, "blabla", "The Knickerbockers");
	insere(B, 20, "blabla", "Don Gibson");
	insere(B, 19, "blabla", "Rihanna");
	insere(B, 21, "nounou", "Don");
	insere(B, 22, "blabla", "T");
	printf("\ntest extraireMorceauxDe: \n");
	affiche_biblio(extraireMorceauxDe(B, "Don Gibson"));
}


	
