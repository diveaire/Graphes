#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "header/parcoursGraphe.h"

void BFS(Graphe *graphe) {
    // Vérifier si le graphe est non nul
    if (graphe == NULL || graphe->tailleGraphe == 0) {
        printf("Le graphe est vide ou non initialisé.\n");
        return;
    }

    // Tableau pour marquer les sommets visités
    bool visite[graphe->tailleGraphe];
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        visite[i] = false;
    }

    // File pour le parcours en largeur, initialisée pour commencer à la racine (sommet 0)
    int *file = malloc(graphe->tailleGraphe * sizeof(int));
    if (file == NULL) {
        perror("Erreur d'allocation mémoire pour la file");
        return;
    }
    int debut = 0, fin = 0;

    // Commencez le parcours à partir de la racine (sommet 0)
    file[fin++] = 0; // La racine est le sommet 0
    visite[0] = true;

    while (debut != fin) {
        int courant = file[debut++];

        // Parcours des voisins du sommet courant
        for (int i = 0; i < graphe->tailleGraphe; i++) {
            if (graphe->matrice[courant][i].arc && !visite[i]) {
                file[fin++] = i;
                visite[i] = true;
                printf("%d ", i); // Affiche le sommet lorsqu'il est visité
            }
        }
    }

    free(file);
}


void DFSRecursif(Graphe *graphe, int sommet, bool visite[]) {
    visite[sommet] = true;
    printf("%d ", graphe->nomSommet[sommet]);

    // Parcours des voisins du sommet
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (graphe->matrice[sommet][i].arc && !visite[i]) {
            DFSRecursif(graphe, i, visite);
        }
    }
}

void DFS(Graphe *graphe) {
    // Vérifier si le graphe est non nul
    if (graphe == NULL || graphe->tailleGraphe == 0) {
        printf("Le graphe est vide ou non initialisé.\n");
        return;
    }

    // Tableau pour marquer les sommets visités
    bool visite[graphe->tailleGraphe];
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        visite[i] = false;
    }

    // Commencez le parcours à partir de la racine (sommet 0)
    DFSRecursif(graphe, 0, visite); // La racine est le sommet 0
}

