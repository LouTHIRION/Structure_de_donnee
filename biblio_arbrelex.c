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
		cour->liste_morceaux = NULL;
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
		cour->liste_morceaux = NULL;
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
		cour->liste_morceaux = NULL;
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

/* Fonction recursive de recherche de morceau par numero */
CellMorceau *rechercheParNum_noeuds(Noeud *N, int num) {
	if(N != NULL) { // si le noeud existe
		// recherche du morceau dans la liste du noeud
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				if (L->num == num) {
					return L;
				}
				L = L->suiv;
			}
		}
		// appelle recursif de la fonction pour les noeuds suivants
		Noeud *N_1 = N->liste_car;
		Noeud *N_2 = N->car_suiv;
		/* par cette condition,ci-dessous on synchronise les return de tous 
		   les appelles a la fonction pour qu'a la fin le dernier 
		   return renvoie le morceau cherche */
		if(rechercheParNum_noeuds(N_1, num) == NULL) {
			return rechercheParNum_noeuds(N_2, num);
		}
		else {
			return rechercheParNum_noeuds(N_1, num);
		}
	}
	return NULL; // renvoie NULL si le noeud n'existe pas
}
		
CellMorceau * rechercheParNum(Biblio *B, int num) {
	return rechercheParNum_noeuds(B->A, num);
}


/* Fonction recursive de recherche de morceau par titre
	idem que pour la rechreche par numero */
CellMorceau *rechercheParTitre_noeuds(Noeud *N, char *titre) {
	if(N != NULL) { // si le noeud existe
		// recherche du morceau dans la liste du noeud
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				if (strcmp(L->titre, titre)==0) {
					return L;
				}
				L = L->suiv;
			}
		}
		// appelle recursif de la fonction pour les noeuds suivants
		Noeud *N_1 = N->liste_car;
		Noeud *N_2 = N->car_suiv;
		/* par cette condition,ci-dessous on synchronise les return de tous 
		   les appelles a la fonction pour qu'a la fin le dernier 
		   return renvoie le morceau cherche */
		if(rechercheParTitre_noeuds(N_1, titre) == NULL) {
			return rechercheParTitre_noeuds(N_2, titre);
		}
		else {
			return rechercheParTitre_noeuds(N_1, titre);
		}
	}
	return NULL; // renvoie NULL si le noeud n'existe pas
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	return rechercheParTitre_noeuds(B->A, titre);
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	
}

int est_dans(CellMorceau *L, Biblio *B) {

}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	
}


int supprimeMorceau(Biblio *B, int num)
{

}
