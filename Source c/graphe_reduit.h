/******************************************************************
* Module Graphe    Reduit                                         *
* Description: Module utilisé pour les calculs de jeu             *
* G. ROBERT - Univ. de Toulouse III - Paul Sabatier               *
*******************************************************************/

#ifndef GRAPHE_REDUIT_H_
#define GRAPHE_REDUIT_H_

#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

typedef struct _graphe_reduit * GrapheReduit;


/* Constructeurs */

/**
 * Description : fonction qui permet de construire un graphe réduit à partir d'un graphe déjà existant
 * /\ Attention! Le graphe n'est plus utilisable
 * Précondition: g ≠ NULL
 */

GrapheReduit graphe_reduit_create (Graphe g);

/* Projecteurs */

/**
 * Description : fonction qui permet de compter les ponts dans un graphe réduit pour un pion donné
 * 
 * Précondition: g ≠ NULL ⋀ (p=NOIR ⋁ p=BLANC)
 */

int graphe_reduit_countPonts(GrapheReduit g, Pion p);



/* Destructeurs */

/**
 * Description: fonction qui permet de rendre l'espace alloué pour un graphe réduit dont l'adresse
 * est passé en paramètre.
 *
 * Précondition: g ≠ NULL ⋀ *g ≠ NULL
 */
void graphe_reduit_destroy(GrapheReduit* g);






#endif