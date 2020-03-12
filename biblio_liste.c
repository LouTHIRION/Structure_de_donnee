/* biblio.c */

#include"biblio_liste.h"


Biblio *nouvelle_biblio(void){
	//allocation memoire et initialisation des champs
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->L = NULL;
	B->nE = 0;
}

void libere_biblio(Biblio *B) {
	CellMorceau *L;
	while(B->L != NULL) {
		L = B->L;
		B->L = L->suiv;
		free(L);
	}	
	free(B);
}
	
void insere(Biblio *B, int num, char *titre, char *artiste) {
	//allocation memoire, initialisation champs et mis a jour de la biblio
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->num = num;
	L->titre = titre;
	L->artiste = artiste;
	L->suiv = B->L;
	B->L = L;
	B->nE ++;
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	CellMorceau *L = B->L;
	int num = 0;
	while(L != NULL) {
		if (L->num >= num) {
			num = L->num + 1;
		}
		L = L->suiv;
	}
	insere(B, num, titre, artiste);
}

CellMorceau *rechercheParNum(Biblio *B, int num) {
	CellMorceau *L = B->L;
	while(num != L->num && L != NULL) {
		L = L->suiv;
	}
	return L;
}
	
CellMorceau *rechercheParTitre(Biblio *B, char *titre) {
	CellMorceau *L = B->L;
	while(strcmp(titre, L->titre)!=0 && L != NULL) {
		L = L->suiv;
	}
	return L;
}
		
int supprimeMorceau(Biblio *B, int num) {
	CellMorceau *L = B->L;
	if (L->num == num) {
		CellMorceau *oldL = L;
		B->L = L->suiv;
		free(oldL);
		return 1;
	}
	while(L->suiv != NULL && L->suiv->num != num) {
		L = L->suiv;
	}
	if (L->suiv != NULL) {
		CellMorceau *oldL = L->suiv;
		L->suiv = L->suiv->suiv;
		free(oldL);
		return 1;
	}
	return 0;
}

void afficheMorceau(CellMorceau *L) {
	printf("n°%d\t", L->num);
	printf("titre: %s\t", L->titre);
	printf("artiste: %s\n", L->artiste);
}

void parcour_Morceaux(CellMorceau *L) {
	if(L != NULL) {
		afficheMorceau(L);
		parcour_Morceaux(L->suiv);
	}
}

void affiche_biblio(Biblio *B) {
	printf("nombre de morceaux: %d\n", B->nE);
	parcour_Morceaux(B->L);
}

Biblio *extraireMorceauxDe(Biblio *B, char *artiste) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *L = B->L;
	while(L != NULL) {
		if(strcmp(L->artiste, artiste)==0) {
			insere(new_B, L->num, L->titre, L->artiste);
		}
		L = L->suiv;
	}
	return new_B;
}

int est_dans(CellMorceau *L, Biblio *B) {
	if (B->L == NULL) {
		return 0;
	}
	CellMorceau *M = B->L;
	while((strcmp(M->titre, L->titre)!=0 || strcmp(M->artiste, L->artiste)!=0) && M->suiv != NULL) {
		M = M->suiv;
	}
	if (strcmp(M->titre, L->titre)==0 && strcmp(M->artiste, L->artiste)==0) {
		return 1;
	}
	return 0;
}


Biblio *uniques(Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *L = B->L;
	for (int i = 0; i < B->nE; i++) {
		if (est_dans(L, new_B)) {
			supprimeMorceau(new_B, rechercheParTitre(new_B, L->titre)->num);
		}
		else {
			insereSansNum(new_B, L->titre, L->artiste);
		}
		affiche_biblio(new_B);
		printf("\n");
		L = L->suiv;
	}
	return new_B;
}






