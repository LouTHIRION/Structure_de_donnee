/* biblio.c */

#include"biblio_liste.h"


Biblio *nouvelle_biblio(void){
	//allocation memoire et initialisation des champs
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->L = NULL;
	B->nE = 0;
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

void afficheMorceau(CellMorceau *L) {
	printf("n°%d\t", L->num);
	printf("titre: %s\t", L->titre);
	printf("artiste: %s\n", L->artiste);
}

void affiche_CellMorceaux(CellMorceau *L) {
	if(L != NULL) {
		afficheMorceau(L);
		affiche_CellMorceaux(L->suiv);
	}
}

void affiche_biblio(Biblio *B) {
	printf("nombre de morceaux: %d\n", B->nE);
	affiche_CellMorceaux(B->L);
}
		

