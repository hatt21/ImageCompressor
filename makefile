CC= gcc
LDFLAGS= -lMLV -lm

calc:
	$(CC) -o projet src/approximation.c src/affichage.c src/sauvegarde.c src/minimisation.c src/main.c $(LDFLAGS)
	
clean:
	rm -rf *.o
