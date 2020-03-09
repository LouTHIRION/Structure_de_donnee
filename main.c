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
	
	test_nouvelle_biblio();
	test_insere();
	test_charge_entrees(nomfichier, nblignes);
	
	
	
	return 0;
}
