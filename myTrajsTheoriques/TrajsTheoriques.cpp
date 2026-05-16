#include "TrajsTheoriques.h"
#include <cmath>

double geostatMars(Vecteur point){
    double norme = point.distance(Vecteur(0,0,0));
    return std::abs(norme - rayonGeoStatMars);
}
