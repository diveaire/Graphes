#include <stdio.h>
#include <stdlib.h>

#include "header/graphe.h"


int main(void){
    Graphe  * monGraphe = initGraphe();
    printf("INIT OK\n");

    int i = 0;
    for (int nom=100;nom>=90;nom--){
        ajoutSommet(monGraphe,nom);
        printf("Nom sommet : %d -- Taille Graphe : %d\n",monGraphe->nomSommet[i], monGraphe->tailleGraphe);
        i++;
    }

    printf("FINIS\n");


    // Libération de la mémoire allouée pour le graphe
    freeGraphe(monGraphe);

    return EXIT_SUCCESS;
}