#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "header/graphe.h"
#include "header/afficheGraphe.h"
#include "header/parcoursGraphe.h"
#include "header/serialization.h"
#include "header/circuit.h"
#include "header/connexe.h"
#include "header/complet.h"
#include "header/djikstra.h"

int main(void){
    srand(time(NULL));

    /* Graphe manuel */
    Graphe  * monGraphe = initGraphe(" monGraphe ");
    for (int i=0,nom=100;nom>=90;i++,nom--){
        ajoutSommet(monGraphe,nom);
        printf("Nom sommet : %d -- Taille Graphe : %d\n",monGraphe->nomSommet[i], monGraphe->tailleGraphe);
        if (nom < 100){
            ajouterArc(monGraphe,nom,nom+1,0);
        }
    }
    afficherGraphe(monGraphe);


    /* Génération de graphe */
    printf("genererGrapheAleatoire\n");
    Graphe * monGraphe2 = genererGrapheAleatoire(" monGraphe2 ",100,500);
    afficherGraphe(monGraphe2);
    printf("\n");


    /* Sérialization des graphes */
    printf("Importation CSV\n");
    Graphe * monGraphe3 = importerGrapheCSV("graphefichier");
    afficherGraphe(monGraphe3);
    printf("\n");
    
    printf("Exportation CSV\n");
    exporterGrapheCSV(monGraphe,"grapheExporter");
    printf("Exportation Réussie");
    printf("\n");


    /* Parcours */
    printf("Parcours en largeur :\n");
    BFS(monGraphe2, monGraphe2->nomSommet[0]);
    printf("\n");
    printf("Parcours en profondeur :\n");
    DFS(monGraphe2, monGraphe2->nomSommet[0]);
    printf("\n");


    /* circuit */
    printf("Circuit\n");
    Graphe * monGraphe4 = importerGrapheCSV("grapheCircuit");
    int chemin[6] = {0,1,2,3,4,0};
    afficherGraphe(monGraphe4);
    printf("%s %s un circuit\n", monGraphe4->nom, (estCircuit(monGraphe4,chemin,6))? "est" : "n'est pas");
    printf("\n");


    /* composantes fortement connexe */
    printf("\nComposantesFortementConnexes\n");
    ComposantesFortementConnexes(monGraphe3);

    /* Complet */
    printf("Complet\n");
    int ordreGraphe4, ordreGraphe5;
    printf("%s %s complet\n", monGraphe4->nom, (estGrapheComplet(monGraphe4,&ordreGraphe4))? "est" : "n'est pas");
    Graphe * monGraphe5 = importerGrapheCSV("grapheComplet");
    afficherGraphe(monGraphe5);
    if  (estGrapheComplet(monGraphe5,&ordreGraphe5)){
        printf("%s est un graphe complet d'ordre %d\n",monGraphe5->nom, ordreGraphe5);
    }else{
        printf("Le graphe n'est pas complet\n");
    }

    /* Chemin le plus cours */
    Graphe * monGraphe6 = importerGrapheCSV("grapheDjikstra");
    afficherGraphe(monGraphe6);
    Dijkstra(monGraphe6,0,6);



    // Libération de la mémoire allouée pour les graphes
    freeGraphe(monGraphe);
    freeGraphe(monGraphe2);
    freeGraphe(monGraphe3);
    freeGraphe(monGraphe4);
    freeGraphe(monGraphe5);
    freeGraphe(monGraphe6);

    return EXIT_SUCCESS;
}