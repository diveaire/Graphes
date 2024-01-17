#if !defined(__GRAPHE__)
#define __GRAPHE__

#include <stdbool.h>

typedef struct Arc{
	int sommetA, sommetB;
	bool arc; 
	int valuation;
}Arc;

typedef struct graphe{
	Arc ** arc;
}graphe;


#endif

