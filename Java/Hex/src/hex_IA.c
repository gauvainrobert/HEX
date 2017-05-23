/*********************************************************************
* Interface IA                                                       *
* Description: Module utilisé pour gérer l'intelligence artificielle *
* G. ROBERT - Univ. de Toulouse III - Paul Sabatier                  *
**********************************************************************/

#include <assert.h>
#include "hex_IA.h"
#include "arbre_minimax.h"
#include "graphe_reduit.h"

typedef struct _coordList * CoordList;

struct _coordList{
  Coordinates* values;
  size_t len;
};

/** 
 * Description: Retourne un entier compris entre 0 et x non inclus
 *
 * Précondition: x>0
 */
static int _random(int x){
  assert(x>0);
  return rand()%x;
}


JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupFacile
  (JNIEnv *env, jclass cl, jstring js, jchar p){
  assert(js!=NULL && (p==NOIR||p==BLANC));
  Coordinates c;
  const char *s = (*env)->GetStringUTFChars(env, js, 0);

  Graphe g=graphe_toGraphe((char*)s);
  ArbreMinimax a=arbre_minimax_create(g,p);
  int n=graphe_getSize(g);
  do{
    c.x=_random(n);
    c.y=_random(n);
  }while(!graphe_isEmptyCell(g,c.x,c.y));


  jintArray result = (*env)->NewIntArray(env,2);
  if(result==NULL)
  	return NULL;
  
  jint coord[2];
  coord[0]=c.x;
  coord[1]=c.y;
  (*env)->SetIntArrayRegion(env, result, 0, 2, coord);
  (*env)->ReleaseStringUTFChars(env, js, s);
  return result;
}

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupMoyen
  (JNIEnv *env, jclass cl, jstring js, jchar p){
  assert(js!=NULL && (p==NOIR||p==BLANC));

  const char *s = (*env)->GetStringUTFChars(env, js, 0);

  Graphe g=graphe_toGraphe((char*)s);
  ArbreMinimax a=arbre_minimax_create(g,p);
  Coordinates c=arbre_minimax_getBestMove(a);

  jintArray result = (*env)->NewIntArray(env,2);
  if(result==NULL)
    return NULL;
  
  jint coord[2];
  coord[0]=c.x;
  coord[1]=c.y;
  (*env)->SetIntArrayRegion(env, result, 0, 2, coord);
  (*env)->ReleaseStringUTFChars(env, js, s);
  return result;
}

/**
 * Description: retourne la valeur de pion opposé à p, retourne NOIR si p est BLANC est vice versa
 *
 * Précondition: (p=NOIR ⋁ p=BLANC)
 */

static Pion _oppositePion(Pion p){
  assert(p==NOIR||p==BLANC);
  return p==NOIR?BLANC:NOIR;
}

/**
 * Description: retourne l'index de l'élément le plus petit du tableau v de taille n
 *
 *
 * Précondition: v ≠ NULL ⋀ n > 0
 *
 */
static int _minIndexArrayOfInt(int* v, int n){
  assert(v!=NULL && n>0);
  int min=0;
  for(int i=0; i<n; i++)
    if(v[i]<v[min])
      min=i;
  return min;
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

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupDifficile
  (JNIEnv *env, jclass cl, jstring js, jchar p){
  assert(js!=NULL && (p==NOIR||p==BLANC));

  const char *s = (*env)->GetStringUTFChars(env, js, 0);

  Graphe g=graphe_toGraphe((char*)s);
  Pion adversaire=_oppositePion(p);
  ArbreMinimax a=arbre_minimax_create(g,adversaire);
  Coordinates c=arbre_minimax_getBestMove(a);
  GrapheReduit gr=graphe_reduit_create(g);
  int count=graphe_reduit_countPonts(gr,adversaire);
  CoordList coord_liste=NULL;
  size_t temp;
  size_t size_coord=0; // memorise la taille de x et y
  int* results=NULL;
  int cond;
  int n=graphe_getSize(g);
  int min_results;

  graphe_reduit_destroy(&gr);
  arbre_minimax_destroy(&a);

  coord_liste=malloc(sizeof(struct _coordList));
  if(coord_liste==NULL){
    fprintf(stderr, "Allocation mémoire impossible\n");
    return NULL;
  }
  coord_liste->values=NULL;

  graphe_insert(&g,adversaire,c.x,c.y);
  if((cond=graphe_detectWinner(g)!=adversaire) && count >= 1){
    graphe_remove(&g,c.x,c.y);
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(graphe_getCellContent(g,i,j)==VIDE){
          coord_liste->values=realloc(coord_liste->values,(++size_coord)*sizeof(struct _coordinates));
          temp=size_coord-1;
          coord_liste->values[temp].x=i;
          coord_liste->values[temp].y=j;
        }
      }
    }
    coord_liste->len=size_coord;

    results=malloc(size_coord*(sizeof(int)));
    if(results==NULL){
      fprintf(stderr, "Allocation mémoire impossible\n");
      return NULL;
    }
    int count_min=0;
    size_t min=0;
    for(size_t i=0;i<size_coord;i++){
      graphe_insert(&g,p,c.x,c.y);
      gr=graphe_reduit_create(g);
      results[i]=graphe_reduit_countPonts(gr,adversaire);
      graphe_reduit_destroy(&gr);
      graphe_remove(&g,c.x,c.y);
    }
    min_results=_minIndexArrayOfInt(results,size_coord);
    c=coord_liste->values[min_results];
    free(results);
    _destroyCoord(&coord_liste);

  }else if(cond && !count){
    int n=graphe_getSize(g);
    do{
      c.x=_random(n);
      c.y=_random(n);
    }while(!graphe_isEmptyCell(g,c.x,c.y));
  }

  graphe_destroy(&g);

  jintArray result = (*env)->NewIntArray(env,2);
  if(result==NULL)
    return NULL;
  
  jint coord[2];
  coord[0]=c.x;
  coord[1]=c.y;
  (*env)->SetIntArrayRegion(env, result, 0, 2, coord);
  (*env)->ReleaseStringUTFChars(env, js, s);
  return result;
}

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupImpossible
  (JNIEnv *env, jclass cl, jstring js, jchar p){
  assert(js!=NULL && (p==NOIR||p==BLANC));
  const char *s = (*env)->GetStringUTFChars(env, js, 0);

  Graphe g=graphe_toGraphe((char*)s);
  Pion adversaire=_oppositePion(p);
  ArbreMinimax a=arbre_minimax_create(g,adversaire);
  Coordinates c=arbre_minimax_getBestMove(a);
  GrapheReduit gr=graphe_reduit_create(g);
  int count=graphe_reduit_countPonts(gr,adversaire);
  CoordList coord_liste=NULL;
  size_t temp;
  size_t size_coord=0; // memorise la taille de x et y
  int* results=NULL;
  int cond;
  int n=graphe_getSize(g);
  int min_results;

  graphe_reduit_destroy(&gr);
  arbre_minimax_destroy(&a);

  coord_liste=malloc(sizeof(struct _coordList));
  if(coord_liste==NULL){
    fprintf(stderr, "Allocation mémoire impossible\n");
    return NULL;
  }
  coord_liste->values=NULL;

  graphe_insert(&g,adversaire,c.x,c.y);
  if((cond=graphe_detectWinner(g)!=adversaire) && count >= 1){
    graphe_remove(&g,c.x,c.y);
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(graphe_getCellContent(g,i,j)==VIDE){
          coord_liste->values=realloc(coord_liste->values,(++size_coord)*sizeof(struct _coordinates));
          temp=size_coord-1;
          coord_liste->values[temp].x=i;
          coord_liste->values[temp].y=j;
        }
      }
    }
    coord_liste->len=size_coord;

    results=malloc(size_coord*(sizeof(int)));
    if(results==NULL){
      fprintf(stderr, "Allocation mémoire impossible\n");
      return NULL;
    }
    int count_min=0;
    size_t min=0;
    for(size_t i=0;i<size_coord;i++){
      graphe_insert(&g,p,c.x,c.y);
      gr=graphe_reduit_create(g);
      results[i]=graphe_reduit_countPonts(gr,adversaire);
      graphe_reduit_destroy(&gr);
      graphe_remove(&g,c.x,c.y);
    }
    min_results=_minIndexArrayOfInt(results,size_coord);
    c=coord_liste->values[min_results];
    free(results);
    _destroyCoord(&coord_liste);

  }else if(cond && !count){
    a=arbre_minimax_create(g,p);
    c=arbre_minimax_getBestMove(a);
    arbre_minimax_destroy(&a);
  }

  graphe_destroy(&g);

  jintArray result = (*env)->NewIntArray(env,2);
  if(result==NULL)
    return NULL;
  
  jint coord[2];
  coord[0]=c.x;
  coord[1]=c.y;
  (*env)->SetIntArrayRegion(env, result, 0, 2, coord);
  (*env)->ReleaseStringUTFChars(env, js, s);
  return result;
  
}
