
#include "header/circuit.h"


bool estCircuit(Graphe * monGraphe, int * chemin, int taille){
    if (taille>monGraphe->tailleGraphe) return false;
    if (chemin[0] != chemin[taille-1]) return false;
    for (int i=0 ; i<taille ; i++){
        for (int j=0;j<taille;j++){
            if (chemin[i] == chemin[j]){
                return false;
            }
        }
    }
    return true;
}