/* biblio_hachage */

#include "biblio_hachage.h"

unsigned int fonction_cle(const char *artiste) {
	unsigned int cle = 0;
	int i = 0;
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
    int indice = fonction_hachage(cle, TAILLE_TABLE);
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
	if (B != NULL) {
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
}


CellMorceau * rechercheParNum(Biblio *B, int num) {
	CellMorceau **T = B->T;
	int i = 0;
    while(i < B->m) {
    	if(T[i] != NULL && T[i]->num == num) {
			return T[i];
    	}
    	i += 1;
    }
    return NULL;
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre) {
	CellMorceau **T = B->T;
	int i = 0;
    while(i < B->m) {
    	if(T[i] != NULL && strcmp(T[i]->titre, titre)==0) {
			return T[i];
    	}
    	i += 1;
    }
    return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste) {
	unsigned int cle = fonction_cle(artiste);
	int indice = fonction_hachage(cle, TAILLE_TABLE);
	CellMorceau *L = B->T[indice];
	if (L != NULL) {
		Biblio *new_B = nouvelle_biblio();
		while (L != NULL) {
			if(L->cle == cle) {
				insere(new_B, L->num, L->titre, L->artiste);
			}
			L = L->suiv;
		}
		return new_B;
	}
	return NULL;
}

void insereSansNum(Biblio *B, char *titre, char *artiste) {
	if (B != NULL) {
		CellMorceau **T = B->T;
		int i = 0, i_emeElem = 0, new_num = 0;
    	while(i_emeElem < B->nE && i < B->m) {
    		if(T[i] != NULL) {
    			if(T[i]->num >= new_num) {
    				new_num = T[i]->num + 1;
    			}
    			i_emeElem += 1;
    		}
    		i += 1;
    		//printf("6\n");
    	}
    	insere(B, new_num, titre, artiste);
    }
}


int supprimeMorceau(Biblio *B, int num) {
	CellMorceau **T = B->T;
	int i = 0;
    while(i < B->m) {
    	if(T[i] != NULL) {
    		CellMorceau *L = T[i];
    		if(L->num == num) {
    			T[i] = L->suiv;
    			B->nE -= 1;
    			free(L);
    			return 1;
    		}
    		while(L->suiv != NULL) {
    		 	if(L->suiv->num == num) {
					CellMorceau *suiv = L->suiv;
					L->suiv = suiv->suiv;
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


int est_dans(CellMorceau *L, Biblio *B) {
	int h = fonction_hachage(fonction_cle(L->artiste), TAILLE_TABLE);
	CellMorceau *M = B->T[h];
	while(M != NULL) {
		if(strcmp(L->titre, M->titre)==0) {
			return 1;
		}
		M = M->suiv;
	}
	return 0;
}

Biblio *uniques (Biblio *B) {
	Biblio *new_B = nouvelle_biblio();
	CellMorceau **T = B->T;
		int i = 0, i_emeElem = 0, new_num = 0;
    	while(i_emeElem < B->nE && i < B->m) {
    		if(T[i] != NULL) {
    			CellMorceau *L = T[i];
    			while(L != NULL) {
    				if(est_dans(L, new_B)) {
    					supprimeMorceau(new_B, rechercheParTitre(new_B, L->titre)->num);
    				}
    				else {
    					insereSansNum(new_B, L->titre, L->artiste);
    				}
    				L = L->suiv;
    			}
    			i_emeElem += 1;
    		}
    		i += 1;
    		//printf("6\n");
    	}
    	return new_B;
}


