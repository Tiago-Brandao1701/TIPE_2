#include "Logique.h"


Vecteur Logique::interac_grav (const Vecteur& pos1, const Vecteur& pos2, const double mass1, const double mass2){
    const double facteur = G*mass1*mass2/(std::pow(pos1.distance(pos2),3));
    return (pos2-pos1)*facteur;
}

Vecteur Logique::pfd (std::vector<Astre>& astres, Astre& astre1, const Vecteur& pos_astre, int t, bool initTrajAstres){
    Vecteur acc (0.0,0.0,0.0);
    const double mass =  astre1.mass;
    for (Astre& astre2 : astres){
        if (!initTrajAstres || &astre2 != &astre1){
            acc += interac_grav(pos_astre, astre2.trajectoire[t], mass, astre2.mass)*(1/mass);
        }
    }
    return acc;
}

void Logique::euler (std::vector<Astre>& astres, Astre& astre, int t, bool initTrajAstres){
    astre.dv = pfd(astres, astre, astre.pos, t, initTrajAstres)*dt;
    astre.dr = (astre.vitesse + astre.dv)*dt;
}

void Logique::rk (std::vector<Astre>& astres, Astre& astre, int t, bool initTrajAstres){
    astre.dr = Vecteur(0,0,0);
    astre.dv = Vecteur(0,0,0);
    Vecteur v = astre.vitesse;
    Vecteur r = astre.pos;
        
    std::vector<Vecteur> k(4);
    std::vector<Vecteur> l(4);
    double coefs[] = {1.0,0.5,0.5,1.0};
    
    //calcul des pentes
    k[0] = v*dt;
    l[0] = pfd(astres, astre, r, t, initTrajAstres)*dt;
    
    for (int i=1 ; i<4 ; i++){
        k[i] = (v + (l[i-1]*coefs[i]))*dt;
        l[i]= pfd(astres,astre,r + (k[i-1]*coefs[i]), t, initTrajAstres)*dt;
    }
    
    for (int i=0 ; i<4 ; i++){
        double coef = (1.0/coefs[i])*(1.0/6.0); 
        astre.dv += l[i]*coef;
        astre.dr += k[i]*coef;
     }
}

