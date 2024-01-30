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
    Graphe  * monGraphe = initGraphe("monGraphe");
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
    Graphe * monGraphe2 = genererGrapheAleatoire("monGraphe2",100,500);
    afficherGraphe(monGraphe2);
    printf("\n");


    /* Parcours */
    printf("Parcours en largeur :\n");
    BFS(monGraphe2, monGraphe2->nomSommet[0]);
    printf("\n");
    printf("Parcours en profondeur :\n");
    DFS(monGraphe2, monGraphe2->nomSommet[0]);
    printf("\n\n\n");

    /* Degrés */
    printf("Degré entrant de %d dans %s = %d\n", monGraphe->nomSommet[0], monGraphe->nom, degreEntrant(monGraphe,0));
    printf("Degré sortant de %d dans %s = %d\n", monGraphe->nomSommet[0], monGraphe->nom, degreSortant(monGraphe,0));

    /* Sous graphe induit */
    printf("\nSousGrapheInduit\n");
    int inclure[] = {100, 99, 97};  // Noms des sommets à inclure dans le sous-graphe
    int tailleInclure = sizeof(inclure) / sizeof(inclure[0]);
    Graphe * sousGraphe = sousGrapheInduit("Sous-Graphe", monGraphe, inclure, tailleInclure);
    afficherGraphe(sousGraphe);
    printf("\n");
    free(sousGraphe);

    /* Sous graphe partiel */
    printf("SousGraphePartiel\n");
    // Initialisation du tableau des arêtes à retirer
    bool **aretesARetirer = malloc(monGraphe->tailleGraphe * sizeof(bool *));
    for (int i = 0; i < monGraphe->tailleGraphe; i++) {
        aretesARetirer[i] = calloc(monGraphe->tailleGraphe, sizeof(bool));
    }

    // Supposons que vous voulez retirer l'arête de 99 à 98 et de 97 à 96
    aretesARetirer[indiceSommet(monGraphe,99)][indiceSommet(monGraphe,100)] = true;  // Correspond à l'arête de 99 à 100
    aretesARetirer[indiceSommet(monGraphe,98)][indiceSommet(monGraphe,99)] = true;   // Correspond à l'arête de 98 à 99

    Graphe * sousGraphe2= sousGraphePartiel(monGraphe, aretesARetirer);
    afficherGraphe(sousGraphe2);  // Utilisez votre fonction d'affichage de graphe
    printf("\n");

    // Libérer la mémoire allouée pour aretesARetirer
    for (int i = 0; i < monGraphe->tailleGraphe; i++) {
        free(aretesARetirer[i]);
    }
    free(aretesARetirer);
    free(sousGraphe2);


    /* Sérialization des graphes */
    printf("Importation CSV\n");
    Graphe * monGraphe3 = importerGrapheCSV("graphefichier");
    afficherGraphe(monGraphe3);
    printf("\n");
    

    Graphe * monGrapheSansArc = importerGrapheCSV("grapheTest");
    afficherGraphe(monGrapheSansArc);
    printf("\n");
    

    printf("Exportation CSV\n");
    exporterGrapheCSV(monGraphe,"grapheExporter");
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