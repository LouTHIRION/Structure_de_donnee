/* biblio_tabdyn.h */

#ifndef _BIBLIO_TABDYN_H_
#define _BIBLIO_TABDYN_H_

#include "biblio.h"
#include <math.h>

#define TAILLE_INITIALLE_TAB 1000

struct CellMorceau{
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    int nE;
    int capacite;
    CellMorceau *T;    
};


#endif
