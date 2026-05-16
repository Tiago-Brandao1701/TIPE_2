#include "CreeAstres.h"
#include <iostream>

std::vector<Astre> creeAstres(){
    /*initialisation de choses*/
    std::vector<Astre> astres;
    /*choses pour json*/
    std::ifstream file("myCreeAstres/astresData.json");
    if (!file) {
        std::cerr << "Error opening JSON file.\n";
        return astres;
    }
    nlohmann::json j;
    file >> j;
    /*remplit astres*/
    int nbreAstres = j["nbreAstres"];
    astres.reserve(nbreAstres);
    for (auto it = j.begin(); it != j.end(); ++it) {
        std::string key = it.key();

        if (key == "nbreAstres") {
            continue; 
        }

        const auto& info = it.value();

        Vecteur pos(info["x"], info["y"], info["z"]);
        Vecteur v(info["vx"], info["vy"], info["vz"]);
        std::string couleur = info["couleur"];
        std::string nom = info["nom"];
        int taille = info["taille"];
        double masse = info["masse"]; 

        astres.emplace_back(nom, couleur, taille, masse, pos, v);
    }
    return astres;
}