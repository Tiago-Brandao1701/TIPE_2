
#include "SimulationLancer.h"

SimulationLancer::SimulationLancer(
    std::vector<Astre>& astres_,
    const Astre& cible_,
    const Astre& terre_
)
    : nbSimulations(0),
      astres(astres_),
      cible(cible_),
      terre(terre_),
      satellite(creeSatellite()),
      nbPts(0),
      t(0),
      initTrajAstres(true)
{}


void SimulationLancer::trouveNbPts() {
    double vitesse = paramsLancer.vitesse;
    if (vitesse == 0 || dt == 0){
        nbPts = 0;
        std::cout<<"vitesse = 0"<<std::endl;
    }        
    else{
        double d = cible.trajectoire[0].distance(terre.trajectoire[0]);
        nbPts = 5*static_cast<int>(((d / vitesse) / dt) * 20.0);
        int nbPts_an = (5*3600*24*366)/dt;
        if (nbPts > nbPts_an){
            nbPts = nbPts_an;
        }
    }
}

Vecteur SimulationLancer::trouvePosSatellite() const {
    double phi = paramsLancer.phi;
    double theta = paramsLancer.theta;
    Vecteur posTerre = terre.trajectoire[0];
    return (Vecteur(
                posTerre.x + rTerre*sin(theta)*cos(phi),
                posTerre.y + rTerre*sin(theta)*sin(phi),
                posTerre.z + rTerre*cos(theta)));
}

Vecteur SimulationLancer::trouveVitesseSatellite() const {
    Vecteur vTerre = terre.vitesseInitiale;
    double phi = paramsLancer.phi;
    double theta = paramsLancer.theta;
    double vitesse = paramsLancer.vitesse;
    //position du satelite en relation au centre de la terre
    Vecteur r_rel(
        rTerre * sin(theta) * cos(phi),
        rTerre * sin(theta) * sin(phi),
        rTerre * cos(theta)
    );
    //vitesse due au mouvement de la terre au tour du soleil
    Vecteur v_rad =Vecteur(
                vTerre.x + vitesse*sin(theta)*cos(phi),
                vTerre.y + vitesse*sin(theta)*sin(phi),
                vTerre.z + vitesse*cos(theta));
    //axe de rotation de la terre dans le referentiel J12000
    Vecteur s_hat(0.0, -sin(incl_axe_rot_tere), cos(incl_axe_rot_tere));
    //vecteur de rotation de la terre
    Vecteur omega_vec(s_hat.x * w_terre, s_hat.y * w_terre, s_hat.z * w_terre);
    //vitesse due a la rotation de la terre
    Vecteur v_rot = omega_vec.prod_vect(r_rel);
    
    return v_rad + v_rot;
}

Astre SimulationLancer::creeSatellite() {
    Astre satelliteCree = Astre(
            "satellite",
            couleurSatellite,
            tailleSatellite,
            masseSatellite,
            trouvePosSatellite(),
            trouveVitesseSatellite()
    );
    return satelliteCree;
}

void SimulationLancer::update(){
    Logique::rk(astres, satellite, t, initTrajAstres);
    satellite.move();
    satellite.trajectoire[t] = satellite.pos - cible.trajectoire[t];
    t+=1;
}

std::vector<Vecteur> SimulationLancer::simulation(){
    //reset tout pour simuler un nouveau lancer
    t=0;
    trouveNbPts();
    satellite.trajectoire.clear();
    satellite.trajectoire.resize(nbPts);
    satellite.pos = trouvePosSatellite();
    satellite.vitesse = trouveVitesseSatellite();
    //simulation
    while (t<nbPts){
        update();
    }
    nbSimulations += 1;
    return (satellite.trajectoire);
}
        
void SimulationLancer::initTrajectoires(){
    t = 0;
    paramsLancer.vitesse = vEvasionMin/2.0;
    std::cout<<vEvasionMin/2.0<<std::endl;
    std::cout<<paramsLancer.vitesse<<std::endl;
    trouveNbPts();
    
    for (Astre& astre : astres){
        std::cout <<astre.nom<<" pos: ("<<astre.pos.x<<","<<astre.pos.y<<","<<astre.pos.z<<")"<<std::endl;
        astre.trajectoire.resize(nbPts);
    }
    while(t<nbPts){
        for (Astre& astre : astres){
            astre.trajectoire[t] = astre.pos;
        }
        for (Astre& astre : astres){
            Logique::rk(astres, astre, t, initTrajAstres);
        }
        for(Astre& astre : astres){
            astre.move();
        }
        t += 1;  
    }
    std::cout << std::endl;
    for (Astre& astre : astres){
        std::cout <<astre.nom<<" pos finale: ("<<astre.trajectoire[nbPts-2].x<<","<<astre.trajectoire[nbPts-2].y<<","<<astre.trajectoire[nbPts-2].z<<")"<<std::endl;
    }
    std::cout << std::endl;
    std::cout<<"initialisation des trajectoires terminees\n"<<std::endl;
    nbSimulations += 1; 
    initTrajAstres = false;
}

Astre SimulationLancer::getSatellite(){
    return satellite;
}

void SimulationLancer::updateCI(ParamsLancer newParams){
    paramsLancer.phi = fmod(newParams.phi, 2*pi);
    paramsLancer.theta = fmod(newParams.theta, 2*pi);
    paramsLancer.vitesse = newParams.vitesse;
}


