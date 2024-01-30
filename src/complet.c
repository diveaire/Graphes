#include "header/graphe.h"

// Fonction pour vérifier si un graphe est complet
bool estGrapheComplet(Graphe *graphe, int *ordre) {
    int nbAretes = 0;
    int n = graphe->tailleGraphe;

    // Parcourir la matrice d'adjacence pour compter les arêtes
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  // Commence à j = i + 1 pour éviter de compter les arêtes en double
            if (graphe->matrice[i][j].arc) {
                nbAretes++;
            }
        }
    }

    // Calculer le nombre total d'arêtes pour un graphe complet de taille n
    int aretesGrapheComplet = n * (n - 1) / 2;

    // Vérifier si le nombre d'arêtes correspond à celui d'un graphe complet
    if (nbAretes == aretesGrapheComplet) {
        *ordre = n;  // Mettre à jour l'ordre du graphe complet
        return true;
    } else {
        *ordre = 0;  // Aucun graphe complet, mettre l'ordre à 0
        return false;
    }
}
