// ParamsLancer.cpp
#include "ParamsLancer.h"

ParamsLancer::ParamsLancer(double phi, double theta, double vitesse)
    : phi(phi), theta(theta), vitesse(vitesse) {}

ParamsLancer ParamsLancer::operator-(const ParamsLancer& other) const {
    return ParamsLancer(phi - other.phi, theta - other.theta, vitesse - other.vitesse);
}

ParamsLancer& ParamsLancer::operator-=(const ParamsLancer& other){
    phi -= other.phi;
    theta -= other.theta;
    vitesse -= other.vitesse;
    return *this;
}

ParamsLancer ParamsLancer::operator+(const ParamsLancer& other) const {
    return ParamsLancer(phi + other.phi, theta + other.theta, vitesse + other.vitesse);
}

ParamsLancer& ParamsLancer::operator+=(const ParamsLancer& other){
    phi += other.phi;
    theta += other.theta;
    vitesse += other.vitesse;
    return *this;
}

ParamsLancer ParamsLancer::operator*(double scal) const {
    return ParamsLancer(scal * phi, scal * theta, scal * vitesse);
}
