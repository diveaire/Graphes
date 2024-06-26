#include <stdio.h>

#include "header/serialization.h"

/*
    * Implementation des graphes représentation par matrice d'adjacences
    * Sérialization : 
        (1èreLigne) paramètres
        (0,1,a);arc2;arc3
*/


void exporterGrapheCSV(Graphe * graphe, char * nomFichier){
    char chemin[128];
    sprintf(chemin,"files/%s",nomFichier);
    FILE * fichier = fopen(chemin, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    for (int i = 0; i < graphe->tailleGraphe; i++) {
        for (int j = 0; j < graphe->tailleGraphe; j++) {
            if (graphe->matrice[i][j].arc) {
                fprintf(fichier, "%d;%d;%d\n", graphe->nomSommet[i], graphe->nomSommet[j], graphe->matrice[i][j].valuation);
            }
        }
    }

    fclose(fichier);
}
/*
// Permet d'importer un graphe en format CSV sous la forme SommetA;SommetB;Valuation
Graphe * importerGrapheCSV(char * nomFichier) {
    char chemin[128];
    sprintf(chemin,"files/%s",nomFichier);
    FILE * fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    Graphe * graphe = initGraphe(nomFichier);
    int sommetA, sommetB, valuation;

    while (fscanf(fichier, "%d;%d;%d", &sommetA, &sommetB, &valuation) >= 2) {
        // Vérifiez et ajoutez les sommets s'ils n'existent pas
        if (indiceSommet(graphe, sommetA) == -1) {
            ajoutSommet(graphe, sommetA);
        }
        if (indiceSommet(graphe, sommetB) == -1) {
            ajoutSommet(graphe, sommetB);
        }

        // Ajoute une arête avec une valuation par défaut si elle n'est pas spécifiée
        if (feof(fichier)) {
            valuation = 0;  // ou une valeur par défaut de votre choix
        }
        ajouterArc(graphe, sommetA, sommetB, valuation);
        //printf("VALEUR AJOUTER ARC : SomA:%d SomB:%d Val:%d\n", sommetA, sommetB, valuation);
    }

    fclose(fichier);
    return graphe;
}
*/
Graphe *importerGrapheCSV(char *nomFichier) {
    char chemin[128];
    sprintf(chemin, "files/%s", nomFichier);
    FILE *fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    Graphe *graphe = initGraphe(nomFichier);
    char ligne[128];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int sommetA, sommetB, valuation;
        int resultat = sscanf(ligne, "%d;%d;%d", &sommetA, &sommetB, &valuation); // sscanf retourne le nombre d'élément assigné
        if (resultat >= 1) { // Au moins un sommet est présent
            if (indiceSommet(graphe, sommetA) == -1) {
                ajoutSommet(graphe, sommetA);
            }

            if (resultat >= 2) { // Deux sommets sont présents, éventuellement une valuation
                if (indiceSommet(graphe, sommetB) == -1) {
                    ajoutSommet(graphe, sommetB);
                }
                if (resultat == 2) { // Pas de valuation spécifiée
                    valuation = 0; // Utilisez une valuation par défaut
                }
                ajouterArc(graphe, sommetA, sommetB, valuation);
            }
        }
    }

    fclose(fichier);
    return graphe;
}