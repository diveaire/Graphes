
#include <stdio.h>
#include <stdlib.h>
#include "header/graphe.h"

/*
    * Implementation des graphes représentation par matrice d'adjacences
    * Sérialization : 
        (1èreLigne) paramètres
        (0,1,a);arc2;arc3
*/

void initGraphe(Graphe * monGraphe){
    monGraphe->tailleGraphe = 0;
    // Allocation Première dimension Matrice d'adjacence
    monGraphe->matrice = malloc(sizeof(Arc *));
    if (monGraphe->matrice == NULL){
        printf("Erreur Allocation Memoire Matrice d'adjacence [%d] (ajoutSommet)\n", monGraphe->tailleGraphe);
        return;
    }
    // Allocation deuxième dimension Matrice d'adjacence
    for (int i=0 ;i<(monGraphe->tailleGraphe) ; i++){
        monGraphe->matrice[i] = malloc(sizeof(Arc));
        if (monGraphe->matrice[i] == NULL){
            printf("Erreur Allocation Memoire Matrice d'adjacence [%d][%d] (ajoutSommet)\n", monGraphe->tailleGraphe, i);
            return;
        }   
    }

    // Allocation Première dimension 
    monGraphe->nomSommet = malloc(sizeof(int));
    if (monGraphe->nomSommet == NULL){
        printf("Erreur Allocation Memoire nomSommet[%d] (ajoutSommet)\n",monGraphe->tailleGraphe);
        return;
    }
}

void ajoutSommet(Graphe * monGraphe, int nom){

    // taille du graphe augmente de 1
    monGraphe->tailleGraphe++;

    /* ---------------------------------------- ALLOCATION MEMOIRE --------------------------------------------------*/
    // Allocation Première dimension Matrice d'adjacence
    Arc ** matriceTemp = realloc(monGraphe->matrice, monGraphe->tailleGraphe * sizeof(Arc *));
    if (matriceTemp == NULL){
        printf("Erreur Allocation Memoire Matrice d'adjacence [%d] (ajoutSommet)\n", monGraphe->tailleGraphe);
        return;
    }
    monGraphe->matrice = matriceTemp;
    
    // Allocation deuxième dimension Matrice d'adjacence
    for (int i=0 ;i<(monGraphe->tailleGraphe) ; i++){
        Arc * matriceTemp2 = realloc(monGraphe->matrice[i], monGraphe->tailleGraphe * sizeof(Arc));
        if (matriceTemp2 == NULL){
            printf("Erreur Allocation Memoire Matrice d'adjacence [%d][%d] (ajoutSommet)\n", monGraphe->tailleGraphe, i);
            return;
        }
        monGraphe->matrice[i] = matriceTemp2;
    }

    // Allocation Première dimension
    int * nomTemp = realloc(monGraphe->nomSommet, monGraphe->tailleGraphe * sizeof(int));
    if (nomTemp == NULL){
        printf("Erreur Allocation Memoire nomSommet[%d] (ajoutSommet)\n",monGraphe->tailleGraphe);
        return;
    }

    /* --------------------------------------- FIN ALLOCATION MEMOIRE -----------------------------------------------*/
    monGraphe->nomSommet = nomTemp;


    // Setup valeur du sommet
    monGraphe->nomSommet[monGraphe->tailleGraphe-1] = nom;

    
}

/*
Arc * initArc(int sommetA, int sommetB, int valuation){
    Arc * monArc = (Arc * ) malloc(sizeof(Arc));
    if (monArc == NULL){
        printf("Erreur d'allocation mémoire sur un Arc\n");
        return NULL;
    }
    monArc->sommetA = sommetA;
    monArc->sommetB = sommetB;
    monArc->valuation = valuation;
    return monArc;
}
*/

int main(void){
    Graphe monGraphe;
    initGraphe(&monGraphe);
    printf("INIT OK\n");

    int i = 0;
    for (int nom=100;nom>=90;nom--){
        ajoutSommet(&monGraphe,nom);
        printf("Nom sommet : %d -- Taille Graphe : %d\n",monGraphe.nomSommet[i], monGraphe.tailleGraphe);
        i++;
    }

    printf("FINIS");

    return 0;
}