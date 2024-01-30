#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "header/parcoursGraphe.h"

void BFS(Graphe *graphe, int sommetDepart) {
    if (graphe == NULL || graphe->tailleGraphe == 0) {
        printf("Le graphe est vide ou non initialisé.\n");
        return;
    }

    // Le tableau visite
    bool *visite = calloc(graphe->tailleGraphe, sizeof(bool));
    if (visite == NULL) {
        perror("Erreur d'allocation mémoire pour visite");
        return;
    }

    int *file = malloc(graphe->tailleGraphe * sizeof(int));
    if (file == NULL) {
        perror("Erreur d'allocation mémoire pour la file");
        free(visite);
        return;
    }

    int debut = 0, fin = 0;
    file[fin++] = indiceSommet(graphe, sommetDepart);  // Commencez le parcours à partir de la racine (sommet 0)
    visite[0] = true;   
    printf("%d ", sommetDepart);  // Affiche le sommet de départ avant de commencer la boucle

    while (debut != fin) {
        int courant = file[debut++];

        for (int i = 0; i < graphe->tailleGraphe; i++) {
            if (graphe->matrice[courant][i].arc && !visite[i]) {
                file[fin++] = i;
                visite[i] = true;
                printf("%d ", graphe->nomSommet[i]);  // Affiche le sommet lorsqu'il est visité
            }
        }
    }

    free(file);   // Libération de la mémoire allouée pour file
    free(visite); // Libération de la mémoire allouée pour visite
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

void DFS(Graphe *graphe, int sommetDepart) {
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
    DFSRecursif(graphe, graphe->nomSommet[sommetDepart], visite); // La racine est le sommet 0
}

