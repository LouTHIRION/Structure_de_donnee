/* biblio_arbrelex.c */

#include "biblio_arbrelex.h"

/*------------------------------------------------------------------------*/

/* Fonction qui cherche et/ou creer le(s) noeud(s) a partir de l'artiste*/
Noeud *rechercheOuCreer_artiste(Biblio *B, char *artiste) {
	int i = 0; //entier pour parcourir la chaine artiste
	Noeud *cour = B->A; //Noeud courant
	Noeud *prec = cour; //Noeud precedent
	int newLettreOuPas = 0; //booleen qui dit si on doit creer un nouveau noeud dans la liste_car
	// boucle qui parcourt l'arbre pour trouver le noeud de l'artiste
	while(cour != NULL && artiste[i] != '\0') {
		prec = cour;
		if (artiste[i] == cour->car) {
			cour = cour->car_suiv;
			i++;
		}
		else {
			cour = cour->liste_car;
			if(cour == NULL) { 
				// au moins une lettre mais liste_car est vide
				newLettreOuPas = 1;
			}
		}
	}
	// si ce noeud existe on le retourne 
	if (cour != NULL || artiste[i] == '\0') {
		return prec;
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
	else if (i == 0 || newLettreOuPas) { 
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

void insere(Biblio *B, int num, char *titre, char *artiste) {
	Noeud *N = rechercheOuCreer_artiste(B, artiste); // cherche ou creer le(s) noeud(s)
	// alloc memoire, nouvelles valeurs, ajout du morceau dans la liste;
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->num = num;
	L->titre = titre;
	L->artiste = artiste;
	L->suiv = N->liste_morceaux;
	N->liste_morceaux = L;
	B->nE ++;
}

/*------------------------------------------------------------------------*/

Biblio *nouvelle_biblio(void) {
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->A = NULL;
	B->nE = 0;
}

/*------------------------------------------------------------------------*/

void libere_noeuds(Noeud *N) {
	//libere noeuds
	if (N != NULL) {
		Noeud *A = N->liste_car;
		Noeud *B = N->car_suiv;
		libere_noeuds(A);
		libere_noeuds(B);
		// libere morceaux
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

/*------------------------------------------------------------------------*/

void afficheMorceau(CellMorceau *L) {
	printf("n°%d\t", L->num);
	printf("titre: %s\t", L->titre);
	printf("artiste: %s\n", L->artiste);
}

/* Fonction recursive qui parcour les morceaux d'une liste chainee 
   pour les afficher */
void parcour_Morceaux(CellMorceau *L) {
	if(L != NULL) {
		afficheMorceau(L);
		parcour_Morceaux(L->suiv);
	}
}

/* Fonction recursive qui parcour un arbre de noeud en noeud */
void parcour_noeuds(Noeud *N, int i) {
	Noeud *cour = N;
	while(cour != NULL) {
		//printf("%d %c\n", i, cour->car);
		parcour_noeuds(cour->car_suiv, i+1);
		parcour_Morceaux(cour->liste_morceaux);
		cour = cour->liste_car;
	}
}

void affiche_biblio(Biblio *B) {
	printf("nombre de morceaux: %d\n", B->nE);
    parcour_noeuds(B->A, 0);
    printf("nombre de morceaux: %d\n", B->nE);
}

/*------------------------------------------------------------------------*/

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
		CellMorceau *M = rechercheParNum_noeuds(N_1, num);
		if(M == NULL) {
			return rechercheParNum_noeuds(N_2, num);
		}
		else {
			return M;
		}
	}
	return NULL; // renvoie NULL si le noeud n'existe pas
}
		
CellMorceau * rechercheParNum(Biblio *B, int num) {
	return rechercheParNum_noeuds(B->A, num);
}

/*------------------------------------------------------------------------*/

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
		CellMorceau *M = rechercheParTitre_noeuds(N_1, titre);
		if(M == NULL) {
			return rechercheParTitre_noeuds(N_2, titre);
		}
		else {
			return M;
		}
	}
	return NULL; // renvoie NULL si le noeud n'existe pas
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	return rechercheParTitre_noeuds(B->A, titre);
}

/*------------------------------------------------------------------------*/

Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	Biblio *new_B = nouvelle_biblio();
	Noeud *cour = B->A; // noeud courant
	Noeud *prec = cour; // noeud precedent
	int i = 0; // index de la chaine artiste
	// Boucle qui parcour l'arbre jusqu'a trouver le noeud de l'artiste
	while(cour != NULL && artiste[i] != '\0') {
		prec = cour;
		if(cour->car == artiste[i]) {
			cour = cour->car_suiv;
			i++;
		}
		else {
			cour = cour->liste_car;
		}
	}
	if(artiste[i] == '\0') {
		CellMorceau *L = prec->liste_morceaux;
		// Une fois le noeud trouve, on ajoute tous ses morceaux dans une nouvelle bibilo
		while(L != NULL) {
			insere(new_B, L->num, L->titre, L->artiste);
			L = L->suiv;
		}
	}
	return new_B;
}

/*------------------------------------------------------------------------*/

/* Fonction recursive de recherche de morceau par numero */
int supprimeMorceau_noeuds(Noeud *N, int num) {
	if(N != NULL) { // si le noeud existe
		// recherche du morceau dans la liste du noeud
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			CellMorceau *suiv = L->suiv;
			// si il n'y a qu'un seul morceau
			if(L->num == num && suiv == NULL) {
				N->liste_morceaux = NULL;
				free(L);
				return 1;
			}
			// si il y en a plusieurs
			while(suiv != NULL) {
				// cette fois on cherche le morceau precedent
				if (suiv->num == num) {
					L->suiv = suiv->suiv;
					free(suiv);
					return 1;
				}
				L = suiv;
				suiv = suiv->suiv;
			}
		}
		// appelle recursif de la fonction pour les noeuds suivants
		Noeud *N_1 = N->liste_car;
		Noeud *N_2 = N->car_suiv;
		// return les valeurs des appels suivants
		return supprimeMorceau_noeuds(N_2, num) || supprimeMorceau_noeuds(N_1, num);
	}
	return 0; // renvoie 0 si le noeud n'existe pas
}

int supprimeMorceau(Biblio *B, int num) {
	if(supprimeMorceau_noeuds(B->A, num)==0) {
		return 0;
	}
	B->nE -=1;
	return 1;
}

/*------------------------------------------------------------------------*/

/* Fonction recursive de choi d'un num pour un morceau */
int rechercheNum_noeuds(Noeud *N, int num) {
	if(N != NULL) { // si le noeud existe
		// compare notre num avec ceux des morceaux
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				// on prend le num le plus grand et on lui incremente 1
				if (L->num >= num) {
					num = L->num + 1;
				}
				L = L->suiv;
			}
		}
		// appelle recursif de la fonction pour les noeuds suivants
		Noeud *N_1 = N->liste_car;
		Noeud *N_2 = N->car_suiv;
		/* par cette condition,ci-dessous on synchronise les return de tous 
		   les appelles a la fonction pour qu'a la fin le dernier 
		   return renvoie le num cherche */
		int new_num1 = rechercheNum_noeuds(N_1, num);
		int new_num2 = rechercheNum_noeuds(N_2, num);
		if(new_num1 < new_num2) {
			return new_num2;
		}
		else {
			return new_num1;
		}
	}
	return num; // renvoie num si le noeud n'existe pas
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	int num = 0;
	num = rechercheNum_noeuds(B->A, num);
	insere(B, num, titre, artiste);
}

/*------------------------------------------------------------------------*/

int est_dans(CellMorceau *L, Biblio *B) {
	Biblio *artiste = extraireMorceauxDe(B, L->artiste);
	return rechercheParTitre(artiste, L->titre) != NULL;
}

/*------------------------------------------------------------------------*/

/* Fonction qui dit si un morceau M se trouve ou non dans une liste liste_M */
int est_dansListeMorceaux(CellMorceau *M, CellMorceau *liste_M) {
	while(liste_M != NULL) {
		// si meme titre et num different, pas besoin de tester l'artiste 
		if(strcmp(liste_M->titre, M->titre)==0 && M->num != liste_M->num) {
			return 1;
		}
		liste_M = liste_M->suiv;
	}
	return 0;
}

/* Fonction qui ajoute un morceau M a la liste des morceau du noeud N */
void ajouteMorceau(CellMorceau *M, Noeud *N) {//CellMorceau *liste_M) {
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->num = M->num;
	L->titre = M->titre;
	L->artiste = M->artiste;
	L->suiv = N->liste_morceaux;
	N->liste_morceaux = L;
}

/* Fonction recursive qui creer les noeuds pour la nouvelle biblio 
   et qui n'y ajoute que les morceaux sans doublons */
int rechercheUniques_noeuds(Noeud *N, Noeud *new_N, int *nE) {//Biblio *B) {
	if(N != NULL) { // si le noeud existe
		// allocation memoire (si necessaire) des noeuds suivants
		if(N->liste_car != NULL) {
			new_N->liste_car = (Noeud *)malloc(sizeof(Noeud));
		}
		else {
			new_N->liste_car = NULL;
		}
		if(N->car_suiv != NULL) {
			new_N->car_suiv = (Noeud *)malloc(sizeof(Noeud));
		}
		else {
			new_N->car_suiv = NULL;
		}
		new_N->liste_morceaux = NULL;
		new_N->car = N->car;
		
		if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			if(L->suiv != NULL) {
				/* si il y a au moins deux morceaux, 
				   on les compare tous entre eux pour trouver des doublons*/
				while(L != NULL) {
					if(est_dansListeMorceaux(L, N->liste_morceaux)==0) {
						ajouteMorceau(L, new_N);
						*nE += 1;
					}
					L = L->suiv;
				}
			}
			else {
				ajouteMorceau(N->liste_morceaux, new_N);
				*nE += 1;
			}
		}
	// appel recursif de la fonction pour les noeuds suivants
	rechercheUniques_noeuds(N->liste_car, new_N->liste_car, nE);
	rechercheUniques_noeuds(N->car_suiv, new_N->car_suiv, nE);
	}

}

Biblio *uniques (Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	new_B->A = (Noeud *)malloc(sizeof(Noeud));
	rechercheUniques_noeuds(B->A, new_B->A, &new_B->nE);
	return new_B;
}

/*------------------------------------------------------------------------*/


