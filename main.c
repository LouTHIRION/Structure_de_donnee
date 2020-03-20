/* main.c */

#include<stdlib.h>
#include<stdio.h>
#include"biblio.h"
#include"jeu_test.h"


void menu()
{
	printf("Menu:\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-Recherche morceaux uniques\n");
	printf("3-Recherche morceau par titre\n");
	printf("Votre choix : ");
}


int main(int argc, const char *argv[]) {
	if (argc < 3 || argc > 4) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire> <option: test>\n", argv[0]);
		return 1;
	}
	
	const char *nomfichier = argv[1];
	int nblignes = atoi(argv[2]);
	char titre[249];
	
	if (argc == 3) {
		printf("Lecture :\n");
		Biblio *biblio = charge_n_entrees(nomfichier, nblignes);
		
		int ch;
		do {
			menu();
			int lus = scanf("%d", &ch);
			if (lus == 0)
				ch = 0;
			
			switch(ch) {
				case 1 :
					printf("Affichage\n");
					affiche_biblio(biblio);
					break;
				case 2:
					{
						Biblio *Bunique = uniques(biblio);
						affiche_biblio(Bunique);
						libere_biblio(Bunique);
						break;
					}
				case 3 :
					{
						printf("Saisir le titre du morceau :\n");
						scanf(" %248[^\n]", titre);
						CellMorceau * r = rechercheParTitre(biblio, titre);
						if (r == NULL) printf("Aucun morceau de titre : %s!!!\n", titre);
						else afficheMorceau(r);
						break;
					}
				default :
					ch = 0;
					break;
			
			}
		
		} while (ch != 0);
		
		libere_biblio(biblio);
		printf("Au revoir\n");
	}
	else if(strcmp(argv[3], "test")==0) {
		printf("Espace de test : \n\n");
		//srand(time(NULL));
		//test_insere(0, "titre", "artiste");
		//test_charge_entrees(nomfichier, nblignes);
		//test_recherche_parNum(nomfichier, nblignes);
		//test_recherche_parTitre(nomfichier, nblignes);
		//test_supprimeMorceau(nomfichier, nblignes);
		//test_insereSansNum(nomfichier, nblignes);
		test_extraireMorceauxDe(nomfichier, nblignes);
		//test_unique(nomfichier, nblignes);
	}
	else {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire> <option: test>\n", argv[0]);
		return 1;
	}
	
	return 0;
}
