#include <assert.h>
#include <time.h>
#include "graphe_reduit.h"


unsigned passed = 0;
unsigned total  = 0;

void test(const char * msg, bool result) {
  printf("%-30s [%s]\n", msg, (result ? "OK" : "--"));
  if (result) passed += 1;
  total += 1;
}

/** 
 * Description: Retourne un entier compris entre 0 et x non inclus
 *
 * Précondition: x>0
 */
int random(int x){
	assert(x>0);
  return rand()%x;
}

int main(void){
	clock_t begin,end;
	int x,y;
	int n=2;
	Graphe g,h,k;
	GrapheReduit f,i,l;

	g=graphe_create(n);
	for(int i=0; i<n; i++){
		x=random(n);
		y=random(n);
		if(graphe_isEmptyCell(g,x,y)){
			graphe_insert(&g,NOIR,x,y);
		}
	}
	graphe_print(g);

	f=graphe_reduit_create(g);

	begin=clock();
	h=graphe_create(3);
	graphe_insert(&h,NOIR,0,0);
	graphe_insert(&h,NOIR,0,1);
	graphe_insert(&h,NOIR,1,0);
	graphe_insert(&h,NOIR,1,2);
	graphe_insert(&h,NOIR,2,1);
	graphe_insert(&h,NOIR,2,2);
	graphe_print(h);
	i=graphe_reduit_create(h);

	test("Test count bridges",graphe_reduit_countPonts(i,NOIR)==4);
	end=clock();
	printf("Time to finish game: %.10f seconds \n",(double) (end-begin)/CLOCKS_PER_SEC);
	begin=clock();
	k=graphe_create(2);
	graphe_insert(&k,NOIR,0,0);
	graphe_insert(&k,NOIR,1,1);
	graphe_print(k);
	l=graphe_reduit_create(k);

	test("Test count bridges",graphe_reduit_countPonts(l,NOIR)==2);
	end=clock();
	printf("Time to finish game: %.10f seconds \n",(double) (end-begin)/CLOCKS_PER_SEC);

	graphe_destroy(&k);
	graphe_reduit_destroy(&l);

	begin=clock();
	k=graphe_create(3);
	graphe_insert(&k,NOIR,0,0);
	graphe_insert(&k,NOIR,0,1);
	graphe_insert(&k,NOIR,0,2);
	graphe_insert(&k,NOIR,1,0);
	graphe_insert(&k,NOIR,1,2);
	graphe_insert(&k,NOIR,2,0);
	graphe_insert(&k,NOIR,2,1);
	graphe_insert(&k,NOIR,2,2);
	graphe_print(k);
	l=graphe_reduit_create(k);



	test("Test count bridges",graphe_reduit_countPonts(l,NOIR)==0);
	end=clock();
	printf("Time to finish game: %.10f seconds \n",(double) (end-begin)/CLOCKS_PER_SEC);



	graphe_destroy(&g);
	graphe_destroy(&h);
	graphe_destroy(&k);
	graphe_reduit_destroy(&i);
	graphe_reduit_destroy(&f);
	graphe_reduit_destroy(&l);
	printf("Tests %d/%d passed\n", passed, total);
  return total - passed;
}