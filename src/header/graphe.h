#if !defined(__GRAPHE__)
#define __GRAPHE__

#include <stdbool.h>

typedef struct Arc{
	bool arc; 
	int valuation;
}Arc;

typedef struct Graphe{	
	char * nom;
	Arc ** matrice;
	int * nomSommet;
	int tailleGraphe;
}Graphe;

/* Graphes */
Graphe * initGraphe(char * nom);
Graphe * genererGrapheAleatoire(char * nom, int nombreSommets, int nombreAretes);
int viderGraphe(Graphe * monGraphe);
void freeGraphe(Graphe * monGraphe);
int ajoutSommet(Graphe * monGraphe, int nom);
int ajouterArc(Graphe * monGraphe, int sommetA, int sommetB, int valuation);
int supprimerArc(Graphe * monGraphe, int sommetA, int sommetB);
int indiceSommet(Graphe * monGraphe, int sommet);
Graphe * sousGrapheInduit(char * nom, Graphe *grapheOriginal, bool sommetsInclus[]);


#endif
