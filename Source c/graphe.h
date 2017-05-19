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

typedef char Pion;
typedef struct _cell * Cell;
typedef struct _graphe * Graphe;

/* Constructeurs */

/**
 * Description: crée un graphe de à partir d'une taille n 
 * et retourne le graphe initialisé avec des cases vides.
 * Précondition: n>1
 */
Graphe graphe_create(int n);

/**
 * Description: Insère un pion p dans un graphe g aux cordonnées (x,y)
 * et retourne le nouveau graphe.
 *
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 *   g ≠ NULL ⋀ *g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC) ⋀ x∈[0,n[ ⋀ y∈[0,n[ ⋀ graphe_isEmptyHex(*g,x,y)
 * ⋀ graphe_getCellContent(*g,x,y)=VIDE
 */
Graphe graphe_insert(Graphe* g, Pion p, int x, int y);

/**
 * Descrition: Supprime le pion dans le graphe g placé aux cordonnées (x,y)
 * et retourne le nouveau graphe.
 *	
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 *   g ≠ NULL ⋀ *g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[ 
 * ⋀ (graphe_getCellContent(*g,x,y)=NOIR ⋁ graphe_getCellContent(*g,x,y)=BLANC)
 *
 */
Graphe graphe_remove(Graphe* g, int x, int y);


/* Projecteurs */

/**
 * Description: retourne vrai si la cellule du graphe g de cordonnées (x,y)
 * est vide,
 * renvoie faux sinon.
 * 
 * Précondition: 
 * Soit n, la taille de la grille g, on a:
 * g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 */
bool graphe_isEmptyCell(Graphe g, int x, int y);

/**
 * Description:
 * La fonction retourne BLANC si le joueur blanc a gagné.
 * La fonction retourne NOIR si le joueur noir a gagné.
 * La fonction retourne VIDE sinon
 *
 * Précondition: g ≠ NULL
 */
char graphe_detectWinner(Graphe g);

/**
 * Description: retourne le contenu d'une cellule de cordonnées (x,y)
 * dans un graphe g
 * 
 * Précondition: g ≠ NULL ⋀ x∈[0,n[ ⋀ y∈[0,n[
 */
char graphe_getCellContent(Graphe g, int x, int y);

/**
 * Description: retourne les groupes de cellules dont le contenu est p
 *
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 */

Cell** graphe_getGroups(Graphe g, Pion p);

/**
 * Description: retourne le nombre des groupes de cellules dont le contenu est p
 *
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 */

size_t graphe_countGroups(Graphe g, Pion p);

/**
 * Description: retourne la taille d'un graphe passé en paramètre
 *
 * Précondition: g ≠ NULL
 */
int graphe_getSize(Graphe g);


/**
 * Description: imprime le graphe sur la sortie standard au format ascii
 *
 * Précondition: g ≠ NULL
 */
void graphe_print(Graphe g);

/**
 * Description: retourne une chaine de caractères representant les valeurs des cases du graphe au format ascii
 *
 * Précondition: g ≠ NULL
 */
char* graphe_toString(Graphe g);

/**
 * Description: transforme une chaine de caractères representant le graphe au format ascii en type Graphe
 *
 * Précondition: c ≠ NULL ⋀ *c ≠ NULL
 */
Graphe graphe_toGraphe(char* c);

/* Destructeurs */

/**
 * Description: détruit un graphe g passé en paramètre
 *
 * Précondition: g ≠ NULL ⋀ *g ≠ NULL
 */
void graphe_destroy(Graphe* g);


#endif