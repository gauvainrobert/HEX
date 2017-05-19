/*****************************************************************************
* Module arbre minimax                                                       *
* Description: Module qui permet de passer en revue toutes le combinaisons   *
* possibles d'un graphe afin d'en sélectionner la meilleure d'après          *
* l'algorithme minimax.                                                      *
* G. ROBERT - Univ. de Toulouse III - Paul Sabatier                          *
******************************************************************************/

#ifndef ARBRE_MINIMAX_H_
#define ARBRE_MINIMAX_H_

#include <stdbool.h>
#include "graphe.h"

typedef struct _arbre_minimax * ArbreMinimax;

struct _coordinates{
	int x;
	int y;
};

typedef struct _coordinates Coordinates;

/* Constructeurs */

/**
 * Description: crée un arbre minimax de à partir d'un graphe g
 * et d'un pion (le joueur dont c'est le tour) et retourne l'arbre associé
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC) ⋀ graphe_detectWinner(g)==VIDE
 */
ArbreMinimax arbre_minimax_create(Graphe g, Pion p);



/* Projecteurs */

/**
 * Description: fonction qui retourne les coordonnées du meilleur coup possible à partir d'un arbre minimax
 *
 * Précondition: a ≠ NULL
 */
Coordinates arbre_minimax_getBestMove(ArbreMinimax a);




/* Destructeurs */

/**
 * Description: détruit un arbre minimax a passé en paramètre
 *
 * Précondition: a ≠ NULL ⋀ *a ≠ NULL
 */
void arbre_minimax_destroy(ArbreMinimax* a);


#endif