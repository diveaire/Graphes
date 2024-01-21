#if !defined(__TABLEAUGRAPHE__)
#define __TABLEAUGRAPHE__

#include "graphe.h"

Graphe ** initTabGraphe();
int ajoutGraphe(Graphe *** tabGraphe, char * nom);
void freeTabGraphe(Graphe ** tabGraphe);

#endif
