/* jeu_test.c */

#include "jeu_test.h"

int tab_num1[100] = {2781 ,287732 ,129312 ,221567 ,65329 ,145243 ,102155 ,136894 ,90406 ,18382 ,84367 ,134243 ,151967 ,55650 ,56854 ,255389 ,45645 ,216503 ,35599 ,294899 ,250903 ,211090 ,193022 ,120706 ,199852 ,50572 ,100611 ,265967 ,213009 ,277078 ,83636 ,111073 ,79981 ,79502 ,104962 ,107481 ,60172 ,33028 ,145466 ,256014 ,153493 ,221312 ,50259 ,213206 ,57643 ,27876 ,175712 ,273636 ,242057 ,137552 ,204267 ,35642 ,136110 ,38065 ,21766 ,287102 ,191886 ,281484 ,94868 ,131440 ,86241 ,80733 ,160921 ,84436 ,39647 ,218902 ,275283 ,98108 ,68950 ,169570 ,113114 ,214711 ,279315 ,66999 ,298477 ,179787 ,76380 ,26648 ,298419 ,235168 ,153002 ,195285 ,180296 ,116066 ,283826 ,218742 ,45317 ,283541 ,162536 ,49836 ,109007 ,219282 ,199932 ,138260 ,72279 ,184594 ,233928 ,82818 ,217058 ,246117};

int *tab_num(int taille_tab, int nbMorceau) {
	int i;
	int *tab = malloc(taille_tab * sizeof(int));
	for(i = 0; i<taille_tab; i++) {
		tab[i] = rand() % nbMorceau;
	}
	return tab;
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

void test_recherche_parNum(const char *nom_fichier, int n) {
	long clk_tck = CLOCKS_PER_SEC;
	clock_t t1, t2;
	double tps_ecoule;
	Biblio *B = charge_n_entrees(nom_fichier, n);
	int *nums = tab_num(100, n);
	/*printf("\ntest recherche par num\n");
	affiche_biblio(B);*/
	t1 = clock();
	for(int i = 0; i < 100; i++) {
		rechercheParNum(B, nums[i]);
	}
	t2 = clock();
	tps_ecoule = (double)(t2-t1)/(double)clk_tck;
	printf("\ntest recherche par NUMERO\n");
	//printf("temps consomme (en secondes)\nPour 100 recherche : %lf\nEn moyenne pour 1: %lf\n", tps_ecoule, tps_ecoule/100);
	printf("temps : %lf\n", tps_ecoule/100);
	libere_biblio(B);
}

void test_recherche_parTitre(const char *nom_fichier, int n) {
	Biblio *B = charge_n_entrees(nom_fichier, n);
	long clk_tck = CLOCKS_PER_SEC;
	clock_t t1, t2;
	double tps_ecoule;
	int i;
	int *nums = tab_num(100, n);
	char *tab_titre[100];
	for(i = 0; i < 100; i++) {
		tab_titre[i] = rechercheParNum(B, nums[i])->titre;
	}
	//printf("\ntest recherche par titre\n");
	t1 = clock();
	for(i = 0; i < 100; i++) {
		rechercheParTitre(B, tab_titre[i]);
	}
	t2 = clock();
	tps_ecoule = (double)(t2-t1)/(double)clk_tck;
	printf("\ntest recherche par TITRE\n");
	//printf("temps consomme (en secondes)\nPour 100 recherche : %lf\nEn moyenne pour 1: %lf\n", tps_ecoule, tps_ecoule/100);
	printf("temps : %lf\n", tps_ecoule/100);
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
	long clk_tck = CLOCKS_PER_SEC;
	clock_t t1, t2;
	double tps_ecoule;
	int i;
	int *nums = tab_num(100, n);
	char *tab_artiste[100];
	for(i = 0; i < 100; i++) {
		tab_artiste[i] = rechercheParNum(B, nums[i])->artiste;
	}
	/*insereSansNum(B, "blabla", "The Knickerbockers");
	insereSansNum(B, "blabla", "Don Gibson");
	insereSansNum(B, "blabla", "Rihanna");
	insereSansNum(B, "nounou", "Don");
	insereSansNum(B, "blabla", "T");
	affiche_biblio(B);*/
	printf("\ntest extraireMorceauxDe: \n");
	t1 = clock();
	for(i = 0; i < 100; i++) {
		extraireMorceauxDe(B, "3 Doors Down");
	}
	t2 = clock();
	tps_ecoule = (double)(t2-t1)/(double)clk_tck;
	printf("\ntest recherche par ARTISTE\n");
	//printf("temps consomme (en secondes)\nPour 100 recherche : %lf\nEn moyenne pour 1: %lf\n", tps_ecoule, tps_ecoule/100);
	printf("temps : %lf\n", tps_ecoule/100);
	
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
	//insereSansNum(B, "God Forever", "Mickael Juniot");
	L->titre = "ABC";
	L->artiste = "Jackson 5";	
	printf("\nest dans : %d\n", est_dans(L, B));
	libere_biblio(B);
}

void test_unique(const char *nom_fichier, int n) {
	long clk_tck = CLOCKS_PER_SEC;
	clock_t t1, t2;
	Biblio *B = charge_n_entrees(nom_fichier, n);
	/*insereSansNum(B, "High On Love", "The Knickerbockers");
	insereSansNum(B, "Stuck On A Feeling", "Prince Royce Featuring Snoop Dogg");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");
	insereSansNum(B, "blabla", "Don Gibson");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");
	insereSansNum(B, "Blue Blue Day", "Don Gibson");
	insereSansNum(B, "blabla", "Don Gibson");*/
	printf("\ntest unique:\n");
	
	t1 = clock();
	Biblio *new_B = uniques(B);
	t2 = clock();
	
	affiche_biblio(new_B);
	printf("temps consomme (en secondes) : %lf \n", (double)(t2-t1)/(double)clk_tck);
	printf("test unique\n");
	libere_biblio(B);
}



	
