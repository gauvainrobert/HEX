#include <assert.h>
#include "hex_IA.h"
#include "arbre_minimax.h"


JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupFacile
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

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupMoyen
  (JNIEnv *, jclass, jstring, jchar);

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupDifficile
  (JNIEnv *, jclass, jstring, jchar);

JNIEXPORT jintArray JNICALL Java_hex_IA_jouerCoupImpossible
  (JNIEnv *, jclass, jstring, jchar);
