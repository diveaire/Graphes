#if !defined(__PARCOURSGRAPHE__)
#define __PARCOURSGRAPHE__

#include "graphe.h"

void BFS(Graphe *graphe, int sommetDepart);
void DFSUtil(Graphe *graphe, int sommet, bool visite[]);
void DFS(Graphe *graphe, int sommetDepart);


#endif
