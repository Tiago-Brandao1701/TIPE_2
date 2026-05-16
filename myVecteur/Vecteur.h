//Vecteur.h
#ifndef VECTEUR_H
#define VECTEUR_H

#include <cmath>

/*
classe vecteur en dimension 3,
muni de l'addition et soustraction entre vecteurs,
muni de la multiplication par un scalaire (attention, elle se fait a droite, vecteur*scalaire) 
*/

class Vecteur {
public:
    double x, y, z;

    Vecteur(double x = 0.0, double y = 0.0, double z = 0.0);

    Vecteur operator+(const Vecteur& other) const;
    Vecteur& operator+=(const Vecteur& other);

    Vecteur operator-(const Vecteur& other) const;
    Vecteur& operator-=(const Vecteur& other);

    Vecteur operator*(double scal) const;

    Vecteur prod_vect(const Vecteur& other) const;
    
    double distance(const Vecteur& other) const;
    double norme() const;
};

#endif // VECTEUR_H

