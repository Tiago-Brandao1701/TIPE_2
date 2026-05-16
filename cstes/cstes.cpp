#define _USE_MATH_DEFINES
#include "cstes.h"

double deg_to_rad(double deg){
    return deg*M_PI/180.0;
}

//utiles au calcul
const double pi = M_PI;
const double doubleInfini = std::numeric_limits<double>::max();

//cstes physiques
const double dt = 4000.0;
const double G = 6.67430e-11;

/*cstes pour les methodes*/
//MonteCarlo 
const int nbEssaisMonteCarlo = 1000;
//Descente du gradient
const int nbIterDescenteGradient = 100;
const double dphi = 1e-3;
const double dtheta = 1e-3;
const double dvitesse = 20e-1;
const double pasApprentissageGradient = 1e-10;
//AdamW
const double beta1 = 0.9;
const double beta2 = 0.999;
const double epsilon = 1e-8;
const double weightDecay = 0.5; //paramètre réglable
//PSO
const int nbParticules = 30;
const int nbIterPSO = 100;  //parametres tous a regler    
const double inertie = 0.7;
const double coefCognitif = 1.4; 
const double coefSocial = 1.4;

//date
const int annee = 2020;
const int mois = 7;
const int jour = 30;
  
/*infos planetes*/
//Soleil
const double masseSoleil = 1.988e30;
const int tailleSoleil = 50;
const std::string couleurSoleil = "yellow";
//Mercure
const double masseMercure = 3.3011e23;
const int tailleMercure = 5;
const std::string couleurMercure = "grey";
//Vénus
const double masseVenus = 4.8675e24;
const int tailleVenus = 7;
const std::string couleurVenus = "orange";
//Terre
const int earthYear = 31558432;
const double rTerre = 6.371e6;
const double masseTerre = 5.97237e24;
const int tailleTerre = 10;
const std::string couleurTerre = "blue";
const double w_terre = 7.2921150e-5;
const double incl_axe_rot_tere = deg_to_rad(23.439281);
//Mars
const double masseMars = 6.4171e23;
const int tailleMars = 6;
const std::string couleurMars = "red";
const double rayonGeoStatMars = 17032e3;
//Jupiter
const double masseJupiter = 1.8982e27;
const int tailleJupiter = 30;
const std::string couleurJupiter = "orange";
//Saturne
const double masseSaturne = 5.6834e26;
const int tailleSaturne = 20;
const std::string couleurSaturne = "gold";
//Uranus
const double masseUranus = 8.6810e25;
const int tailleUranus = 15;
const std::string couleurUranus = "cyan";
//Neptune
const double masseNeptune = 1.02413e26;
const int tailleNeptune = 17;
const std::string couleurNeptune = "blue";

/*info satellite*/
//vitesses evasion
const double vEvasionMin = 5e3;
const double vEvasionMax = 40e3;
//angles de lancement intials minimals et maximals
const double phiDebutMin = 0;
const double phiDebutMax = 2.0*pi;
const double thetaDebutMin = -pi/4.0;
const double thetaDebutMax = pi/4.0;
//dimensions et couleur
const int tailleSatellite = 5;
const double masseSatellite = 1000.0;
const std::string couleurSatellite = "white";
