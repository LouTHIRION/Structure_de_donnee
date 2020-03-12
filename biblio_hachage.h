/* biblio_hachage.h */

#ifndef _BIBLIO_HACHAGE_H_
#define _BIBLIO_HACHAGE_H_

#include "biblio.h"
#include <math.h>

#define TAILLE_TABLE 60000
#define A 0.6180339887498949


struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
};


struct Biblio {
    int nE;	/* nombre d'element contenus dans la table de hachage*/
    int m;	/* taille de la table de hachage */
    CellMorceau **T;    /* table avec resolution des colisions par chainage */
};


#endif
