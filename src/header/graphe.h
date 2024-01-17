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


#endif
