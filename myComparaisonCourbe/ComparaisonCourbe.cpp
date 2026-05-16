#include "ComparaisonCourbe.h"

double ComparaisonCourbe::score(std::vector<Vecteur>& courbe, std::function<double(Vecteur)> fonction){
    /*double cout = 0.0;
    float taille = 0.0;
    for (Vecteur& pt : courbe){
        cout += fonction(pt);
        taille+=1;
    }
    cout/=taille;
    return cout;*/
    return trouveDistMin(courbe);
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