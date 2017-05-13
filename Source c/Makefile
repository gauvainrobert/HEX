CFLAGS= -Wall -std=c99 -g
EXEC=test_graphe

.PHONY: all clean
all: $(EXEC)

graphe.o: graphe.c graphe.h
	$(CC) $(CFLAGS) -o $@ -c $<
test_graphe.o: test_graphe.c
	$(CC) $(CFLAGS) -o $@ -c $<



test_graphe: graphe.o test_graphe.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean maxclean

clean:
	rm -rf *.o $(EXEC)
