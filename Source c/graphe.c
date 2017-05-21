#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "graphe.h"


struct _cell{
	char key;
	Cell* cells;
};
struct _graphe{
	Cell head;
	Cell** groupsW; // memorise les groupes de cellules blanches
	size_t size_groupsW;
	Cell** groupsB; // memorise les groupes de cellules noires
	size_t size_groupsB;
	int size;
};

/**
 * Description: retourne une cellule avec le caractère key et les pointeurs de la cellule à NULL
 *
 * Numérotation des pointeurs:
 *
 *                0/\1
 *               5|  |2
 *                4\/3
 */

static Cell _createCell(char key){
	Cell c=malloc(sizeof(struct _cell));
	if(c==NULL){
		fprintf(stderr, "Allocation mémoire impossible.\n");
		return NULL;
	}
	c->cells=malloc(6*sizeof(Cell));
	if(c->cells==NULL){
		fprintf(stderr, "Allocation mémoire impossible.\n");
		return NULL;
	}
	c->key=key;
	for(int i=0; i<6; i++)
		c->cells[i]=NULL;
	return c;
}


Graphe graphe_create(int n){
	assert(n>1);
	Graphe g;
	Cell w,b; // les cotés
	Cell* temp;
	int x,y; // cordonnées d'une case
	int n_carre=n*n;

	w=_createCell('W');
	b=_createCell('B');

	g=malloc(sizeof(struct _graphe));

	if(g==NULL){
		fprintf(stderr,"Allocation mémoire impossible.\n");
		return NULL;
	}

	temp=malloc(n_carre*sizeof(Cell));

	if(temp==NULL){
		fprintf(stderr,"Allocation mémoire impossible.\n");
		return NULL;
	}

	for(int i=0; i<n_carre;i++)
		temp[i]=_createCell(VIDE);


	for(int i=0; i<n_carre;i++){
		x=i/n;
		y=i%n;

		if(y==0){
			temp[i]->cells[4]=b;
			temp[i]->cells[5]=b;
		}else{
			temp[i]->cells[5]=temp[i-1];
			if(x!=n-1)
				temp[i]->cells[4]=temp[i+n-1];
		}

		if(y==n-1){
			temp[i]->cells[1]=b;
			temp[i]->cells[2]=b;
		}else{
			temp[i]->cells[2]=temp[i+1];
		}

		if(x==0){
			temp[i]->cells[0]=w;
			temp[i]->cells[1]=w;
		}else{
			temp[i]->cells[0]=temp[i-n];
			if(y!=n-1)
				temp[i]->cells[1]=temp[i-n+1];
		}

		if(x==n-1){
			temp[i]->cells[3]=w;
			temp[i]->cells[4]=w;
		}else{
			temp[i]->cells[3]=temp[i+n];
		}
	}


	g->head=temp[0];
	g->size=n;
	g->groupsB=NULL;
	g->groupsW=NULL;
	g->size_groupsW=0;
	g->size_groupsB=0;
	free(temp);
	return g;
}

char* graphe_toString(Graphe g){
	Cell itr,mem;
	int n=g->size;
	int i=0;
	char* c=malloc((n*n)+1);

	itr=g->head;
	mem=itr;
	for(;itr->key!='W';i++){

		if(itr->key==VIDE)
			c[i]=itr->key;
		else
			c[i]=itr->key==BLANC?'o':'*';

		if(itr->cells[2]->key=='B'){
			itr=mem->cells[3];
			mem=itr;
		}else{
			itr=itr->cells[2];
		}
	}
	c[i]='\0';
	return c;
}

void graphe_print(Graphe g){
	Cell itr,mem;
	int n=g->size;
	int j=1;
	for(int i=0;i<n;i++)
		printf("W ");
	printf("W/B\n");

	itr=g->head;
	mem=itr;
	for(;itr->key!='W';){
		if(itr->cells[5]->key=='B'){
			printf("%*s", j, "");
			printf("B ");
		}
		if(itr->key==VIDE)
			printf("%c ",itr->key);
		else
			printf("%s ",itr->key==BLANC?"o":"*");

		if(itr->cells[2]->key=='B'){
			printf("B\n");
			j++;
			itr=mem->cells[3];
			mem=itr;
		}else{
			itr=itr->cells[2];
		}
	}

	printf("%*s", n+1, "");
	printf("B/W ");
	for(int i=0;i<n;i++)
		printf("W ");
	printf("\n");
}

Graphe graphe_toGraphe(char* c){
	Graphe g;
	size_t c_len;
	int n=(int)sqrt((double)(c_len=strlen(c)));
	char car;
	Pion p;
	g=graphe_create(n);
	for(size_t i=0;i<c_len;i++){
		car=c[i];
		if(car=='o'||car=='*'){
			p=car=='o'?BLANC:NOIR;
			graphe_insert(&g,p,i/n,i%n);
		}
	}
	return g;
}

/**
 * Description: libère la mémoire d'une cellule c
 * 
 * Précondition: c ≠ NULL ⋀ *c ≠ NULL
 */

static void _freeCell(Cell* c){
	assert(c!=NULL && *c!=NULL);
	free((*c)->cells);
	free(*c);
}

void graphe_destroy(Graphe* g){
	Cell itr,mem1,mem2;
	Cell** groupsW=(*g)->groupsW;
	Cell** groupsB=(*g)->groupsB;
	size_t i;

	for(i=0;i<(*g)->size_groupsB;i++)
		free(groupsB[i]);
	free(groupsB);

	for(i=0;i<(*g)->size_groupsW;i++)
		free(groupsW[i]);
	free(groupsW);


	itr=(*g)->head;
	mem1=itr->cells[3];
	
	for(;itr->cells[2]->key!='B'||itr->cells[3]->key!='W';){
		if(itr->cells[2]->key=='B'){
			_freeCell(&itr);
			itr=mem1;
			mem1=itr->cells[3];
		}else{
			mem2=itr->cells[2];
			_freeCell(&itr);
			itr=mem2;
		}
	}
	_freeCell(&itr->cells[2]);
	_freeCell(&itr->cells[3]);
	_freeCell(&itr);
	free(*g);

}

/**
 * Description: retourne la cellule de cordonnées (x,y) du graphe g
 * 
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 * g ≠ NULL ⋀ *g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 */

static Cell _getCell(Graphe g, int x, int y){
	assert(g!=NULL && x>=0 && x<g->size && y>=0 && y<g->size);
	Cell c=g->head;
	int i;
	for(i=0;i<x;i++)
		c=c->cells[3];
	for(i=0;i<y;i++)
		c=c->cells[2];
	return c;
}

bool graphe_isEmptyCell(Graphe g, int x, int y){
	assert(g!=NULL && x>=0 && x<g->size && y>=0 && y<g->size);
	return graphe_getCellContent(g,x,y)==VIDE;
}

/**
 * Description: permet de déterminer si les au moins une des arrêtes d'une cellule c pointe vers une cellule
 * d'un groupe de cellule
 *
 * Précondition: c!=NULL ⋀ group!=NULL
 */

static bool _asCellInCommon(Cell* group, Cell c){
	assert(c!=NULL && group!=NULL && *group!=NULL);

	for(int i=0;group[i]!=NULL;++i)
		for(int j=0;j<6;j++)
			if(c->cells[j]==group[i])
				return true;
	return false;
}

/**
 * Description: permet de placer une cellule c dans le bon groupe de cellules du graphe
 * et permet de fusionner des groupes de cellules si c possède des arrêtes communes entre des cellules
 * de ces deux groupes.
 *
 * Précondition: g!=NULL ⋀ c!=NULL ⋀ (c->key==NOIR ⋁ c->key==BLANC)
 */

static void _insertIntoGroups(Graphe g, Cell c){
	assert(g!=NULL && c!=NULL && (c->key==BLANC||c->key==NOIR));
	Cell*** groups;
	Cell* temp;
	size_t size_temp=1;
	size_t* size_groups;
	size_t j;
	if(c->key==NOIR){
		groups=&g->groupsB;
		size_groups=&g->size_groupsB;
	}else{
		groups=&g->groupsW;
		size_groups=&g->size_groupsW;
	}

	temp=malloc(2*sizeof(Cell));
	if(temp==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return;
	}
	temp[0]=c;
	temp[1]=NULL;

	for(size_t i=0;i<(*size_groups);){
		if(_asCellInCommon((*groups)[i],c)){
			// on recopie les cellules de *groups[i] dans temp
			for(j=0;(*groups)[i][j]!=NULL;j++){
				temp=(Cell*)realloc(temp,(++size_temp+1)*sizeof(Cell));
				if(temp==NULL){
					fprintf(stderr, "Allocation mémoire impossible\n");
					return;
				}
				temp[size_temp-1]=(*groups)[i][j];
				temp[size_temp]=NULL;
			}
			free((*groups)[i]);
			for(j=i;j<(*size_groups)-1;j++)
				(*groups)[j]=(*groups)[j+1];
			*groups=(Cell**)realloc(*groups,--(*size_groups)*sizeof(Cell*));
		}else{
			i++;
		}
	}
	*groups=(Cell**)realloc(*groups,(++(*size_groups)+1)*sizeof(Cell*));
	if((*groups)==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return;
	}
	(*groups)[(*size_groups)-1]=temp;
	(*groups)[(*size_groups)]=NULL;
}

Graphe graphe_insert(Graphe* g, Pion p, int x, int y){
	assert(g!=NULL&&*g!=NULL&&x>=0&&x<(*g)->size&&y>=0&&y<(*g)->size&&
		p==BLANC||p==NOIR&&graphe_getCellContent(*g,x,y)==VIDE);
	Cell c=_getCell(*g,x,y);
	c->key=p;

	_insertIntoGroups(*g,c);

	return (*g);
}

/**
 * Description: renvoie vrai si c appartient à group, faux sinon
 *
 * Précondition: group!=NULL ⋀ *group!=NULL ⋀ c!=NULL
 */

static bool _cellInGroup(Cell* group, Cell c){
	assert(group!=NULL && *group!=NULL && c!=NULL);
	for(size_t i=0;group[i]!=NULL;i++)
		if(group[i]==c)
			return true;
	return false;
}

/**
 * Description: permet de retirer une cellule c du bon groupe de cellules du graphe auquel elle appartenait
 * et permet de séparer des groupes de cellules si c possèdait des arrêtes communes entre des cellules
 * de ce groupe.
 *
 * Précondition: g!=NULL ⋀ c!=NULL ⋀ (c->key==BLANC||c->key==NOIR)
 */

static void _removeFromGroups(Graphe g, Cell c){
	assert(g!=NULL && c!=NULL && (c->key==BLANC||c->key==NOIR));
	
	Cell*** groups;
	Cell* temp=NULL;
	size_t size_temp=0;
	size_t* size_groups;
	size_t i,j;

	if(c->key==NOIR){
		groups=&g->groupsB;
		size_groups=&g->size_groupsB;
	}else{
		groups=&g->groupsW;
		size_groups=&g->size_groupsW;
	}

	for(i=0;i<(*size_groups)&&!_cellInGroup((*groups)[i],c);i++);
	for(j=0;(*groups)[i][j]!=NULL;j++){
		if((*groups)[i][j]!=c){
			temp=realloc(temp,(++size_temp)*sizeof(Cell));
			temp[size_temp-1]=(*groups)[i][j];
		}
	}
	free((*groups)[i]);
	for(j=i;j<(*size_groups)-1;j++)
		(*groups)[j]=(*groups)[j+1];
	*groups=realloc(*groups,(--(*size_groups))*sizeof(Cell*));

	for(j=0;j<size_temp;j++)
		_insertIntoGroups(g,temp[j]);
	free(temp);

}

Graphe graphe_remove(Graphe* g, int x, int y){
	assert(g!=NULL && *g!=NULL && x>=0 && x<(*g)->size && y>=0 && y<(*g)->size
			&& (graphe_getCellContent(*g,x,y)==NOIR||graphe_getCellContent(*g,x,y)==BLANC));
	Cell c=_getCell(*g,x,y);
	_removeFromGroups(*g,c);
	c->key=VIDE;
	return (*g);
}

char graphe_getCellContent(Graphe g, int x, int y){
	assert(g!=NULL && x>=0 && x<g->size && y>=0 && y<g->size);
	return _getCell(g,x,y)->key;
}


Cell** graphe_getGroups(Graphe g, Pion p){
	assert(g!=NULL && (p==BLANC||p==NOIR));
	return p==NOIR?g->groupsB:g->groupsW;
}

size_t graphe_countGroups(Graphe g, Pion p){
	assert(g!=NULL && (p==BLANC||p==NOIR));
	return p==NOIR?g->size_groupsB:g->size_groupsW;
}

/** 
 * Description: renvoie vrai si le pion passé en paramètre est la couleur gagnante.
 *
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 */

static bool _detectWinner(Graphe g, Pion p){
	assert(g!=NULL && (p==NOIR || p==BLANC));

	Cell** groups=graphe_getGroups(g,p);
	size_t size_group=p==NOIR?g->size_groupsB:g->size_groupsW;
	bool w1,w2,b1,b2; // permettent de savoir si les arrêtes d'une cellule sont en contact avec un bord du plateau
	w1=false;
	w2=false;
	b1=false;
	b2=false;

	if(size_group==0)
		return false;

	for(size_t i=0;i<size_group&&(!w1||!w2)&&(!b1||!b2);i++){
		w1=false;
		w2=false;
		b1=false;
		b2=false;
		for(size_t j=0;groups[i][j]!=NULL&&(!w1||!w2)&&(!b1||!b2);j++){
			if(p==BLANC){
				if(groups[i][j]->cells[0]->key=='W')
					w1=true;
				else if(groups[i][j]->cells[3]->key=='W')
					w2=true;
			}else{
				if(groups[i][j]->cells[2]->key=='B')
					b1=true;
				else if(groups[i][j]->cells[5]->key=='B')
					b2=true;
			}
		}
	}
	return (w1&&w2)||(b1&&b2);

}

char graphe_detectWinner(Graphe g){
	assert(g!=NULL);
	if(_detectWinner(g,NOIR))
		return NOIR;
	else if(_detectWinner(g,BLANC))
		return BLANC;
	return VIDE;
}

int graphe_getSize(Graphe g){
	return g->size;
}