CFLAGS= -Wall -std=c99 -g
EXEC=test_graphe test_arbre_minimax
LIBS = -lm

.PHONY: all clean
all: $(EXEC)

graphe.o: graphe.c graphe.h
	$(CC) $(CFLAGS) -o $@ -c $<
arbre_minimax.o: arbre_minimax.c arbre_minimax.h
	$(CC) $(CFLAGS) -o $@ -c $<
test_graphe.o: test_graphe.c
	$(CC) $(CFLAGS) -o $@ -c $<
test_arbre_minimax.o: test_arbre_minimax.c
	$(CC) $(CFLAGS) -o $@ -c $<



test_graphe: graphe.o test_graphe.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
test_arbre_minimax: graphe.o arbre_minimax.o test_arbre_minimax.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean maxclean

clean:
	rm -rf *.o $(EXEC)
