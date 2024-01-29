#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "header/graphe.h"
#include "header/afficheGraphe.h"
#include "header/parcoursGraphe.h"
#include "header/serialization.h"
#include "header/connexe.h"

int main(void){
    srand(time(NULL));

    Graphe  * monGraphe = initGraphe(" monGraphe ");

    for (int i=0,nom=100;nom>=90;i++,nom--){
        ajoutSommet(monGraphe,nom);
        printf("Nom sommet : %d -- Taille Graphe : %d\n",monGraphe->nomSommet[i], monGraphe->tailleGraphe);
        if (nom < 100){
            ajouterArc(monGraphe,nom,nom+1,0);
        }
    }
    afficherGraphe(monGraphe);


    printf("genererGrapheAleatoire\n");
    Graphe * monGraphe2 = genererGrapheAleatoire(" monGraphe2 ",100,500);
    afficherGraphe(monGraphe2);


    printf("Importation CSV\n");
    Graphe * monGraphe3 = importerGrapheCSV("graphefichier");
    afficherGraphe(monGraphe3);


    /* Parcours */
    printf("PARCOURS\n");
    BFS(monGraphe3);
    printf("\n");
    DFS(monGraphe3);

    /* composantes fortement connexe */
    printf("\nComposantesFortementConnexes\n");
    ComposantesFortementConnexes(monGraphe3);


    // Libération de la mémoire allouée pour le graphe
    freeGraphe(monGraphe);
    freeGraphe(monGraphe2);

    return EXIT_SUCCESS;
}