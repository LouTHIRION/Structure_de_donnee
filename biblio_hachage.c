/* biblio_hachage */

#include "biblio_hachage.h"

unsigned int fonction_cle(const char *artiste) {
	unsigned int cle = 0;
	int i;
	while(artiste[i] != '\0') {
		cle += artiste[i];
		i++;
	}
	return cle;
}

unsigned int fonction_hachage(unsigned int cle, int m) {
	return floor(m*(cle * A - floor(cle * A)));
}

void insere(Biblio *B, int num, char *titre, char *artiste) {
    unsigned int cle = fonction_cle(artiste);
    CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
    L->num = num;
    L->titre = titre;
    L->artiste = artiste;
    L->cle = cle;
    int indice = fonction_hachage(cle, 85000);
    L->suiv = B->T[indice];
    B->T[indice] = L;
    B->nE += 1;
}

Biblio *nouvelle_biblio(void) {
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->nE = 0;
	B->m = TAILLE_TABLE;
	CellMorceau **T = (CellMorceau **)malloc(B->m * sizeof(CellMorceau *));
	for(int i = 0; i < B->m; i++) {
		T[i] = NULL;
	}	
	B->T = T;
}

void libere_biblio(Biblio *B) {
	CellMorceau **T = B->T;
	int i = 0;
	for(i; i<B->m; i++) {
		free(T[i]);
	}
	free(T);
	free(B);
}

void afficheMorceau(CellMorceau *L) {
	//printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
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
	CellMorceau **T = B->T;
	int i = 0, i_emeElem = 0;
    while(i_emeElem < B->nE && i < B->m) {
    	if(T[i] != NULL) {
    		parcour_Morceaux(T[i]);
    		i_emeElem += 1;
    	}
    	i += 1;
    }
}


CellMorceau * rechercheParNum(Biblio *B, int num) {

}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{

}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{

}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{

}


int supprimeMorceau(Biblio *B, int num)
{

}


int est_dans(CellMorceau *L, Biblio *B) {

}

Biblio *uniques (Biblio *B)
{
    
}
