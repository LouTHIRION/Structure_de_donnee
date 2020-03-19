/* biblio_hachage */

#include "biblio_hachage.h"

/*------------------------------------------------------------------------*/

/* Fonction qui calcul une cle en a partir d'une chaine de caractere artiste */
unsigned int fonction_cle(const char *artiste) {
	unsigned int cle = 0;
	int i = 0;
	// fait la somme des valeurs ASCII de chaque lettre
	while(artiste[i] != '\0') {
		cle += artiste[i];
		i++;
	}
	return cle;
}

/* Fonction qui calcul l'indice d'un morceau a partir de sa cle */
unsigned int fonction_hachage(unsigned int cle, int m) {
	/* fait un calcul tres savant pour obtenir un indice
	   qui sera entre 0 et m */
	return floor(m*(cle * A - floor(cle * A)));
}

void insere(Biblio *B, int num, char *titre, char *artiste) {
	// calcul de cle et indice, alloc memoire, ajout valeurs et ajout du morceau dans la biblio
    unsigned int cle = fonction_cle(artiste);
    CellMorceau *L = (CellMorceau *)malloc(sizeof(CellMorceau));
    L->num = num;
    L->titre = titre;
    L->artiste = artiste;
    L->cle = cle;
    /* pour calculer l'indice, on choisit TAILLE_TABLE, 
       cela permettera d'avoir des valeur entre 0 et TAILLE_TABLE */
    int indice = fonction_hachage(cle, TAILLE_TABLE);
    L->suiv = B->T[indice];
    B->T[indice] = L;
    B->nE += 1;
}

/*------------------------------------------------------------------------*/

Biblio *nouvelle_biblio(void) {
	Biblio *B = (Biblio *)malloc(sizeof(Biblio));
	B->nE = 0;
	B->m = TAILLE_TABLE;
	CellMorceau **T = (CellMorceau **)malloc(B->m * sizeof(CellMorceau *));
	// mis a NULL de toutes les cases du tableau
	for(int i = 0; i < B->m; i++) {
		T[i] = NULL;
	}	
	B->T = T;
}

/*------------------------------------------------------------------------*/

void libere_biblio(Biblio *B) {
	CellMorceau **T = B->T;
	int i = 0;
	//libere chaque case du tableau
	for(i; i<B->m; i++) {
		free(T[i]);
	}
	free(T);
	free(B);
}

/*------------------------------------------------------------------------*/

void afficheMorceau(CellMorceau *L) {
	if(L != NULL) {
		printf("n°%d\t", L->num);
		printf("titre: %s\t", L->titre);
		printf("artiste: %s\n", L->artiste);
	}
}

/* Fonction recursive qui va parcourir chaque morceau du tableau pour l'afficher */
void parcour_Morceaux(CellMorceau *L) {
	if(L != NULL) {
		afficheMorceau(L);
		parcour_Morceaux(L->suiv);
	}
}

void affiche_biblio(Biblio *B) {
	printf("nombre de morceaux: %d\n", B->nE);
	if (B != NULL) {
		CellMorceau **T = B->T;
		int i = 0, i_emeElem = 0;
    	while(i_emeElem < B->nE && i < B->m) {
    		/* parcour chaque element du tableau, 
    		   si non NULL alors on affiche la liste */
    		if(T[i] != NULL) {
    			parcour_Morceaux(T[i]);
    			i_emeElem += 1;
    		}
    		i += 1;
    	}
    }
    printf("nombre de morceaux: %d\n", B->nE);
}

/*------------------------------------------------------------------------*/

CellMorceau * rechercheParNum(Biblio *B, int num) {
	CellMorceau **T = B->T;
	int i = 0;
	// parcour chaque elem du tableau 
    while(i < B->m) {
    	if(T[i] != NULL) { // si non NULL
    		CellMorceau *L = T[i];
    		while(L != NULL) { // parcour tout les morceaux de liste chaine
    			// compare les num
    			if(L->num == num) { 
					return L;
				}
				L = L->suiv;
			}
    	}
    	i += 1;
    }
    return NULL;
}

/*------------------------------------------------------------------------*/

CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	CellMorceau **T = B->T;
	int i = 0;
    while(i < B->m) {
    	if(T[i] != NULL) {
    		CellMorceau *L = T[i];
    		while(L != NULL) {
    			// compare les titres
    	 		if (strcmp(L->titre, titre)==0) {
					return L;
				}
				L = L->suiv;
			}
    	}
    	i += 1;
    }
    return NULL;
}

/*------------------------------------------------------------------------*/

Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	// calcul l'indice ou aller chercher le(s) morceau(x)
	unsigned int cle = fonction_cle(artiste);
	int indice = fonction_hachage(cle, TAILLE_TABLE);
	CellMorceau *L = B->T[indice];
	if (L != NULL) {
		Biblio *new_B = nouvelle_biblio();
		while (L != NULL) {
			// on tri les morceaux pour ne garder que ceux de l'artiste
			if(strcmp(L->artiste, artiste)==0) {
				insere(new_B, L->num, L->titre, L->artiste);
			}
			L = L->suiv;
		}
		return new_B;
	}
	return NULL;
}

/*------------------------------------------------------------------------*/

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	if (B != NULL) {
		CellMorceau **T = B->T;
		int i = 0, i_emeElem = 0, new_num = 0;
		// parcour tout le tableau
    	while(i_emeElem < B->nE && i < B->m) {
    		if(T[i] != NULL) {
    			CellMorceau *L = T[i];
    			// parcour la liste de morceau
    			while(L != NULL) {
    				if(L->num >= new_num) {
    					/* pour trouver le plus grand num de la biblio 
    					   et choisir le suivant */
    					new_num = L->num + 1;
    				}
    				L = L->suiv;
    			}
    			i_emeElem += 1;
    		}
    		i += 1;
    	}
    	insere(B, new_num, titre, artiste);
    }
}

/*------------------------------------------------------------------------*/

int supprimeMorceau(Biblio *B, int num) {
	CellMorceau **T = B->T;
	int i = 0;
	// parcour le tableau
    while(i < B->m) {
    	if(T[i] != NULL) {
    		CellMorceau *L = T[i];
    		// soit c'est le premier morceau de la liste qui doit etre supp
    		if(L->num == num) {
    			T[i] = L->suiv;
    			B->nE -= 1;
    			free(L);
    			return 1;
    		}
    		// soit c'est un morceau plus bas dans la liste
    		while(L->suiv != NULL) {
    		 	if(L->suiv->num == num) {
					CellMorceau *suiv = L->suiv;
					L->suiv = suiv->suiv;
					B->nE -= 1;
					free(suiv);
					return 1;
    			}
    			L = L->suiv;
    		}
    	}
    	i += 1;
    }
    return 0;
}

/*------------------------------------------------------------------------*/

int est_dans(CellMorceau *L, Biblio *B) {
	// on se place directement dans la case grace a la cle
	int h = fonction_hachage(fonction_cle(L->artiste), TAILLE_TABLE);
	CellMorceau *M = B->T[h];
	while(M != NULL) {
		// parcour le liste et cheche un morceau similaire
		if(strcmp(L->titre, M->titre)==0 && strcmp(M->artiste, L->artiste)==0) {
			return 1;
		}
		M = M->suiv;
	}
	return 0;
}

/*------------------------------------------------------------------------*/

/* Fonction qui dit si un morceau M se trouve ou non dans une liste liste_M */
int est_dansListeMorceaux(CellMorceau *M, CellMorceau *liste_M) {
	/* meme mecanisme que fonction est_dans sauf 
	   qu'on compare egalement les num pour qu'ils soient different */
	while(liste_M != NULL) {
		if(strcmp(M->titre, liste_M->titre)==0 && M->num != liste_M->num) {
			return 1;
		}
		liste_M = liste_M->suiv;
	}
	return 0;
}

Biblio *uniques (Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau **T = B->T;
		int i = 0, i_emeElem = 0, new_num = 0;
		// parcour le tableau
    	while(i_emeElem < B->nE && i < B->m) {
    		if(T[i] != NULL) {
    			CellMorceau *L = T[i];
    			if(L->suiv != NULL) {
    				// parcour la liste de morceau (si il y a au moins deux morceaux)
    				while(L != NULL) {
    					/* et on ajoute dans la nouvelle bibilo, 
    					   tous les morceaux qui n'ont pas de doublons */
    					if(est_dansListeMorceaux(L, T[i])==0) {
    						insere(new_B, L->num, L->titre, L->artiste);
    					}
    					L = L->suiv;
    				}
    			}
    			else {
    				// si il n'y a qu'un morceau
    				insere(new_B, L->num, L->titre, L->artiste);
    			}
    			i_emeElem += 1;
    		}
    		i += 1;
    	}
    	return new_B;
}

/*------------------------------------------------------------------------*/

