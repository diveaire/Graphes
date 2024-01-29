#if !defined(__SERIALIZATION__)
#define __SERIALIZATION__

#include "graphe.h"

void exporterGrapheCSV(Graphe * graphe, char * nomFichier);
Graphe * importerGrapheCSV(char * nomFichier);

#endif
