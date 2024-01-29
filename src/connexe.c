#include <stdio.h>
#include <string.h>
#include "header/connexe.h"

// Parcours DFSconnexe pour stocker dans une pile l'ordre de fin
void DFSconnexe(Graphe *graphe, int sommet, bool visite[], int ordreFin[], int *indice) {
    visite[sommet] = true;

    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (graphe->matrice[sommet][i].arc && !visite[i]) {
            DFSconnexe(graphe, i, visite, ordreFin, indice);
        }
    }

    ordreFin[(*indice)++] = sommet;  // Stocke le sommet dans l'ordre de fin
}


void DFSconnexeComposante(Graphe *grapheTransposé, int sommet, bool visite[]) {
    visite[sommet] = true;
    printf("%d ", sommet);  // Affiche le sommet pour identifier la composante

    for (int i = 0; i < grapheTransposé->tailleGraphe; i++) {
        if (grapheTransposé->matrice[sommet][i].arc && !visite[i]) {
            DFSconnexeComposante(grapheTransposé, i, visite);
        }
    }
}

void ComposantesFortementConnexes(Graphe *graphe) {
    bool visite[graphe->tailleGraphe];
    memset(visite, false, sizeof(visite));
    int ordreFin[graphe->tailleGraphe];
    int indice = 0;

    // Premier DFSconnexe pour déterminer l'ordre de fin
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (!visite[i]) {
            DFSconnexe(graphe, i, visite, ordreFin, &indice);
        }
    }

    // Obtenir le graphe transposé
    Graphe *transposé = transposerGraphe(graphe, "transposéeGraphe");

    // Réinitialiser le tableau de visite pour le deuxième DFSconnexe
    memset(visite, false, sizeof(visite));

    // Deuxième DFSconnexe sur le graphe transposé en suivant l'ordre de fin
    for (int i = graphe->tailleGraphe - 1; i >= 0; i--) {
        int sommet = ordreFin[i];
        if (!visite[sommet]) {
            DFSconnexeComposante(transposé, sommet, visite);
            printf("\n");  // Nouvelle ligne pour séparer les composantes fortement connexes
        }
    }

    // Libérer la mémoire du graphe transposé
    freeGraphe(transposé);
}


Graphe * transposerGraphe(Graphe *graphe, char * nom) {
    Graphe *transpose = initGraphe(nom);
    for(int i=0 ; i < graphe->tailleGraphe; i++) {
        ajoutSommet(transpose,i);
    }
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        for (int j = 0; j < graphe->tailleGraphe; j++) {
            if (graphe->matrice[i][j].arc) {
                ajouterArc(transpose, j, i, graphe->matrice[i][j].valuation);  // Inverser la direction de l'arête
            }
        }
    }
    return transpose;
}
