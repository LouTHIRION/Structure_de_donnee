/* main.c */

#include<stdlib.h>
#include<stdio.h>
#include"biblio.h"


int main(int argc, const char *argv[]) {
	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}
	
	
	return 0;
}
