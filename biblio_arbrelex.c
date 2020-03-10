/* biblio_arbrelex.c */

#include "biblio_arbrelex.h"

Noeud *rechercheOuCreer_artiste(Biblio *B, char *artiste) {
	int i = 0; //entier pour parcourir la chaine artiste
	Noeud *cour = B->A; //Noeud courant
	Noeud *prec = cour; //Noeud precedent
	while(cour != NULL && artiste[i] != '\0') {
		prec = cour;
		if (artiste[i] == cour->car) {
			cour = cour->car_suiv;
			i++;
		}
		else {
			cour = cour->liste_car;
		}
	}
	if (cour != NULL) {
		return cour;
	}
	if (artiste[i-1] != prec->car) {
		cour = (Noeud *)malloc(sizeof(Noeud));
		cour->car = artiste[i];
		cour->liste_car = NULL;
		cour->car_suiv = NULL;
		prec->liste_car = cour;
		prec = cour;
		cour = NULL;
	}
	while(artiste[i] != '\0') {
		cour = (Noeud *)malloc(sizeof(Noeud));
		cour->car = artiste[i];
		cour->liste_car = NULL;
		cour->car_suiv = NULL;
		prec->car_suiv = cour;
		prec = cour;
		cour = NULL;
		i++;
	}
	return prec;
}


Biblio *nouvelle_biblio(void) {

}


void insere(Biblio *B, int num, char *titre, char *artiste) {

}
