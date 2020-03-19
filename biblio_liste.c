/* biblio.c */

#include"biblio_liste.h"

/*------------------------------------------------------------------------*/

Biblio *nouvelle_biblio(void){
	//allocation memoire et initialisation des champs
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->L = NULL;
	B->nE = 0;
}

/*------------------------------------------------------------------------*/

void libere_biblio(Biblio *B) {
	CellMorceau *L;
	// libere chaque morceaux
	while(B->L != NULL) {
		L = B->L;
		B->L = L->suiv;
		free(L);
	}	
	free(B);
}

/*------------------------------------------------------------------------*/
	
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

/*------------------------------------------------------------------------*/

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	CellMorceau *L = B->L;
	int num = 0;
	// cherche le num le plus grand pour prendre le suivant
	while(L != NULL) {
		if (L->num >= num) {
			num = L->num + 1;
		}
		L = L->suiv;
	}
	insere(B, num, titre, artiste);
}

/*------------------------------------------------------------------------*/

CellMorceau *rechercheParNum(Biblio *B, int num) {
	CellMorceau *L = B->L;
	// parcour toute la liste a la recherche du morceau num
	while(num != L->num && L != NULL) {
		L = L->suiv;
	}
	return L;
}

/*------------------------------------------------------------------------*/
	
CellMorceau *rechercheParTitre(Biblio *B, char *titre) {
	CellMorceau *L = B->L;
	// parcour toute la liste a la recherche du morceau num
	while(strcmp(titre, L->titre)!=0 && L != NULL) {
		L = L->suiv;
	}
	return L;
}

/*------------------------------------------------------------------------*/
		
int supprimeMorceau(Biblio *B, int num) {
	CellMorceau *L = B->L;
	// si le premier morceau est celui a supp
	if (L->num == num) {
		B->L = L->suiv;
		free(L);
		B->nE -= 1;
		return 1;
	}
	// sinon 
	while(L->suiv != NULL && L->suiv->num != num) {
		L = L->suiv;
	}
	if (L->suiv != NULL) {
		CellMorceau *oldL = L->suiv;
		L->suiv = L->suiv->suiv;
		free(oldL);
		B->nE -= 1;
		return 1;
	}
	return 0;
}

/*------------------------------------------------------------------------*/

void afficheMorceau(CellMorceau *L) {
	printf("n°%d\t", L->num);
	printf("titre: %s\t", L->titre);
	printf("artiste: %s\n", L->artiste);
}

void affiche_biblio(Biblio *B) {
	CellMorceau *L = B->L;
	printf("nombre de morceaux: %d\n", B->nE);
	//parcour_Morceaux(B->L);
	while(L != NULL) {
		afficheMorceau(L);
		L = L->suiv;
	}
	printf("nombre de morceaux: %d\n", B->nE);
}

/*------------------------------------------------------------------------*/

Biblio *extraireMorceauxDe(Biblio *B, char *artiste) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *L = B->L;
	while(L != NULL) {
		/* Pour chaque morceau, si l'artiste correspond a notre artsite,
		   alors on l'ajoute dans la nouvelle biblio */
		if(strcmp(L->artiste, artiste)==0) {
			insere(new_B, L->num, L->titre, L->artiste);
		}
		L = L->suiv;
	}
	return new_B;
}

/*------------------------------------------------------------------------*/

int est_dans(CellMorceau *L, Biblio *B) {
	CellMorceau *M = B->L;
	while(M != NULL) {
		/* Pour chaque morceau, si le titre et l'artiste mais pas le num correspondent
		   a notre morceau L, alors on renvoie 1 sinon on renvoie 0*/
		if(strcmp(M->titre, L->titre)==0 && strcmp(M->artiste, L->artiste)==0 && M->num != L->num) {
			return 1;
		}
		M = M->suiv;
	}
	return 0;
}

/*------------------------------------------------------------------------*/

Biblio *uniques(Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau *L = B->L;
	for (int i = 0; i < B->nE; i++) {
		/* Pour chaque morceau, si aucun autre morceau n'est similaire dans B,
		   alors on insere dans new_B */
		if (est_dans(L, B)==0) {
			insere(new_B, L->num, L->titre, L->artiste);
		}
		L = L->suiv;
	}
	return new_B;
}

/*------------------------------------------------------------------------*/


