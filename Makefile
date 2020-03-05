
all: biblio

biblio: biblio_liste.o biblio.o main.o 
	gcc -o biblio biblio_liste.o biblio.o main.o
	
biblio_liste.o: biblio_liste.c
	gcc -o biblio_liste.o -c biblio_liste.c
	
biblio.o: biblio.c
	gcc -o biblio.o -c biblio.c
	
main.o: main.c
	gcc -o main.o -c main.c
	
clean:
	rm -rf *.o
	
mrpropre: clean
	rm -rf biblio
