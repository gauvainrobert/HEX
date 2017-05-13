#include <stdio.h>
#include "graphe.h"


unsigned passed = 0;
unsigned total  = 0;

void test(const char * msg, bool result) {
  printf("%-30s [%s]\n", msg, (result ? "OK" : "--"));
  if (result) passed += 1;
  total += 1;
}



int main(void){
	int n=13;
	Graphe g;
	Graphe f;
	g=graphe_create(n);
	f=graphe_create(2);

	for(int x=0;x<n;x++)
		for(int y=0;y<n;y++)
			test("Empty cell",graphe_isEmptyCell(g,x,y));

	graphe_insert(&g,NOIR,1,1);
	graphe_insert(&g,NOIR,10,1);
	graphe_insert(&g,NOIR,1,2);

	graphe_remove(&g,1,2);

	graphe_insert(&f,BLANC,0,0);
	graphe_insert(&f,BLANC,0,1);

	test("Detect winner",graphe_detectWinner(f)==BLANC);


	graphe_destroy(&g);
	printf("Tests %d/%d passed\n", passed, total);
  return total - passed;
}