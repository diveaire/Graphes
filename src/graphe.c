#include <stdio.h>
#include <stdlib.h>
#include "header/graphe.h"

/*
    * Implementation des graphes représentation par matrice d'adjacences
    * Sérialization : 
        (1èreLigne) paramètres
        (0,1,a);arc2;arc3
*/


Graphe *initGraphe(void){
    // Allocation de la mémoire pour le graphe
    Graphe *nouveauGraphe = malloc(sizeof(Graphe));
    if (nouveauGraphe == NULL) {
        printf("Erreur d'allocation mémoire pour le graphe\n");
        return NULL;
    }

    // Initialisation des propriétés du graphe
    nouveauGraphe->tailleGraphe = 0;
    nouveauGraphe->matrice = NULL;
    nouveauGraphe->nomSommet = NULL;

    return nouveauGraphe;
}

// Fonction permettant de Vider un graphe
int viderGraphe(Graphe * monGraphe){
    if (monGraphe == NULL) {
        printf("Impossible de Vider le Graphe (Le Graphe est NULL)\n");
        return EXIT_FAILURE;
    }
    // Libération de la mémoire pour la matrice d'adjacence
    if (monGraphe->matrice != NULL) {
        for (int i = 0; i < monGraphe->tailleGraphe; i++) {
            free(monGraphe->matrice[i]);
        }
        free(monGraphe->matrice);
        monGraphe->matrice = NULL; // Réinitialiser le pointeur après libération
    }
    // Libération de la mémoire pour le tableau des noms des sommets
    if (monGraphe->nomSommet != NULL) {
        free(monGraphe->nomSommet);
        monGraphe->nomSommet = NULL; // Réinitialiser le pointeur après libération
    }
    // Réinitialisation de la taille du graphe
    monGraphe->tailleGraphe = 0;

    return EXIT_SUCCESS;
}

// Fonction permettant de supprimer un graphe et de libérer sa mémoire correctement
void freeGraphe(Graphe *monGraphe){
    if (monGraphe == NULL) {
        return; // Retourner une erreur si le graphe est NULL
    }
    // Utiliser viderGraphe pour réinitialiser le graphe
    if (viderGraphe(monGraphe)) {
        return;
    }
    // Libération de la mémoire allouée pour la structure du graphe elle-même
    free(monGraphe);

    return; // Retourner le succès
}


// Fonction permettant d'ajouter un sommet dans un Graphe
int ajoutSommet(Graphe * monGraphe, int nom){

    // taille du graphe augmente de 1
    monGraphe->tailleGraphe++;

    /* ---------------------------------------- ALLOCATION MEMOIRE --------------------------------------------------*/
    /* --- Allocation Première dimension Matrice d'adjacence --- */
    Arc ** nouvelleMatrice = realloc(monGraphe->matrice, monGraphe->tailleGraphe * sizeof(Arc *));
    if (nouvelleMatrice == NULL){
        freeGraphe(monGraphe);
        printf("Erreur Allocation Memoire Matrice d'adjacence [%d] (ajoutSommet)\n", monGraphe->tailleGraphe);
        return EXIT_FAILURE;
    }
    monGraphe->matrice = nouvelleMatrice;
    
    /* --- Allocation deuxième dimension Matrice d'adjacence --- */
    for (int i=0 ;i<(monGraphe->tailleGraphe) ; i++){
        // Si on est sur l'ajout de la colonne de droite des anciens sommets
        if (i < monGraphe->tailleGraphe-1 ){
            // On realloue la mémoire de la nouvelle ligne pour ajouter 1 colonne à la fin
            Arc * nouvelleLigne = realloc(monGraphe->matrice[i], monGraphe->tailleGraphe * sizeof(Arc));
            if (nouvelleLigne == NULL){ 
                // Erreur d'allocation mémoire
                freeGraphe(monGraphe);
                printf("Erreur Allocation Memoire Matrice d'adjacence [%d][%d] (ajoutSommet)\n", monGraphe->tailleGraphe, i);
                return EXIT_FAILURE;
            }
            // Initialisation de la nouvelle colonne aux paramètres par défauts
            nouvelleLigne[monGraphe->tailleGraphe-1] = (Arc){.arc = false, .valuation = 0};
            // Réaffectation du pointeur dans le graphe
            monGraphe->matrice[i] = nouvelleLigne;
        }else{ // On est sur la nouvelle ligne 
            // Ajout nouvelle ligne de la matrice d'adjacence
            monGraphe->matrice[i] = calloc(monGraphe->tailleGraphe, sizeof(Arc));
            if (monGraphe->matrice[i] == NULL) {
                // Erreur d'allocation mémoire
                freeGraphe(monGraphe);
                printf("Erreur d'allocation mémoire (ajoutSommet)\n");
                return EXIT_FAILURE;
            }
        }
    }
    
    /* --- Allocation tableau des noms des sommets --- */
    int * nouveauNomSommet = realloc(monGraphe->nomSommet, monGraphe->tailleGraphe * sizeof(int));
    if (nouveauNomSommet == NULL) {
        // Erreur d'allocation mémoire
        freeGraphe(monGraphe);
        printf("Erreur d'allocation mémoire (ajoutSommet)\n");
        return EXIT_FAILURE;
    }

    /* --------------------------------------- FIN ALLOCATION MEMOIRE -----------------------------------------------*/
    monGraphe->nomSommet = nouveauNomSommet;

    // Initialisation du nom du sommet
    monGraphe->nomSommet[monGraphe->tailleGraphe-1] = nom;

    return EXIT_SUCCESS;
}


int ajouterArc(Graphe *monGraphe, int indiceA, int indiceB, int valuation){
    if (indiceA < 0 || indiceA >= monGraphe->tailleGraphe || indiceB < 0 || indiceB >= monGraphe->tailleGraphe) {
        printf("Indices de sommets invalides.\n");
        return EXIT_FAILURE;
    }
    monGraphe->matrice[indiceA][indiceB].arc = true;
    monGraphe->matrice[indiceA][indiceB].valuation = valuation;
    return EXIT_SUCCESS;
}

void supprimerArc(Graphe *monGraphe, int indiceA, int indiceB){
    if (indiceA < 0 || indiceA >= monGraphe->tailleGraphe || indiceB < 0 || indiceB >= monGraphe->tailleGraphe) {
        printf("Indices de sommets invalides.\n");
        return;
    }
    monGraphe->matrice[indiceA][indiceB].arc = false;
    monGraphe->matrice[indiceA][indiceB].valuation = 0;
}

// Fonction permettant de retourner l'indice i d'un sommet dans un graphe
int indiceSommet(Graphe *monGraphe, int sommet){
    if (monGraphe == NULL || monGraphe->nomSommet == NULL) {
        return -1; // Retourner -1 si le graphe ou le tableau des noms des sommets est NULL
    }

    for (int i = 0; i < monGraphe->tailleGraphe; i++) {
        if (monGraphe->nomSommet[i] == sommet) {
            return i; // Retourner l'indice si le sommet est trouvé
        }
    }

    return -1; // Retourner -1 si le sommet n'est pas trouvé dans le graphe
}