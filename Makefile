# Variables d'environnement et d'options
CC=gcc
EXEC=biblio_arbrelex biblio_liste biblio_tabdyn biblio_hachage

all: $(EXEC)

# table hachage
biblio_hachage: biblio_hachage.o parser.o biblio.o main.o jeu_test.o
	$(CC)  -o biblio_hachage biblio_hachage.o parser.o biblio.o main.o jeu_test.o -lm

#tableau dynamique
biblio_tabdyn: biblio_tabdyn.o parser.o biblio.o main.o jeu_test.o
	$(CC)  -o biblio_tabdyn biblio_tabdyn.o parser.o biblio.o main.o jeu_test.o
#arbre_lexico
biblio_arbrelex: biblio_arbrelex.o parser.o biblio.o main.o jeu_test.o
	$(CC)  -o biblio_arbrelex biblio_arbrelex.o parser.o biblio.o main.o jeu_test.o

#Liste chainee
biblio_liste: biblio_liste.o parser.o biblio.o main.o jeu_test.o
	$(CC)  -o biblio_liste biblio_liste.o parser.o biblio.o main.o jeu_test.o

#fichiers .o
main.o : main.c biblio.h jeu_test.h
	$(CC)  -c main.c

biblio_liste.o: biblio_liste.c biblio_liste.h biblio.h
	$(CC)  -c biblio_liste.c

biblio_tabdyn.o: biblio_tabdyn.c biblio_tabdyn.h biblio.h
	$(CC)  -c biblio_tabdyn.c

biblio_hachage.o: biblio_hachage.c biblio_hachage.h biblio.h
	$(CC)  -c biblio_hachage.c

biblio_arbrelex.o: biblio_arbrelex.c biblio_arbrelex.h biblio.h
	$(CC)  -c biblio_arbrelex.c

parser.o : parser.c parser.h
	$(CC)  -c parser.c

biblio.o: biblio.c biblio.h parser.h
	$(CC)  -c biblio.c
	
jeu_test.o: jeu_test.c jeu_test.h biblio.h biblio_liste.h biblio_tabdyn.h biblio_hachage.h biblio_arbrelex.h
	$(CC)  -c jeu_test.c

#nettoyage
clean:
	rm -f *.o $(EXEC)

