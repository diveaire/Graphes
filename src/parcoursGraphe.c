#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "header/parcoursGraphe.h"

void BFS(Graphe * graphe, int sommetDepart){
    // Tableau pour marquer les sommets visités
    bool visite[graphe->tailleGraphe];
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        visite[i] = false;
    }

    // File pour le parcours en largeur
    int * file = malloc(graphe->tailleGraphe * sizeof(int));
    int debut = 0, fin = 0;

    // Ajout du sommet de départ à la file et marquage comme visité
    file[fin++] = sommetDepart;
    visite[sommetDepart] = true;

    while (debut != fin) {
        int courant = file[debut++];
        printf("%d ", courant);

        // Parcours des voisins du sommet courant
        for (int i = 0; i < graphe->tailleGraphe; i++) {
            if (graphe->matrice[courant][i].arc && !visite[i]) {
                file[fin++] = i;
                visite[i] = true;
            }
        }
    }
    free(file);
}

void DFSRecursif(Graphe * graphe, int sommet, bool visite[]){
    visite[sommet] = true;
    printf("%d ", sommet);

    // Parcours des voisins du sommet
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (graphe->matrice[sommet][i].arc && !visite[i]) {
            DFSRecursif(graphe, i, visite);
        }
    }
}

void DFS(Graphe * graphe, int sommetDepart){
    // Tableau pour marquer les sommets visités
    bool visite[graphe->tailleGraphe];
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        visite[i] = false;
    }

    DFSRecursif(graphe, sommetDepart, visite);
}
