/* biblio_tabdyn.c */

#include "biblio_tabdyn.h"

void insere(Biblio *B, int num, char *titre, char *artiste) {
	//if(num < B->nE) {  //Pour tester si le num choisi n'est pas out of range
	// reallocation de la memoire si necessaire
	if(B->nE+1 >= B->capacite) {
		// on augmente la capacite de 25%
		B->capacite = round(B->capacite + B->capacite/2);
		B->T = realloc(B->T, B->capacite * sizeof(CellMorceau));
	}
	// et on ajoute l'element
	CellMorceau L;
	L.num = num;
	L.titre = titre;
	L.artiste = artiste;
	B->T[num] = L;
	B->nE += 1;
}

Biblio *nouvelle_biblio(void) {
	// allocation memoire pour la biblio et la tab et initialisation des variables
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->nE = 0;
	B->capacite = TAILLE_INITIALLE_TAB;
	CellMorceau *T = (CellMorceau *)malloc(B->capacite * sizeof(CellMorceau));
	B->T = T;
}

void libere_biblio(Biblio *B) {
	// libere le tableau puis la biblio
   free(B->T);
   free(B);
}


void afficheMorceau(CellMorceau *L) {
	//printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
	if(L != NULL) {
		printf("n°%d\t", L->num);
		printf("titre: %s\t", L->titre);
		printf("artiste: %s\n", L->artiste);
	}
}

void affiche_biblio(Biblio *B) {
    printf("nombre de morceaux: %d\n", B->nE);
    printf("capacite du tableau: %d\n", B->capacite);
    for(int i = 0; i < B->nE; i++) {
    	afficheMorceau(&B->T[i]);
    }
    printf("nombre de morceaux: %d\n", B->nE);
    printf("capacite du tableau: %d\n", B->capacite);
}


CellMorceau * rechercheParNum(Biblio *B, int num) {
	return &B->T[num];
	/*CellMorceau *T = B->T;
	int i = 0;
	// parcour chaque element pour trouver le morceau de numero num
	while(i < B->nE) {
		if(T[i].num == num) {
			return &T[i];
		}
		i++;
	}
	return NULL;*/	
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	CellMorceau *T = B->T;
	int i = 0;
	// parcour chaque element pour trouver le morceau avec le titre
	while(i < B->nE) {
		if(strcmp(T[i].titre, titre)==0) {
			return &T[i];
		}
		i++;
	}
	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *T = B->T;
	int i = 0;
	// parcour chaque element
	for(i; i<B->nE; i++) {
		// si l'artiste est celui demande, on ajoute le morceau a la nouvelle biblio
		if(strcmp(T[i].artiste, artiste)==0) {
			insereSansNum(new_B, T[i].titre, T[i].artiste);
		}
	}
	return new_B;
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	insere(B, B->nE, titre, artiste);
	/*CellMorceau *T = B->T;
	int i = 0;
	//int num = 0;
	while(T[i] != NULL) {
		i++;
	}
	insere(B, i, titre, artiste);*/
	// parcour chaque element a la recherche d'un num libre
	/*for(i; i<B->nE; i++) {
		if(T[i].num >= num) {
			num += 1;
		}
	}
	insere(B, num, titre, artiste);*/
}


int supprimeMorceau(Biblio *B, int num) {
	//B->T[num] = NULL;
	CellMorceau *T = B->T;
	int i = 0, stop = 0;
	// cherche le morceau a supprimer
	while(i < B->nE || stop) {
		if(T[i].num == num) {
			// une fois trouve, on l'ecrase avec le morceau suivant et on decale tout le tableau
			stop = 1;
			for(i; i<B->nE-1; i++) {
				T[i] = T[i+1];
			}
			B->nE -= 1;
			return 1;
		}
		i++;
	}
	return 0;
}

int est_dans(CellMorceau *L, Biblio *B) {
	CellMorceau *T = B->T;
	int i = 0;
	// parcour chaque element
	while(i < B->nE) {
		// si meme titre ET meme artiste
		if(strcmp(T[i].titre, L->titre)==0 && strcmp(T[i].artiste, L->artiste)==0) {
			return 1;
		}
		i++;
	}
	return 0;
}

Biblio *uniques (Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *T = B->T;
	int i = 0;
	for(i; i<B->nE; i++) {
		if(est_dans(&T[i], new_B)) {
			supprimeMorceau(new_B, rechercheParTitre(new_B, T[i].titre)->num);
		}
		else {
			insereSansNum(new_B, T[i].titre, T[i].artiste);
		}
	}
	return new_B;
}


