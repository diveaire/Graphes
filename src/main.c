#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "header/graphe.h"
#include "header/afficheGraphe.h"
#include "header/parcoursGraphe.h"

int main(void){
    srand(time(NULL));

    Graphe  * monGraphe = initGraphe(" monGraphe ");
    printf("INIT OK\n");

    for (int nom=100;nom>=90;nom--){
        ajoutSommet(monGraphe,nom);
        //printf("Nom sommet : %d -- Taille Graphe : %d\n",monGraphe->nomSommet[i], monGraphe->tailleGraphe);
        int nb=rand() % 3; // Une chance sur 3 de d'ajouter l'arc
        for (int i=0;i<monGraphe->tailleGraphe-1 && !nb ;i++){
            ajouterArc(monGraphe,nom,nom+i,rand());
            nb=rand() % 3; // Une chance sur 3 de d'ajouter l'arc
        }
    }
    Graphe * monGraphe2 = genererGrapheAleatoire(" monGraphe2 ",100,500);
    afficherGraphe(monGraphe);
    afficherGraphe(monGraphe2);

    /* Parcours */
    BFS(monGraphe, monGraphe->nomSommet[0]);
    DFS(monGraphe, monGraphe->nomSommet[0]);


    // Libération de la mémoire allouée pour le graphe
    freeGraphe(monGraphe);
    freeGraphe(monGraphe2);

    return EXIT_SUCCESS;
}