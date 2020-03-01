/* biblio.c */

#include <stdio.h>
#include <stdlib.h>

typedef struct CellMorceau {
	struct CellMorceau *suiv;
	int num;
	char *titre;
	char *artiste;
} CellMorceau;

struct Biblio {
	CellMorceau *L; /* Liste chainee des morceaux */
	int nE; 	/* Nombre de morceaux dans la liste */
};
