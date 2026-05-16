from skyfield.api import load
import json
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from cstes import *

'''
cree le fichier json avec les infos de toutes les planètes, le soleil (et peut-être 
un jour tous les astres) du système solaire
Les vecteurs position et vitesse crées sont en unités S.I. dans le repère (Soleil, base eliptique)
'''

class AstreInfo:
    def __init__(self, nom, masse, taille, couleur, eph_name):
        self.nom = nom
        self.masse = masse
        self.taille = taille
        self.couleur = couleur
        self.eph_name = eph_name

#Construction des Astres
def constitueFichierDonnees():
    nbreAstres = 0
    #load planetary ephemeros data
    astresData = {}
    ts = load.timescale()
    t = ts.utc(annee,mois,jour,14,7) #date
    eph = load('de421.bsp')
    sun =  eph['sun']
    #constitue donnees de tous les astres mineurs (futur)

    #constitue données planètes
    planets_info = [
        AstreInfo("Soleil", masseSoleil, tailleSoleil, couleurSoleil, "sun"),
        #AstreInfo("Mercure", masseMercure, tailleMercure, couleurMercure, "mercury"),
        #AstreInfo("Venus", masseVenus, tailleVenus, couleurVenus, "venus"),
        AstreInfo("Terre", masseTerre, tailleTerre, couleurTerre, "earth"),
        AstreInfo("Mars", masseMars, tailleMars, couleurMars, "mars"),
        #AstreInfo("Jupiter", masseJupiter, tailleJupiter, couleurJupiter, "jupiter barycenter"),
        #AstreInfo("Saturne", masseSaturne, tailleSaturne, couleurSaturne, "saturn barycenter"),
        #AstreInfo("Uranus", masseUranus, tailleUranus, couleurUranus, "uranus barycenter"),
        #AstreInfo("Neptune", masseNeptune, tailleNeptune, couleurNeptune, "neptune barycenter"),
    ]
    for planetInfo in planets_info:
        planete = eph[planetInfo.eph_name]
        x,y,z=sun.at(t).observe(planete).ecliptic_position().m
        vx,vy,vz = sun.at(t).observe(planete).ecliptic_velocity().m_per_s
        astresData[planetInfo.nom] = {
        'x': x,
        'y': y,
        'z': z,
        'vx':vx,
        'vy':vy,
        'vz':vz,
        'nom':planetInfo.nom,
        'couleur':planetInfo.couleur,
        'masse':planetInfo.masse,
        'taille':planetInfo.taille
        }
        nbreAstres += 1 
    astresData["nbreAstres"] = nbreAstres
    script_dir = os.path.dirname(os.path.abspath(__file__))
    output_path = os.path.join(script_dir, 'astresData.json')
    with open(output_path, 'w') as f:
        json.dump(astresData, f, indent=2)

    #constitue donnees de tous les astres mineurs (futur)    
if (__name__ == '__main__'):
    constitueFichierDonnees()
