#include <cmath>
#include <math.h>
#include "Vecteur.h"

/*definition de +,-,* et de distance*/

Vecteur::Vecteur(double x, double y, double z) : x(x), y(y), z(z) {}

Vecteur Vecteur::operator+(const Vecteur& other) const {
    return Vecteur(x + other.x, y + other.y, z + other.z);
}

Vecteur& Vecteur::operator+=(const Vecteur& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vecteur Vecteur::operator-(const Vecteur& other) const {
    return Vecteur(x - other.x, y - other.y, z - other.z);
}

Vecteur& Vecteur::operator-=(const Vecteur& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vecteur Vecteur::operator*(double scal) const {
    return Vecteur(scal * x, scal * y, scal * z);
}

Vecteur Vecteur::prod_vect(const Vecteur& other) const {
    return Vecteur(
        y*other.z - z*other.y,
        z*other.x - x*other.z,
        x*other.y - y*other.x
    ); 
}

double Vecteur::distance(const Vecteur& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double Vecteur::norme() const {
    return distance(Vecteur(0,0,0));
}
