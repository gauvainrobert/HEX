#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "arbre_minimax.h"

typedef struct _node * Node;

struct _node{
	Pion color;
	int key; // memorise le coefficient minimax du noeud
	Node* child;
	Node parent;
};

typedef struct _coordList * CoordList;

struct _coordList{
	Coordinates* values;
	size_t len;
};

struct _arbre_minimax{
	Node head;
	CoordList c; // memorise les coordonnées des cases vides
};

/*
 * Description: permet d'initialiser un noeud vide à partir d'une couleur de Pion p
 * et d'un coefficient minimax key.
 *
 * Précondition: (p=NOIR ⋁ p=BLANC)
 */

static Node _createNode(Pion p, int key){
	assert(p==BLANC||p==NOIR);
	Node n;

	n=malloc(sizeof(struct _node));
	if(n==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return NULL;
	}
	n->color=p;
	n->key=key;
	n->parent=NULL;
	n->child=NULL;
	return n;
}

/**
 * Description: fonction qui permet de rendre la mémoire allouée par un noeud et ses enfants
 *
 * Précondition: n ≠ NULL
 */
static void _destroyNode(Node* n){
	assert(n!=NULL);
	if(*n!=NULL){
		if((*n)->child!=NULL){
			_destroyNode((*n)->child);
			free((*n)->child);
		}
		free(*n);
	}
}

/**
 * Description: retourne la valeur de pion opposé à p, retourne NOIR si p est BLANC est vice versa
 *
 * Précondition: (p=NOIR ⋁ p=BLANC)
 */

static char _oppositePion(Pion p){
	assert(p==NOIR||p==BLANC);
	return p==NOIR?BLANC:NOIR;
}
/**
 * Description: fonction qui permet de rendre l'espace alloué pour des coordonnées c
 * 
 * Précondition: c ≠ NULL ⋀ *c ≠ NULL
 */
static void _destroyCoord(CoordList* c){
	assert(c!=NULL && *c!=NULL);
	free((*c)->values);
	free((*c));
}

/**
 * Description: fonction qui échange les pointeurs de deux coordonnées a et b
 * 
 * Précondition: a ≠ NULL ⋀ *a ≠ NULL ⋀ b ≠ NULL ⋀ *b ≠ NULL
 */
static void _swapCoord(Coordinates* a, Coordinates* b){
	Coordinates* temp=a;
	a=b;
	b=temp;
}


/**
 * Description: fonction auxiliaire de arbre_minimax_create qui permet de créer un Noeud (on l'uilise pour créer la tête de l'arbre)
 * et ses enfants récursivement à partir d'un graphe, d'un pion d'origine o (l'abre minimax est créé pour cette couleur),
 * un pion p qui doit être insérer dans g et des coordonnées c pour mémoriser les cases vides du graphes.
 *
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC) ⋀ (o=NOIR ⋁ o=BLANC) ⋀ c ≠ NULL
 */

static Node _createHead(Graphe g, Pion o, Pion p, CoordList* c){
	assert(g!=NULL&&(p==NOIR||p==BLANC)&&(o==NOIR||o==BLANC)&&c!=NULL&&*c!=NULL);
	char result;
	Node n,child;
	size_t i,j,k;
	size_t children_len=0;
	CoordList temp;
	Coordinates coords;
	int cond;

	if((result=graphe_detectWinner(g)!=VIDE))
		return _createNode(p,result==o?1:-1);

	n=_createNode(p,p==o?-1:1);
	for (i = 0; i < (*c)->len && !children_len;){
		graphe_insert(&g,p,(*c)->values[i].x,(*c)->values[i].y);
		temp=malloc(sizeof(struct _coordList));
		if(temp==NULL){
			fprintf(stderr, "Allocation mémoire impossible\n");
			return NULL;
		}
		temp->values=malloc(((*c)->len-1)*sizeof(struct _coordinates));
		if(temp->values==NULL){
			fprintf(stderr, "Allocation mémoire impossible\n");
			return NULL;
		}
		temp->len=(*c)->len-1;
		k=0;
		for(j=0;j<(*c)->len;j++){
			if(j!=i){
				temp->values[k]=(*c)->values[j];
				k++;
			}
		}
		child=_createHead(g,o,_oppositePion(p),&temp);
		_destroyCoord(&temp);
		if((cond=((p==o && child->key>=n->key)
			||(p!=o && child->key<=n->key)))){
			coords=(*c)->values[i];
			n->key=child->key;
			n->child=realloc(n->child,(++children_len)*sizeof(Node));

			if(n->child==NULL){
				fprintf(stderr, "Allocation mémoire impossible\n");
				return NULL;
			}
			child->parent=n;
			n->child[children_len-1]=child;
		}else{
			_destroyNode(&child);
		}

		graphe_remove(&g,(*c)->values[i].x,(*c)->values[i].y);
		if(cond){
			i++;
			(*c)->values=realloc((*c)->values,sizeof(struct _coordinates));
			(*c)->values[0]=coords;
			(*c)->len=1;
		}else{
			_swapCoord(&(*c)->values[i],&(*c)->values[(*c)->len-1]);
			(*c)->values=realloc((*c)->values,(--(*c)->len)*sizeof(struct _coordinates));
		}
	}

	return n;

}


ArbreMinimax arbre_minimax_create(Graphe g, Pion p){
	assert(g!=NULL && (p==NOIR||p==BLANC) && graphe_detectWinner(g)==VIDE);
	ArbreMinimax a;
	int n=graphe_getSize(g);
	CoordList c=NULL;
	size_t temp;
	size_t size_coord=0; // memorise la taille de x et y

	a=malloc(sizeof(struct _arbre_minimax));
	if(a==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return NULL;
	}
	c=malloc(sizeof(struct _coordList));
	if(c==NULL){
		fprintf(stderr, "Allocation mémoire impossible\n");
		return NULL;
	}
	c->values=NULL;

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(graphe_getCellContent(g,i,j)==VIDE){
				c->values=realloc(c->values,(++size_coord)*sizeof(struct _coordinates));
				temp=size_coord-1;
				c->values[temp].x=i;
				c->values[temp].y=j;
			}
		}
	}
	a->c=c;
	a->c->len=size_coord;
	a->head=_createHead(g,p,p,&a->c);
	return a;
}

void arbre_minimax_destroy(ArbreMinimax* a){
	_destroyNode(&(*a)->head);
	_destroyCoord(&(*a)->c);
	free(*a);
}


Coordinates arbre_minimax_getBestMove(ArbreMinimax a){
	assert(a!=NULL);
	Coordinates c;
	Node* nodes=a->head->child;
	size_t i_max=0;
	c.x=-1;
	c.y=-1;
	/* Dans la réalité les coordonnées c(-1,-1) ne sont jamais retournées par la fonction
	 * à cause de la précondition de arbre_minimax_create -> un arbre minimax est créé à partir 
	 * d'un graphe dont la partie n'est pas terminée -> la racine de a possède des fils.
	 */
	if(nodes==NULL)
		return c;

	for(size_t i=0;i<a->c->len;i++)
		if(nodes[i]->key>nodes[i_max]->key)
			i_max=i;

	return a->c->values[i_max];
}