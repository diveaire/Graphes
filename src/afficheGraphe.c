#include <stdio.h>
#include <stdlib.h>
#include "header/afficheGraphe.h"
#include "header/outils.h"
// Permet d'afficher un graphe
void afficherGraphe(Graphe * graphe){
    if (graphe == NULL) {
        printf("Le graphe est vide.\n");
        return;
    }
    titre(graphe->nom, '-');
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        printf("%6d -—> (", graphe->nomSommet[i]);
        bool premiereArete = true;
        for (int j = 0; j < graphe->tailleGraphe; j++) {
            if (graphe->matrice[i][j].arc) {
                if (!premiereArete) {
                    printf(", ");
                }
                printf("%6d", graphe->nomSommet[j]);
                premiereArete = false;
            }
        }
        printf(")\n");
    }
}
