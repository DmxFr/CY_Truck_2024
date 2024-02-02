/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_trajet.h"
#include "model.h"*/



Comparaison compareTrajet(Ville a, Ville b) {
    if(a.trajets_total > b.trajets_total) return PLUS_GRAND;
    else if(a.trajets_total < b.trajets_total) return PLUS_PETIT;
    else return EGAL;
}

Comparaison compareNomVille(Ville a, Ville b) {
    int result = strcmp(a.nom_ville, b.nom_ville);
    if(result > 0) return PLUS_GRAND;
    else if(result < 0) return PLUS_PETIT;
    else return EGAL;
}

void printVille(Ville ville) {
    printf("%s%d--", ville.nom_ville, ville.trajets_total);
}




