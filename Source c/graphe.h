/******************************************************************
* Module Graphe                                                   *
* Description: Module qui permet de représenter un plateau de jeu *
* de taille variable                                              *
* G. ROBERT - Univ. de Toulouse III - Paul Sabatier               *
*******************************************************************/

#ifndef GRAPHE_H_
#define GRAPHE_H_

#include <stdbool.h>

#define BLANC 'b'
#define NOIR  'n'
#define VIDE '.'

typedef char pion;
typedef struct _cell * cell;
typedef struct _graphe * graphe;

/* Constructeurs */

/**
 * Description: crée un graphe de à partir d'une taille n 
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
bool graphe_isEmptyCell(graphe g, int x, int y);

/**
 * Description:
 * La fonction retourne BLANC si le joueur blanc a gagné.
 * La fonction retourne NOIR si le joueur noir a gagné.
 * La fonction retourne VIDE sinon
 *
 * Précondition: g ≠ NULL
 */
char graphe_detectWinner(graphe g);

/**
 * Description: retourne le contenu d'une cellule de cordonnées (x,y)
 * dans un graphe g
 * 
 * Précondition: g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 */
char graphe_getCellContent(graphe g, int x, int y);

/**
 * Description: retourne les groupes de cellules dont le contenu est p
 *
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 */

cell** graphe_getGroups(graphe g, pion p);


/* Destructeurs */

/**
 * Description: détruit un graphe g passé en paramètre
 *
 * Précondition: g ≠ NULL ⋀ *g ≠ NULL
 */
int graphe_destroy(graphe* g);


#endif