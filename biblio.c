#include "biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n) {
	Biblio *B = nouvelle_biblio();
	FILE *fichier = fopen(nom_fichier, "r");
	char *titre;
	char *artiste;
	int taille_buffer;
	char delim;
	int num_morceau;
	int i = 0;
    while(i < n && !end_of_file(fichier)) {
    	parse_int(fichier, &num_morceau);
    	fseek(fichier, 1, SEEK_CUR);
    	delim = '\t';
    	parse_string(fichier, &titre, &taille_buffer, delim);
    	fseek(fichier, 1, SEEK_CUR);
    	delim = '\n';
    	parse_string(fichier, &artiste, &taille_buffer, delim);
    	insere(B, num_morceau, titre, artiste);
    	i ++;
    }
    return B;
}
