#ifndef CREE_ASTRES_H
#define CREE_ASTRES_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "Astre.h"
#include "Vecteur.h"
#include "json.hpp"

/*
Ce module sert à la création des astres
Les infos viennent d'un fichier json crée à partir du script python "creeAstresData"
*/

std::vector<Astre> creeAstres();

#endif