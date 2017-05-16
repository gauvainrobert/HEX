#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graphe.h"


unsigned passed = 0;
unsigned total  = 0;

void test(const char * msg, bool result) {
  printf("%-30s [%s]\n", msg, (result ? "OK" : "--"));
  if (result) passed += 1;
  total += 1;
}

/* 
 * Description: Retourne un entier compris entre 0 et x non inclus
 *
 * Précondition: x>0
 */
int random(int x){
	assert(x>0);
  return rand()%x;
}

int main(void){
	int n=20;
	int x,y;
	char* c;
	Graphe g,f,h,i,k;
	g=graphe_create(n);
	f=graphe_create(2);
	h=graphe_create(3);

	for(int x=0;x<n;x++)
		for(int y=0;y<n;y++)
			test("Empty cell",graphe_isEmptyCell(g,x,y));

	graphe_insert(&g,NOIR,1,1);
	graphe_insert(&g,NOIR,10,1);
	graphe_insert(&g,NOIR,1,2);

	graphe_remove(&g,1,2);

	graphe_insert(&f,BLANC,0,0);
	graphe_insert(&f,BLANC,1,0);
	test("Detect winner",graphe_detectWinner(f)==BLANC);
	graphe_remove(&f,0,0);
	graphe_insert(&f,NOIR,0,0);
	graphe_insert(&f,NOIR,0,1);
	test("Detect winner",graphe_detectWinner(f)==NOIR);
	graphe_remove(&f,1,0);
	graphe_remove(&f,0,1);
	graphe_insert(&f,NOIR,1,1);
	test("Test number of groups",graphe_countGroups(f,NOIR)==2);
	graphe_insert(&f,NOIR,1,0);
	test("Test number of groups",graphe_countGroups(f,NOIR)==1);

	graphe_insert(&h,NOIR,0,0);
	graphe_insert(&h,NOIR,0,1);
	graphe_insert(&h,NOIR,1,2);
	graphe_insert(&h,NOIR,2,0);
	graphe_insert(&h,NOIR,2,2);
	test("Test number of groups",graphe_countGroups(h,NOIR)==3);
	graphe_insert(&h,NOIR,1,1);
	test("Test number of groups",graphe_countGroups(h,NOIR)==1);
	graphe_remove(&h,1,1);
	graphe_insert(&h,NOIR,1,0);
	test("Test number of groups",graphe_countGroups(h,NOIR)==2);
	graphe_insert(&h,NOIR,1,1);
	test("Test number of groups",graphe_countGroups(h,NOIR)==1);
	test("Detect winner",graphe_detectWinner(f)==NOIR);

	for(int i=0; i<1000; i++){
		x=random(n);
		y=random(n);
		if(graphe_isEmptyCell(g,x,y)){
			graphe_insert(&g,NOIR,x,y);
			test("Test insert",!graphe_isEmptyCell(g,x,y));
		}else{
			graphe_remove(&g,x,y);
			test("Test remove",graphe_isEmptyCell(g,x,y));
		}
	}
	printf("Test conversion Graphe vers String:\n");
	c=graphe_toString(g);
	printf("%s\n",c);
	printf("Test conversion String vers Graphe:\n");
	i=graphe_toGraphe(c);
	free(c);
	c=graphe_toString(i);
	printf("Test conversion Graphe vers String:\n");
	printf("%s\n",c);
	free(c);

	for(int i=2; i<50; i++){
		k=graphe_create(i);
		test("Test detect winner in Empty Graphe",graphe_detectWinner(k)==VIDE);
		graphe_destroy(&k);
	}
	graphe_destroy(&g);
	graphe_destroy(&f);
	graphe_destroy(&h);
	graphe_destroy(&i);
	printf("Tests %d/%d passed\n", passed, total);
  return total - passed;
}