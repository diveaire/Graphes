
#include "header/circuit.h"


bool estCircuit(Graphe *monGraphe, int *chemin, int taille) {
    // Un circuit valide doit commencer et finir par le même sommet
    if (chemin[0] != chemin[taille - 1]) return false;

    // Vérifier que le chemin ne traverse pas un sommet plus d'une fois (sauf le premier/dernier)
    for (int i = 1; i < taille - 1; i++) {
        for (int j = i + 1; j < taille - 1; j++) {
            if (chemin[i] == chemin[j]) {
                return false;
            }
        }
    }

    // Vérifier que chaque transition entre sommets existe dans le graphe
    for (int i = 0; i < taille - 1; i++) {
        if (!monGraphe->matrice[chemin[i]][chemin[i + 1]].arc) {
            return false; // Si une arête entre chemin[i] et chemin[i+1] n'existe pas
        }
    }

    return true;
}

