#if !defined(__GRAPHE__)
#define __GRAPHE__

#include <stdbool.h>

typedef struct Arc{
	bool arc; 
	int valuation;
}Arc;

typedef struct Graphe{	
	Arc ** matrice;
	int * nomSommet;
	int tailleGraphe;
}Graphe;

/* Graphes */
Graphe * initGraphe(void);
int viderGraphe(Graphe * monGraphe);
void freeGraphe(Graphe * monGraphe);
int ajoutSommet(Graphe * monGraphe, int nom);
int ajouterArc(Graphe * monGraphe, int indiceA, int indiceB, int valuation);
void supprimerArc(Graphe * monGraphe, int indiceA, int indiceB);
int indiceSommet(Graphe * monGraphe, int sommet);


#endif
