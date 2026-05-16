// Astre.h
#ifndef ASTRE_H
#define ASTRE_H

#include <string>
#include <vector>
#include "Vecteur.h"

/*
classe Astre munie:
    -d'une méthode distance qui renvoi la distance entre l'astre et un autre
    -d'une méthode move qui actualise la position et la vitesse de l'astre en fonction de dr et dv
*/

class Astre {
public:
    std::string nom;
    std::string couleur;
    int taille_aff;
    double mass;
    Vecteur pos;
    Vecteur dr;
    Vecteur vitesse;
    Vecteur vitesseInitiale;
    Vecteur dv;
    std::vector<Vecteur> trajectoire;
    
    Astre(const std::string& nom = "",
          const std::string& couleur = "",
          int taille_aff = 0,
          double mass = 0,
          const Vecteur& pos = Vecteur(),
          const Vecteur& vitesse = Vecteur());

    double distance(const Astre& other) const;
    void move();
};

#endif // ASTRE_H
