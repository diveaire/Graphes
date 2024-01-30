#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "header/graphe.h"

/* ------------------------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------- Initialisation ----------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------- */

Graphe * initGraphe(char * nom){
    // Allocation de la mémoire pour le graphe
    Graphe * nouveauGraphe = malloc(sizeof(Graphe));
    if (nouveauGraphe == NULL) {
        printf("Erreur d'allocation mémoire pour le graphe\n");
        return NULL;
    }

    // Initialisation des propriétés du graphe
    nouveauGraphe->tailleGraphe = 0;
    nouveauGraphe->nom = strdup(nom);
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

    /*  ALLOCATION MEMOIRE */
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

    /*  FIN ALLOCATION MEMOIRE  */
    monGraphe->nomSommet = nouveauNomSommet;

    // Initialisation du nom du sommet
    monGraphe->nomSommet[monGraphe->tailleGraphe-1] = nom;

    return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------- ARC ---------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------- */

// Permet d'ajouter un arc dans le Graphe
int ajouterArc(Graphe *monGraphe, int sommetA, int sommetB, int valuation){
    int indiceA = indiceSommet(monGraphe,sommetA);
    int indiceB = indiceSommet(monGraphe,sommetB);

    if (indiceA == -1 || indiceB == -1 || indiceB >= monGraphe->tailleGraphe) {
        printf("Indices de sommets invalides.\n");
        printf("%d vers %d", sommetA, sommetB);
        return EXIT_FAILURE;
    }

    monGraphe->matrice[indiceA][indiceB].arc = true;
    monGraphe->matrice[indiceA][indiceB].valuation = valuation;
    return EXIT_SUCCESS;
}

// Permet de supprimer un arc dans le Graphe
int supprimerArc(Graphe *monGraphe, int sommetA, int sommetB){
    int indiceA = indiceSommet(monGraphe,sommetA);
    int indiceB = indiceSommet(monGraphe,sommetB);

    if (indiceA == -1 || indiceB == -1 || indiceB >= monGraphe->tailleGraphe) {
        printf("Indices de sommets invalides.\n");
        return -1;
    }
    monGraphe->matrice[indiceA][indiceB].arc = false;
    monGraphe->matrice[indiceA][indiceB].valuation = 0;
    return EXIT_SUCCESS;
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

/* ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------- Génération ------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------- */

Graphe * genererGrapheAleatoire(char * nom, int nombreSommets, int nombreAretes){
    Graphe * graphe = initGraphe(nom);
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Ajout des sommets
    for (int i = 0; i < nombreSommets; i++) {
        ajoutSommet(graphe, i+1);
    }

    // Ajout des arêtes
    for (int i = 0; i < nombreAretes; i++) {
        int sommetA = (rand() % (nombreSommets-1))+1;
        int sommetB = (rand() % (nombreSommets-1))+1;
        int valuation = rand() % 100; // Générer une valuation aléatoire, entre 0 et 99

        // Vérifier si une arête existe déjà entre sommetA et sommetB, si non, l'ajouter
        //printf("Ajout d'un arc entre %d(%d) et %d(%d)\n", sommetA,indiceSommet(graphe,sommetA), sommetB,indiceSommet(graphe,sommetB));
        if (!graphe->matrice[sommetA][sommetB].arc) {
            ajouterArc(graphe, sommetA, sommetB, valuation);
        } else {
            i--; // Décrémenter i pour compenser l'itération en cas d'arête déjà existante
        }
    }
    return graphe;
}

/* ------------------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------- Degré --------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------- */

int degreSortant(Graphe *graphe, int sommet) {
    int degre = 0;
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (graphe->matrice[sommet][i].arc) {
            degre++;
        }
    }
    return degre;
}

int degreEntrant(Graphe *graphe, int sommet) {
    int degre = 0;
    for (int i = 0; i < graphe->tailleGraphe; i++) {
        if (graphe->matrice[i][sommet].arc) {
            degre++;
        }
    }
    return degre;
}

/* ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------ Sous Graphe ------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------- */

Graphe * sousGrapheInduit(char * nom, Graphe * grapheOriginal, int * inclure, int tailleInclure) {
    Graphe * sousGraphe = initGraphe(nom); // Initialisez un nouveau graphe
    // Tableau pour garder la trace des indices des sommets inclus dans le sous-graphe
    bool estInclus[grapheOriginal->tailleGraphe];
    memset(estInclus, 0, sizeof(estInclus));
    // Ajouter les sommets spécifiés au sous-graphe et marquer comme inclus
    for (int i = 0; i < tailleInclure; i++) {
        int sommet = inclure[i];
        for (int j = 0; j < grapheOriginal->tailleGraphe; j++) {
            if (grapheOriginal->nomSommet[j] == sommet) {
                ajoutSommet(sousGraphe, sommet);
                estInclus[j] = true; // Marquer ce sommet comme inclus
                break; // Passer au prochain sommet à inclure une fois trouvé
            }
        }
    }
    // Ajouter les arêtes au sous-graphe
    for (int i = 0; i < grapheOriginal->tailleGraphe; i++) {
        for (int j = 0; j < grapheOriginal->tailleGraphe; j++) {
            if (estInclus[i] && estInclus[j] && grapheOriginal->matrice[i][j].arc) {
                ajouterArc(sousGraphe, grapheOriginal->nomSommet[i], grapheOriginal->nomSommet[j], grapheOriginal->matrice[i][j].valuation);
            }
        }
    }
    return sousGraphe;
}


Graphe *sousGraphePartiel(Graphe *grapheOriginal, bool **aretesARetirer) {
    Graphe *sousGraphe = initGraphe("Sous-Graphe Partiel"); // Initialise un nouveau graphe

    // Copier les sommets du graphe original dans le sous-graphe
    for (int i = 0; i < grapheOriginal->tailleGraphe; i++) {
        ajoutSommet(sousGraphe, grapheOriginal->nomSommet[i]);
    }

    // Copier les arêtes du graphe original dans le sous-graphe, sauf celles à retirer
    for (int i = 0; i < grapheOriginal->tailleGraphe; i++) {
        for (int j = 0; j < grapheOriginal->tailleGraphe; j++) {
            if (grapheOriginal->matrice[i][j].arc && (!aretesARetirer || !aretesARetirer[i][j])) {
                // Utiliser les noms des sommets pour ajouter les arêtes, si les indices changent
                ajouterArc(sousGraphe, grapheOriginal->nomSommet[i], grapheOriginal->nomSommet[j], grapheOriginal->matrice[i][j].valuation);
            }
        }
    }

    return sousGraphe;
}
