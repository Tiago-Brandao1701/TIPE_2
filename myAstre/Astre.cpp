// Astre.cpp
#include "Astre.h"

Astre::Astre(const std::string& nom,
             const std::string& couleur,
             int taille_aff,
             double mass,
             const Vecteur& pos,
             const Vecteur& vitesse)
             
    : nom(nom), couleur(couleur), taille_aff(taille_aff), mass(mass),
      pos(pos), vitesse(vitesse), vitesseInitiale(vitesse) {
        trajectoire.reserve(1);
        trajectoire[0] = pos;
      }

double Astre::distance(const Astre& other) const {
    return pos.distance(other.pos);
}
//Peut-être faire un "update", dans le cas du satellite, tu peux avoir envie de mettre l'ajout de son point ici, pour les performances...
void Astre::move() {
    vitesse = vitesse + dv;
    pos = pos + dr;
}