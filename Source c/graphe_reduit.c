#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "graphe_reduit.h"

struct _graphe_reduit{
	Cell head;
	Cell* groupB; // on memorise les cellules noires
	Cell* groupW; // et les cellules blanches
	Cell* cellsV; // on mémorise les cellules vides pour la destruction
};

/**
 * Description: retourne la position de c dans group->cells[] retourne -1 sinon
 *
 *
 * Précondition: group ≠ NULL ⋀ *group ≠ NULL ⋀ c!=NULL
 */
static int _getIndexCellInGroup(Cell* group, Cell c){
	assert(group!=NULL && c!=NULL);
	for(size_t i=0;group[i]!=NULL;i++)
		if(group[i]==c)
			return i;

	return -1;
}


/**
 * Description: transforme un chaque groupe de groupes de cellules en une unique cellule 
 * Modifie la tête de g s'il le faut
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 *
 */

static Cell* _unifyGroups(GrapheReduit g, Cell** groups, Pion p){
	assert(p==BLANC||p==NOIR);
	size_t temp;
	Cell* group=NULL;
	char c;
	int index;
	size_t size_group=0;
	size_t size_cells;
	if(groups==NULL||*groups==NULL)
		return NULL;


	for(size_t i=0;groups[i]!=NULL;i++){
		group=realloc(group,(++size_group+1)*sizeof(Cell));
		temp=size_group-1;
		group[temp]=malloc(sizeof(struct _cell));
		if(group[temp]==NULL){
			fprintf(stderr, "Allocation mémoire impossible\n");
			return NULL;
		}

		group[temp]->key=p;
		group[temp]->cells=NULL;
		size_cells=0;
		for(size_t j=0;groups[i][j]!=NULL;j++){
			if(groups[i][j]==g->head)
				g->head=group[temp];
			if(groups[i][j]->cells!=NULL)
				for(size_t k=0;k<6;k++){
					if(groups[i][j]->cells[k]!=NULL&&groups[i][j]->cells[k]->key!=p){
						group[temp]->cells=realloc(group[temp]->cells,(++size_cells)*(sizeof(Cell)));
						group[temp]->cells[size_cells-1]=groups[i][j]->cells[k];
						if((c=groups[i][j]->cells[k]->key)!='B'&&c!='W'){
							index=_getIndexCellInGroup(groups[i][j]->cells[k]->cells,groups[i][j]);
							groups[i][j]->cells[k]->cells[index]=group[temp];
						}
					}
				}	
		}
		if(group[temp]->cells!=NULL){
			group[temp]->cells=realloc(group[temp]->cells,(size_cells+1)*(sizeof(Cell)));
			group[temp]->cells[size_cells]=NULL;
		}
	}
	if(group!=NULL)
		group[size_group]=NULL;


	return group;
}


GrapheReduit graphe_reduit_create (Graphe g){
	Graphe f;
	GrapheReduit gr;
	int n;
	size_t k,l;
	Cell c;
	Cell** groupsW;
	Cell** groupsB;
	size_t size_cellsV=0;

	n=graphe_getSize(g);

	gr=malloc(sizeof(struct _graphe_reduit));
	if(gr==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return NULL;
	}
	gr->cellsV=NULL;

	graphe_copy(&f,g);

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if((c=graphe_getCell(f,i,j))->key==VIDE){
				gr->cellsV=realloc(gr->cellsV,(size_cellsV+2)*sizeof(Cell));
				gr->cellsV[size_cellsV++]=c;
			}
		}
	}
	if(gr->cellsV!=NULL)
		gr->cellsV[size_cellsV]=NULL;

	gr->head=graphe_getHead(f);

	groupsW=graphe_getGroups(f,BLANC);
	groupsB=graphe_getGroups(f,NOIR);

	gr->groupW=_unifyGroups(gr,groupsW,BLANC);
	gr->groupB=_unifyGroups(gr,groupsB,NOIR);

	if(groupsW!=NULL){
		for(k=0;groupsW[k]!=NULL;k++){
			for(l=0;groupsW[k][l]!=NULL;l++)
				graphe_freeCell(&groupsW[k][l]);
			free(groupsW[k]);
		}
		free(groupsW);
	}
	if(groupsB!=NULL){
		for(k=0;groupsB[k]!=NULL;k++){
			for(l=0;groupsB[k][l]!=NULL;l++)
				graphe_freeCell(&groupsB[k][l]);
			free(groupsB[k]);
		}
		free(groupsB);
	}
	free(f);

	return gr;

}




void graphe_reduit_destroy (GrapheReduit* g){
	assert(g!=NULL && *g!=NULL);
	size_t i;

	Cell head=(*g)->head;

	graphe_freeCell(&head->cells[0]);
	if(head->key==VIDE){
		graphe_freeCell(&head->cells[5]);
	}else{
		for(i=0;head->cells[i]!=NULL;i++);
		graphe_freeCell(&head->cells[i-1]);
	}

	if((*g)->groupB!=NULL){
		for(i=0;(*g)->groupB[i]!=NULL;i++)
			graphe_freeCell(&(*g)->groupB[i]);
		free((*g)->groupB);
	}

	if((*g)->groupW!=NULL){
		for(i=0;(*g)->groupW[i]!=NULL;i++)
			graphe_freeCell(&(*g)->groupW[i]);
		free((*g)->groupW);
	}

	if((*g)->cellsV!=NULL){
		for(i=0;(*g)->cellsV[i]!=NULL;i++)
			graphe_freeCell(&(*g)->cellsV[i]);
		free((*g)->cellsV);
	}

	free(*g);
}

/**
 * Description: renvoie vrai si c est dans cells, feux sinon
 *
 * Précondition: cells ≠ NULL ⋀ *cells ≠ NULL ⋀ c ≠ NULL
 */

static bool _inArrayOfCell(Cell* cells, Cell c){
	assert(cells!=NULL&&*cells!=NULL&&c!=NULL);
	for(size_t i=0;cells[i]!=NULL;i++)
		if(cells[i]==c)
			return true;
	return false;
}


int graphe_reduit_countPonts(GrapheReduit g, Pion p){
	assert(g!=NULL && (p==NOIR||p==BLANC));

	int count=0;
	Cell* group;
	Cell c;

	if(p==NOIR)
		group=g->groupB;
	else
		group=g->groupW;

	if(group==NULL)
		return count;

	for(size_t i=0; group[i]!=NULL; i++)
		for(size_t j=i+1;group[j]!=NULL; j++)
			for(size_t k=0;(c=group[i]->cells[k])!=NULL;k++)
				if(c->key==VIDE&&_inArrayOfCell(group[j]->cells,c))
					count++;




	return count;
}



