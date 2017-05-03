/****************************************************
* Module Graphe
* Description:
*
* G. ROBERT - Univ. de Toulouse III - Paul Sabatier 
*****************************************************/

#ifndef GRAPHE_H_
#define GRAPHE_H_

#include <stdbool.h>

#define BLANC 'b'
#define NOIR  'n'
#define VIDE  '.' 

typedef char pion;
typedef struct _cell * cell;
typedef struct _graphe * graphe;

/* Constructeurs */

/**
 * Description: crée un graphe à partir d'une taille n 
 * et retourne le graphe initialisé avec des cases vides.
 * Précondition: n>1
 */
graphe graphe_create(int n);

/**
 * Description: Insère un pion p dans un graphe g aux cordonnées (x,y)
 * et retourne le nouveau graphe.
 *
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 *   g ≠ NULL ⋀ *g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC) ⋀ x∈[0,n[ ⋀ y∈[0,n[ ⋀ graphe_isEmptyHex(*g,x,y)
 */
graphe graphe_insert(graphe* g, pion p, int x, int y);

/**
 * Descrition: Supprime le pion dans le graphe g placé aux cordonnées (x,y)
 * et retourne le nouveau graphe.
 *	
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 *   g ≠ NULL ⋀ *g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 *
 */
graphe graphe_remove(graphe* g, int x, int y);


/* Projecteurs */

/**
 * Description: retourne vrai si la cellule du graphe g de cordonnées (x,y)
 * est vide,
 * renvoie faux sinon.
 * 
 * Précondition: g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 */
bool graphe_isEmptyHex(graphe g, int x, int y);


/* Destructeurs */

/**
 * Description: détruit un graphe g passé en paramètre
 *
 * Précondition: g ≠ NULL ⋀ *g ≠ NULL
 */
int graphe_destroy(graphe* g);


#endif