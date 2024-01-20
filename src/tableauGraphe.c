#include <stdio.h>
#include <stdlib.h>
#include "header/tableauGraphe.h"

Graphe **initTabGraphe(){
    Graphe **tableauDeGraphes = malloc(sizeof(Graphe *));
    if (tableauDeGraphes == NULL) {
        printf("Échec de l'allocation de mémoire pour le tableau de graphes.\n");
        return NULL;
    }

    tableauDeGraphes[0] = NULL; // Initialiser le premier élément à NULL
    return tableauDeGraphes;
}

int ajoutGraphe(Graphe ***tabGraphe){
    int taille = 0;
    while ((*tabGraphe)[taille] != NULL) taille++;

    // Redimensionnement du tableau pour accueillir un nouveau graphe
    Graphe **nouveauTab = realloc(*tabGraphe, (taille + 2) * sizeof(Graphe *));
    if (nouveauTab == NULL) {
        printf("Échec du redimensionnement du tableau de graphes.\n");
        return -1; // Retourner -1 en cas d'échec
    }

    *tabGraphe = nouveauTab;
    (*tabGraphe)[taille] = initGraphe(); // Ajouter le nouveau graphe
    if ((*tabGraphe)[taille] == NULL) {
        printf("Échec de l'initialisation du nouveau graphe.\n");
        return -1;
    }

    (*tabGraphe)[taille + 1] = NULL; // Marquer la fin du tableau

    return taille; // Retourner l'indice du nouveau graphe
}

void freeTabGraphe(Graphe **tabGraphe){
    if (tabGraphe == NULL) {
        return; // Si le tableau est déjà NULL, il n'y a rien à libérer
    }

    // Libération de chaque graphe dans le tableau
    for (int i = 0; tabGraphe[i] != NULL; i++) {
        freeGraphe(tabGraphe[i]); // Utilise freeGraphe pour libérer chaque graphe individuellement
    }

    // Libération du tableau de graphes lui-même
    free(tabGraphe);
}