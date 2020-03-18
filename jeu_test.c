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
	afficheMorceau(rechercheParTitre(B, "You Still Touch Me"));
	printf("test recherche par num\n");
	//for(int i = 0; i < 19; i++) {
		//printf("%d\n", i);
		//affiche_biblio(B);
		afficheMorceau(rechercheParNum(B, 100000));
	//}
	libere_biblio(B);
}

void test_supprimeMorceau(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	printf("\ntest supprimeMorceau\n");
	//insereSansNum(B, "High On Love", "The Knickerbockers");
	printf("%d\n", supprimeMorceau(B, 12));
	affiche_biblio(B);
	libere_biblio(B);
}

void test_est_dans(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	//Biblio *B = nouvelle_biblio();
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	//L->suiv = NULL;
	insereSansNum(B, "God Forever", "Mickael Juniot");
	L->titre = "God Forever";
	L->artiste = "Mickael Juniot";	
	printf("\nest dans : %d\n", est_dans(L, B));
	libere_biblio(B);
}
	

void test_insereSansNum(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	insereSansNum(B, "blabla", "Jean");
	insereSansNum(B, "God Forever", "Mickael Juniot");
	printf("\ntest insereSansNum:\n");
	affiche_biblio(B);
	libere_biblio(B);
}
	
void test_extraireMorceauxDe(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	//insereSansNum(B, "blabla", "The Knickerbockers");
	insereSansNum(B, "blabla", "Don Gibson");
	insereSansNum(B, "blabla", "Rihanna");
	insereSansNum(B, "nounou", "Don");
	insereSansNum(B, "blabla", "T");
	//affiche_biblio(B);
	printf("\ntest extraireMorceauxDe: \n");
	affiche_biblio(extraireMorceauxDe(B, "3 Doors Down"));
}

void test_unique(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	/*insereSansNum(B, "High On Love", "The Knickerbockers");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");
	insereSansNum(B, "Stuck On A Feeling", "Prince Royce Featuring Snoop Dogg");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");*/
	printf("\ntest unique:\n");
	Biblio *new_B = uniques(B);
	//affiche_biblio(B);
	affiche_biblio(new_B);
	printf("test unique\n");
	libere_biblio(B);
}



	
