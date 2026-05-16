//Bornes.h
#ifndef BORNES_H
#define BORNES_H

#include "ParamsLancer.h"

/*
Classe Bornes qui permet de borner les essais de lancers
*/

class Bornes {
public:
    ParamsLancer min;
    ParamsLancer max;
    Bornes(const ParamsLancer& min = ParamsLancer(),
           const ParamsLancer& max = ParamsLancer());
};

#endif

