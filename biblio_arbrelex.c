/* biblio_arbrelex.c */

#include "biblio_arbrelex.h"

Noeud *rechercheOuCreer_artiste(Biblio *B, char *artiste) {
	int i = 0; //entier pour parcourir la chaine artiste
	Noeud *cour = B->A; //Noeud courant
	Noeud *prec = cour; //Noeud precedent
	// boucle qui parcourt l'arbre pour trouver le noeud de l'artiste
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
	// si ce noeud existe on le retourne 
	if (cour != NULL) {
		return cour;
	}
	// sinon on cree le ou les noeud(s), plusieurs cas de figure :
	if (prec == NULL) { // l'arbre est encore vide
		cour = (Noeud *)malloc(sizeof(Noeud));
		cour->car = artiste[i];
		cour->liste_car = NULL;
		cour->car_suiv = NULL;
		B->A = cour;
		prec = cour;
		cour = NULL;
		i++;
	}
	/* l'arbre est non vide mais on a aucune lettre de la chaine
		OU
	   on a au moins une lettre mais la liste des lettres suivantes est vide */
	else if (i == 0 || artiste[i-1] != prec->car) { 
		cour = (Noeud *)malloc(sizeof(Noeud));
		cour->car = artiste[i];
		cour->liste_car = NULL;
		cour->car_suiv = NULL;
		prec->liste_car = cour;
		prec = cour;
		cour = NULL;
		i++;
	}
	// boucle general qui ajoute des branches de l'arbre qui n'existent pas
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
	return prec; //renvoi le nouveau noeud
}


Biblio *nouvelle_biblio(void) {
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->A = NULL;
	B->nE = 0;
}

void libere_noeuds(Noeud *N) {
	if (N != NULL) {
		Noeud *A = N->liste_car;
		Noeud *B = N->car_suiv;
		libere_noeuds(A);
		libere_noeuds(B);
		// libere morceau
		CellMorceau *L = N->liste_morceaux;
		while(N->liste_morceaux != NULL) {
			L = N->liste_morceaux;
			N->liste_morceaux = L->suiv;
			free(L);
		}
		free(N);
	}
}

void libere_biblio(Biblio *B) {
    Noeud *N = B->A;
    libere_noeuds(N);
    free(B);
}

void insere(Biblio *B, int num, char *titre, char *artiste) {
	Noeud *N = rechercheOuCreer_artiste(B, artiste);
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->num = num;
	L->titre = titre;
	L->artiste = artiste;
	L->suiv = N->liste_morceaux;
	N->liste_morceaux = L;
	B->nE ++;
}

void afficheMorceau(CellMorceau *L) {
	printf("n°%d\t", L->num);
	printf("titre: %s\t", L->titre);
	printf("artiste: %s\n", L->artiste);
	
	//printf("|A| %8d | %-32.32s | %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
}

void parcour_Morceaux(CellMorceau *L) {
	if(L != NULL) {
		afficheMorceau(L);
		parcour_Morceaux(L->suiv);
	}
}

void parcour_noeuds(Noeud *N) {
	Noeud *cour = N;
	while(cour != NULL) {
		//printf("%d %c\n", i, cour->car);
		parcour_noeuds(cour->car_suiv);
		parcour_Morceaux(cour->liste_morceaux);
		cour = cour->liste_car;
	}
}

void affiche_biblio(Biblio *B) {
	printf("nombre de morceaux: %d\n", B->nE);
    parcour_noeuds(B->A);
    /*Noeud *N = B->A;
	while(N != NULL) {
		printf("%c %c ", N->car, N->car_suiv->car);
		N = N->liste_car;
	}
	printf(" \n");*/
}


Biblio *uniques (Biblio *B)
{
   
}

CellMorceau *rechercheParNum_noeuds(Noeud *N, int num) {
	Noeud *cour = N;
	if(N != NULL) {
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				if(L->num == num) {
					return L;
				}
				L = L->suiv;
			}
		}
		
		


CellMorceau * rechercheParNum(Biblio *B, int num) {
	Biblio *biblio_A;
	Biblio *biblio_B;
	Noeud *N = B->A;
	if(N != NULL) {
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				if(L->num == num) {
					return L;
				}
				L = L->suiv;
			}
		}
		biblio_A = B;
		biblio_A->A = B->
		rechercheParNum(A, num);
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	
}

int est_dans(CellMorceau *L, Biblio *B) {

}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	
}


int supprimeMorceau(Biblio *B, int num)
{

}
