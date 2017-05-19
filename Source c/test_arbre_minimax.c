#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "arbre_minimax.h"

unsigned passed = 0;
unsigned total  = 0;

void test(const char * msg, bool result) {
  printf("%-30s [%s]\n", msg, (result ? "OK" : "--"));
  if (result) passed += 1;
  total += 1;
}

/**
 * Description: Affiche des coordonnées c
 *
 * Précondition: ∅
 */
void coordinates_print(Coordinates c){
	printf("(%d,%d)\n",c.x,c.y);
}

/**
 * Description: retourne la valeur de pion opposé à p, retourne NOIR si p est BLANC est vice versa
 *
 * Précondition: (p=NOIR ⋁ p=BLANC)
 */

char oppositePion(Pion p){
	assert(p==NOIR||p==BLANC);
	return p==NOIR?BLANC:NOIR;
}

int random(int x){
  return rand()%x;
}

int main(void){
	clock_t begin,end;
	Graphe g;
	size_t graphe_size=20;
	ArbreMinimax a;
	Coordinates c;
	Pion p=NOIR;

	g=graphe_create(graphe_size);

	begin=clock();
	while(graphe_detectWinner(g)==VIDE){
		if(p==NOIR){
			a=arbre_minimax_create(g,p);
			test("Test ArbreMinimax create",a!=NULL);
			c=arbre_minimax_getBestMove(a);
			arbre_minimax_destroy(&a);
		}else{
			do{
				c.x=random(graphe_size);
				c.y=random(graphe_size);
			}while(!graphe_isEmptyCell(g,c.x,c.y));
		}

		test("Test ArbreMinimax getBestMove",c.x>-1&&c.x<graphe_size&&c.y>-1&&c.y<graphe_size);
		printf("%s:",p==NOIR?"NOIR":"BLANC");
		coordinates_print(c);
		graphe_insert(&g,p,c.x,c.y);
		graphe_print(g);
		p=oppositePion(p);
	}
	end=clock();
	printf("Time to finish game: %.10f seconds \n",(double) (end-begin)/CLOCKS_PER_SEC);
	


	graphe_destroy(&g);


	printf("Tests %d/%d passed\n", passed, total);
	return total - passed;
}