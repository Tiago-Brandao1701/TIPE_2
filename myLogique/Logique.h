#ifndef LOGIQUE_H
#define LOGIQUE_H

#include <cmath>
#include <iomanip>
#include <iostream>

#include "Vecteur.h"
#include "Astre.h"
#include "cstes.h"


/*
Class Logique:
cette classe a comme objectif le calcul de l'acceleration d'objets celestes par deux methode differentes
qui prennent en argument une liste d'objest celestes et modifient le champ acceleration d'un objet de cette liste :
    -Methode euler explicite
    -Methode rk
Deux fonctions auxiliaires interac_grav et pfd qui aident a determiner l'accleration d'un objet a un moment donné
Attribut initTrajAstres qui a simplement coomme objectif si c'est la premiere simulation (et donc l'initialisation de
la trajectoire des astres) ou pas
*/

class Logique {
    public:
        static Vecteur interac_grav (const Vecteur& pos1, const Vecteur& pos2, const double mass1, const double mass2);
        static Vecteur pfd (std::vector<Astre>& astres, Astre& astre1, const Vecteur& pos_astre, int t, bool initTrajAstres);
        static void euler (std::vector<Astre>& astres, Astre& astre, int t, bool initTrajAstres);
        static void rk (std::vector<Astre>& astres, Astre& astre, int t, bool initTrajAstres);
};

#endif

