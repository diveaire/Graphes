#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // Pour INT_MAX

#include "header/djikstra.h"

#define INFINI INT_MAX

// Trouver le sommet avec la distance minimale, parmi les sommets non inclus dans Solution
int minDistance(int distance[], bool solution[], int taille) {
    int min = INFINI, min_index;

    for (int sommetSuivant = 0; sommetSuivant < taille; sommetSuivant++) {
        if (!solution[sommetSuivant] && distance[sommetSuivant] <= min) {
            min = distance[sommetSuivant], min_index = sommetSuivant;
        }
    }

    return min_index;
}

// Fonction pour afficher le chemin du sommet source au sommet destination
void afficherChemin(int parent[], int j) {
    if (parent[j] == -1) return;  // Si j est la source

    afficherChemin(parent, parent[j]);
    printf("%d ", j);
}

// Fonction pour trouver le chemin de poids minimal avec l'algorithme de Dijkstra
void Dijkstra(Graphe *monGraphe, int sommetA, int sommetB) {
    int distance[monGraphe->tailleGraphe];  // contiendra la distance la plus courte de sommetA à i
    bool solution[monGraphe->tailleGraphe];  // solution[i] est vrai si le sommet i est inclus dans le plus court chemin
    int parent[monGraphe->tailleGraphe];  // parent[i] contiendra le prédécesseur de i dans le chemin

    // Initialisation
    for (int i = 0; i < monGraphe->tailleGraphe; i++) {
        parent[i] = -1;
        distance[i] = INFINI;
        solution[i] = false;
    }
    distance[sommetA] = 0;

    // Trouver le plus court chemin pour tous les sommets
    for (int count = 0; count < monGraphe->tailleGraphe - 1; count++) {
        int sommetActuel = minDistance(distance, solution, monGraphe->tailleGraphe);
        solution[sommetActuel] = true;

        for (int sommetSuivant = 0; sommetSuivant < monGraphe->tailleGraphe; sommetSuivant++) {
            if (
                !solution[sommetSuivant] && 
                monGraphe->matrice[sommetActuel][sommetSuivant].arc &&
                distance[sommetActuel] != INFINI && 
                distance[sommetActuel] + monGraphe->matrice[sommetActuel][sommetSuivant].valuation < distance[sommetSuivant]
            ) {
                parent[sommetSuivant] = sommetActuel;
                distance[sommetSuivant] = distance[sommetActuel] + monGraphe->matrice[sommetActuel][sommetSuivant].valuation;
            }
        }
    }

    // Afficher le plus court chemin de sommetA à sommetB
    if (distance[sommetB] == INFINI) {
        printf("%d, %d ne sont pas reliés\n", sommetA, sommetB);
    } else {
        printf("Chemin le plus court entre %d et %d: [%d ", sommetA, sommetB, sommetA);
        afficherChemin(parent, sommetB);
        printf("]\n");
    }
}
