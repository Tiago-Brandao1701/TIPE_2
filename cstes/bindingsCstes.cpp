#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // nécessaire pour std::string
#include "cstes.h"

namespace py = pybind11;

PYBIND11_MODULE(cstes, m) {
    // Constantes utiles
    m.attr("pi") = pi;
    m.attr("infini") = doubleInfini;

    // Constantes physiques
    m.attr("dt") = dt;
    m.attr("G") = G;

    /*cstes pour les methodes*/
    //Montecarlo
    m.attr("nbEssaisMonteCarlo") = nbEssaisMonteCarlo;
    //Descente du gradient
    m.attr("nbIterDescenteGradient") = nbIterDescenteGradient;
    m.attr("dphi") = dphi;
    m.attr("dtheta") = dtheta;
    m.attr("dvitesse") = dvitesse;
    m.attr("pasApprentissageGradient") = pasApprentissageGradient;
    //AdamW
    m.attr("beta1") = beta1;
    m.attr("beta2") = beta2;
    m.attr("epsilon") = epsilon;
    m.attr("weightDecay") = weightDecay;
    //PSO
    m.attr("nbParticules") = nbParticules;
    m.attr("nbIterPSO") = nbIterPSO;

    // Date
    m.attr("annee") = annee;
    m.attr("mois") = mois;
    m.attr("jour") = jour;

    /*Infos astres*/
    //Soleil
    m.attr("masseSoleil") = masseSoleil;
    m.attr("tailleSoleil") = tailleSoleil;
    m.attr("couleurSoleil") = couleurSoleil;
    //Mercure
    m.attr("masseMercure") = masseMercure;
    m.attr("tailleMercure") = tailleMercure;
    m.attr("couleurMercure") = couleurMercure;
    // Vénus
    m.attr("masseVenus") = masseVenus;
    m.attr("tailleVenus") = tailleVenus;
    m.attr("couleurVenus") = couleurVenus;
    // Terre
    m.attr("earthYear") = earthYear;
    m.attr("rTerre") = rTerre;
    m.attr("masseTerre") = masseTerre;
    m.attr("tailleTerre") = tailleTerre;
    m.attr("couleurTerre") = couleurTerre;
    m.attr("w_terre") = w_terre;
    m.attr("incl_axe_rot_terre") = incl_axe_rot_tere;
    // Mars
    m.attr("masseMars") = masseMars;
    m.attr("tailleMars") = tailleMars;
    m.attr("couleurMars") = couleurMars;
    m.attr("rayonGeoStatMars") = rayonGeoStatMars;
    // Jupiter
    m.attr("masseJupiter") = masseJupiter;
    m.attr("tailleJupiter") = tailleJupiter;
    m.attr("couleurJupiter") = couleurJupiter;
    // Saturne
    m.attr("masseSaturne") = masseSaturne;
    m.attr("tailleSaturne") = tailleSaturne;
    m.attr("couleurSaturne") = couleurSaturne;
    // Uranus
    m.attr("masseUranus") = masseUranus;
    m.attr("tailleUranus") = tailleUranus;
    m.attr("couleurUranus") = couleurUranus;
    // Neptune
    m.attr("masseNeptune") = masseNeptune;
    m.attr("tailleNeptune") = tailleNeptune;
    m.attr("couleurNeptune") = couleurNeptune;
    
    /*Satellite*/
    //vitesses evasion terre
    m.attr("vEvasionMin") = vEvasionMin;
    m.attr("vEvasionMax") = vEvasionMax;
    //angles de lancement intials minimals et maximals
    m.attr("phiDebutMin") = phiDebutMin;
    m.attr("phiDebutMax") = phiDebutMax;
    m.attr("thetaDebutMin") = thetaDebutMin;
    m.attr("thetaDebutMax") = thetaDebutMax;
    //dimensions
    m.attr("tailleSatellite") = tailleSatellite;
    m.attr("masseSatellite") = masseSatellite;
    m.attr("couleurSatellite") = couleurSatellite;
}