/* main.c */

#include<stdlib.h>
#include<stdio.h>
#include"biblio.h"
#include"jeu_test.h"


int main(int argc, const char *argv[]) {
	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>\n", argv[0]);
		return 1;
	}
	
	const char *nomfichier = argv[1];
	int nblignes = atoi(argv[2]);
	
	srand(time(NULL));
	
	//test_nouvelle_biblio();
	//test_insere(0, "titre", "artiste");
	//test_charge_entrees(nomfichier, nblignes);
	//test_libere();
	test_recherche_parNum(nomfichier, nblignes);
	test_recherche_parTitre(nomfichier, nblignes);
	//test_supprimeMorceau(nomfichier, nblignes);
	//test_insereSansNum(nomfichier, nblignes);
	//test_est_dans(nomfichier, nblignes);
	test_extraireMorceauxDe(nomfichier, nblignes);
	//test_unique(nomfichier, nblignes);
	
	
	return 0;
}
