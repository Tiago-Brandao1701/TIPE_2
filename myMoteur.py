import vpython as vp
from time import monotonic
from myAffichage import Affichage
from cstes import dt
from myTrouveCI import TrouveCI
from myTrajsTheoriques import *
from mySimulationLancer import SimulationLancer
from myAstre import Astre, AstreList
from myParamsLancer import ParamsLancer

'''
Commence par recuper les donnees du lancement opti et puis affiche la solution en boucle
'''

nomCible = "Mars"

class Moteur:
    def __init__(self):
        self.startTime = monotonic()
        self.running = True
        self.paused = False
        self.affichage = Affichage()
        self.realTime = 0       #temps en secondes
        self.chatGPT = TrouveCI(geostatMars,nomCible)
        self.echelle_distances = 1e-9


    #Print des paramsOpti et tps de sim ici pour 
    def getDonneesCPP(self):
        self.astres = self.chatGPT.astres
        self.satellite = self.chatGPT.satellite
        self.astres.append(self.satellite)
        self.nbPts = len(self.satellite.trajectoire)
        for i,astre in enumerate(self.astres):
            if astre.nom == nomCible:
                self.cible = astre
                self.i_cible = i
                break

    def toggle_pause(self, b):
        self.paused = not self.paused

        if self.paused:
            b.text = "Reprendre"
        else:
            b.text = "Pause"

    def run(self):
        try:
            self.paused = False

            self.paramsOpti = self.chatGPT.recherche()
            self.tpsSim = monotonic() - self.startTime

            print(f"paramsOpti: \n \t phi = {self.paramsOpti.phi} \n \t theta = {self.paramsOpti.theta} \n \t vitesse = {self.paramsOpti.vitesse}")
            print(f"temps de simulation :{self.tpsSim}")
            print(f"temps par simulation de lancer:{self.tpsSim/self.chatGPT.getNbSims()}")

            self.getDonneesCPP()
            t = 0
            tpsAffDebut = monotonic()

            self.representants = self.affichage.creerAstres(self.astres, self.i_cible)
            self.affichage.creer_boutons(self.astres)

            # Bouton pause
            vp.button(
                text="Pause",
                bind=self.toggle_pause
            )

            while self.running:
                vp.rate(600)

                # Si en pause, on saute la mise à jour
                if self.paused:
                    continue

                self.realTime += dt

                self.affichage.affichage(
                    self.astres,
                    self.realTime,
                    monotonic() - tpsAffDebut,
                    t,
                    self.i_cible
                )

                t = (t + 1) % self.nbPts

                if t == 0:
                    self.realTime = 0
                    tpsAffDebut = monotonic()

        finally:
            import time
            time.sleep(1)