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
    /*Noeud *N = B->A;
	while(N != NULL) {
		printf("%c %c ", N->car, N->car_suiv->car);
		N = N->liste_car;
	}
	printf(" \n");*/
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


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	Biblio *new_B = nouvelle_biblio();
	Noeud *cour = B->A;
	Noeud *prec = cour;
	int i = 0;
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
		while(L != NULL) {
			insere(new_B, L->num, L->titre, L->artiste);
			L = L->suiv;
		}
	}
	return new_B;
}


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


int est_dans(CellMorceau *L, Biblio *B) {
	Biblio *artiste = extraireMorceauxDe(B, L->artiste);
	return rechercheParTitre(artiste, L->titre) != NULL;
}

/*int est_dansListeMorceaux(CellMorceau *M, CellMorceau *liste_M) {
	//CellMorceau *prec_liste_M = liste_M;
	liste_M = liste_M;//->suiv;
	//parcour_Morceaux(liste_M);
	while(liste_M != NULL) {
		if(strcmp(liste_M->titre, M->titre)==0 && strcmp(liste_M->artiste, M->artiste)==0 && liste_M->num != M->num) {
			/*prec_liste_M->suiv = liste_M->suiv;
			free(liste_M);
			printf("jhfhgisdufh\n");
			return 1;
			//return liste_M;
		}
		
		//prec_liste_M = prec_liste_M->suiv;
		liste_M = liste_M->suiv;
		/*if(liste_M == NULL) {
			printf("sdflnsmdfj\n");
		}
		//afficheMorceau(liste_M);
	}
	return 0;
}*/

int est_dansListeMorceaux(CellMorceau *M, CellMorceau *liste_M) {
	while(liste_M != NULL) {
		if(strcmp(M->titre, liste_M->titre)==0 && strcmp(M->artiste, liste_M->artiste)==0 && M->num != liste_M->num) {
			return 1;
		}
		liste_M = liste_M->suiv;
	}
	return 0;
}

void ajouteMorceau(CellMorceau *M, CellMorceau *liste_M) {
	while(liste_M->suiv != NULL) {
		liste_M = liste_M->suiv;
	}
	CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
	L->num = M->num;
	L->titre = M->titre;
	L->artiste = M->artiste;
	liste_M->suiv = L;
}

void supprimeCellMorceau(CellMorceau *M, CellMorceau *liste_M) {
	CellMorceau *prec_liste_M = liste_M;
	liste_M = liste_M->suiv;
	while((strcmp(liste_M->titre, M->titre)!=0 || strcmp(liste_M->artiste, M->artiste)!=0) && liste_M->suiv != NULL) {
		prec_liste_M = liste_M;
		liste_M = liste_M->suiv;
	}
	if(liste_M->suiv != NULL) {
		prec_liste_M->suiv = liste_M->suiv;
		free(liste_M);
	}
}

/* fonction recursive qui cherche les doublons */
void rechercheUniques_noeuds(Noeud *N, Noeud *new_N, int *nE) {//Biblio *B) {
	if(N != NULL) { // si le noeud existe
		//new_N = (Noeud *)malloc(sizeof(Noeud)); // allocation memoire de notre nouveau noeud 
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
		// compare notre num avec ceux des morceaux
		if(N->liste_morceaux != NULL) {
			if(N->liste_morceaux->suiv != NULL) {
				CellMorceau *L = N->liste_morceaux;
				//CellMorceau *liste_sansDouble = (CellMorceau *)malloc(sizeof(CellMorceau));
				printf("-\n-\n");
				while(L != NULL) {
					afficheMorceau(L);
					printf("%d\n", est_dansListeMorceaux(L, N->liste_morceaux));
					if(est_dansListeMorceaux(L, N->liste_morceaux)) {
						printf("2\n");
						*nE -=1;
					}
					/*else {
						ajouteMorceau(L, liste_sansDouble);
					}*/
					L = L->suiv;
				}
			}
				
				
				
				
				//parcour_Morceaux(N->liste_morceaux);
				/*printf("M:\n");
				afficheMorceau(N->liste_morceaux);
				printf("suiv\n");
				
				CellMorceau *L = N->liste_morceaux;
				CellMorceau *liste_sansDouble = (CellMorceau *)malloc(sizeof(CellMorceau));
				CellMorceau *liste_Doublons = (CellMorceau *)malloc(sizeof(CellMorceau));
				ajouteMorceau(L, liste_sansDouble);
				L = L->suiv;
				if(L->suiv != NULL) {
				afficheMorceau(L->suiv);}
				//liste_sansDouble = liste_sansDouble->suiv;
				while(L != NULL) {
					printf("2\n");
					/*CellMorceau *M = est_dansListeMorceaux(L, liste_sansDouble)
					if(M != NULL) {
						printf("3\n");
						supprimeCellMorceau(M, liste_sansDouble);
						*nE -= 1;
					}*
					//parcour_Morceaux(liste_sansDouble);
					if(est_dansListeMorceaux(L, )) {
						printf("3\n");
						*nE -= 2;
					}
					else {
						printf("4\n");
						ajouteMorceau(L, liste_sansDouble);
					}
					printf("5\n");
					L = L->suiv;
				}
				/*printf("-\n");
				parcour_Morceaux(liste_sansDouble->suiv);
				printf("-\n\n");*
				new_N->liste_morceaux = liste_sansDouble->suiv;
				free(liste_sansDouble);*/
			//}
			//else {
				new_N->liste_morceaux = N->liste_morceaux;
			//}
		}
		/*if(N->liste_morceaux != NULL) {
			CellMorceau *L = N->liste_morceaux;
			while(L != NULL) {
				afficheMorceau(L);
				printf("1\n");
				affiche_biblio(B);
				if (est_dans(L, B)) {
					printf("2\n");
					supprimeMorceau(B, rechercheParTitre(B, L->titre)->num);
				}
				else {
					printf("3\n");
					insereSansNum(B, L->titre, L->artiste);
					//afficheMorceau(L);
				}
				printf("4\n");
				L = L->suiv;
			}
		}*/
		
		// appelle recursif de la fonction pour les noeuds suivants
		//Noeud *N_1 = N->liste_car;
		//Noeud *N_2 = N->car_suiv;
		/* par cette condition,ci-dessous on synchronise les return de tous 
		   les appelles a la fonction pour qu'a la fin le dernier 
		   return renvoie le num cherche */
		rechercheUniques_noeuds(N->liste_car, new_N->liste_car, nE);//B);
		rechercheUniques_noeuds(N->car_suiv, new_N->car_suiv, nE);
	}
}

Biblio *uniques (Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	new_B->A = (Noeud *)malloc(sizeof(Noeud));
	int *nE;
	*nE = B->nE;
	rechercheUniques_noeuds(B->A, new_B->A, nE);
	new_B->nE = *nE;
	return new_B;
}




