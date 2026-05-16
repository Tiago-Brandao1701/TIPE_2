// ParamsLancer.h
#ifndef PARAMS_LANCER_H
#define PARAMS_LANCER_H

/*
Cette classe contient 3 champs qui correspondent aux cordonnees spheriques du vecteur vitesse
au moment de le lancer
*/

class ParamsLancer {
public:
    double phi;
    double theta;
    double vitesse;

    ParamsLancer operator-(const ParamsLancer& other) const;
    ParamsLancer& operator-=(const ParamsLancer& other);

    ParamsLancer operator+(const ParamsLancer& other) const;
    ParamsLancer& operator+=(const ParamsLancer& other);

    ParamsLancer operator*(double scal) const;

    ParamsLancer(double phi = 0, double theta = 0, double vitesse = 0);
};

#endif // PARAMS_LANCER_H