#include "ComparaisonCourbe.h"

double ComparaisonCourbe::score(std::vector<Vecteur>& courbe, int nbPts, std::function<double(Vecteur)> fonction){
    double cout_distance_norm = trouveDistMin(courbe) / dist_max;
    double vitesse_init = (courbe[1]-courbe[0]).norme()/dt ;
    double vitesse_fina = (courbe[nbPts-1] - courbe[nbPts-2]).norme()/dt;
    double cout_vitesse_norm = vitesse_fina/vitesse_init;
    double cout_temps_norm = (nbPts*dt)/(365*24*3600);
    double cout_equateur_norm = abs(courbe[1].z/courbe[0].z);
    return (500*cout_distance_norm + 10*cout_vitesse_norm + 10*cout_temps_norm + 3*cout_equateur_norm);
}

double ComparaisonCourbe::trouveDistMin(std::vector<Vecteur>& courbe){
    double min = courbe[0].norme();
    double temp;
    for (Vecteur& pt : courbe){
        temp = pt.norme();
        if (temp < min){
            min = temp;
        }
    }
    return min;
}

double ComparaisonCourbe::test(Vecteur params){
    return params.distance(Vecteur(10,10,2500));
}