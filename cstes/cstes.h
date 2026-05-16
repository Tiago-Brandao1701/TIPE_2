//cstes.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <climits>
#include <cmath> // for M_PI


/*
TOUTES LES CSTES MUAHAHHAHAHAHAHA (il y en a de plus en plus mdr rip
Peut etre un jour ce sera organise avec des name spaces mais pour l'instant comme ca a
cause de python
*/

/*utiles au calcul*/
extern const double pi;
extern const double doubleInfini;

/*cstes pour les methodes*/
//Montecarlo
extern const int nbEssaisMonteCarlo;
//Descente du gradient
extern const int nbIterDescenteGradient;
extern const double dphi;
extern const double dtheta;
extern const double dvitesse;
extern const double pasApprentissageGradient;
//AdamW
extern const double beta1;
extern const double beta2;
extern const double epsilon;
extern const double weightDecay; //paramètre réglable
//PSO
extern const int nbParticules;
extern const int nbIterPSO;
extern const double inertie;
extern const double coefSocial;
extern const double coefCognitif;

/*cstes physiques*/
extern const double dt;
extern const double G;

/*date*/
extern const int annee;
extern const int mois;
extern const int jour;

/*infos astres*/
//Soleil
extern const double masseSoleil;
extern const int tailleSoleil;
extern const std::string couleurSoleil;
//Mercure
extern const double masseMercure;
extern const int tailleMercure;
extern const std::string couleurMercure;
//Mars
extern const double masseMars;
extern const int tailleMars;
extern const std::string couleurMars;
extern const double rayonGeoStatMars;
//Terre
extern const int earthYear;
extern const double rTerre;
extern const double masseTerre;
extern const int tailleTerre;
extern const std::string couleurTerre;
extern const double w_terre;
extern const double incl_axe_rot_tere;
//Venus
extern const double masseVenus;
extern const int tailleVenus;
extern const std::string couleurVenus;
// Jupiter
extern const double masseJupiter;
extern const int tailleJupiter;
extern const std::string couleurJupiter;
// Saturne
extern const double masseSaturne;
extern const int tailleSaturne;
extern const std::string couleurSaturne;
// Uranus
extern const double masseUranus;
extern const int tailleUranus;
extern const std::string couleurUranus;
// Neptune
extern const double masseNeptune;
extern const int tailleNeptune;
extern const std::string couleurNeptune;

/*infos satellite*/
//vitesses evasion terre
extern const double vEvasionMin;
extern const double vEvasionMax;
//angles de lancement intials minimals et maximals
extern const double phiDebutMin;
extern const double phiDebutMax;
extern const double thetaDebutMin;
extern const double thetaDebutMax;
//dimensions
extern const int tailleSatellite;
extern const double masseSatellite;
extern const std::string couleurSatellite;

#endif
//CONSTANTS_H