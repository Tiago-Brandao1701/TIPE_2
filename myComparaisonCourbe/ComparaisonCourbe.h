#ifndef COMPARAISON_COURBES_H
#define COMPARAISON_COURBES_H

#include <vector>
#include "Vecteur.h"
#include <functional>

/*
Calcule un score en fonction de la ressemblance entre la trajectoire du satellite et la trajectoire theorique
desiree qui est représentée à l'aide d'une fonction.
Pour l'instant elle ne fait que renvoyer la distance en valeur absolue entre chaque point de la courbe et le
point theorique associé.
*/

class ComparaisonCourbe{
public:
    static double score(std::vector<Vecteur>& courbe, std::function<double(Vecteur)> fonction);
    static double trouveDistMin(std::vector<Vecteur>& courbe);
    static double test(Vecteur params);
};

#endif
