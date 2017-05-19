#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <jni.h>
#include "hex_Plateau.h"
#include "graphe.h"




JNIEXPORT jstring JNICALL
Java_hex_Plateau_creerGraphe (JNIEnv *env, jclass cl, jint ji) {


/* traitement en C */
Graphe g=graphe_create(ji);
char* res=graphe_toString(g);
graphe_destroy(&g);
/* conversion du résultat en chaîne Java */
jstring jres = (*env)->NewStringUTF(env, res);
/* libération mémoire */
free(res);
return jres;

}

JNIEXPORT jstring JNICALL 
Java_hex_Plateau_rentrerCoup (JNIEnv *env, jclass cl, jstring js,jchar jc, jint ji1, jint ji2){

	/* conversion de la chaîne Java en chaîne C */
	const char *s = (*env)->GetStringUTFChars(env, js, 0);
	/* traitement en C */
	Graphe g=graphe_toGraphe((char *)s);
	g=graphe_insert(&g,jc,ji1,ji2);
	char* res=graphe_toString(g);
	graphe_destroy(&g);
	/* conversion du résultat en chaîne Java */
	jstring jres = (*env)->NewStringUTF(env, res);
	/* libération mémoire */
	(*env)->ReleaseStringUTFChars(env, js, s);
	free(res);
	return jres;

}


JNIEXPORT jchar JNICALL 
Java_hex_Plateau_verifierGagnant (JNIEnv *env, jclass cl, jstring js){

	/* conversion de la chaîne Java en chaîne C */
	const char *s = (*env)->GetStringUTFChars(env, js, 0);
	/* traitement en C */
	Graphe g=graphe_toGraphe((char *)s);
	char c= graphe_detectWinner(g);
	graphe_destroy(&g);
	return c;
	



}


JNIEXPORT jstring JNICALL 
Java_hex_Plateau_annulerDernierCoup (JNIEnv *env, jclass cl, jstring js, jint ji1, jint ji2){

	/* conversion de la chaîne Java en chaîne C */
	const char *s = (*env)->GetStringUTFChars(env, js, 0);
	/* traitement en C */
	Graphe g=graphe_toGraphe((char *)s);
	g=graphe_remove(&g,ji1,ji2);
	char* res=graphe_toString(g);
	graphe_destroy(&g);
	/* conversion du résultat en chaîne Java */
	jstring jres = (*env)->NewStringUTF(env, res);
	/* libération mémoire */
	(*env)->ReleaseStringUTFChars(env, js, s);
	free(res);
	return jres;

	


}

JNIEXPORT jchar JNICALL 
Java_hex_Plateau_verifierCase (JNIEnv *env, jclass cl, jstring js, jint ji1, jint ji2){

	/* conversion de la chaîne Java en chaîne C */
	const char *s = (*env)->GetStringUTFChars(env, js, 0);
	Graphe g=graphe_toGraphe((char *)s);
	char c= graphe_getCellContent(g,ji1,ji2);
	graphe_destroy(&g);
	return c;

  }