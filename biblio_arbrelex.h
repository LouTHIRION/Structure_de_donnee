/* biblio_arbrelex.h */

#ifndef _BIBLIO_ARBRELEX_H_
#define _BIBLIO_ARBRELEX_H_

#include "biblio.h"

struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};


typedef struct Noeud {
    struct Noeud *liste_car;	/* liste des choix possibles de caract‘eres */ 
    struct Noeud *car_suiv;		/* caract‘ere suivant dans la cha^ine */
    CellMorceau *liste_morceaux;/* liste des morceaux ayant le m^eme interpr‘ete */ 
    char car;
} Noeud;


struct Biblio {
    int nE; 	/* nombre d’’elements contenus dans l’arbre */ 
    Noeud *A;	/* arbre lexicographique */ 
};



#endif
