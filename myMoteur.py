import pygame
from myAffichage import Affichage
from myClavier import Clavier
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
        pygame.init()
        self.clock = pygame.time.Clock()
        self.running = True
        self.affichage = Affichage()
        self.clavier = Clavier()    #gere les inputs
        self.realTime = 0       #temps en secondes
        self.chatGPT = TrouveCI(geostatMars,nomCible)
        print("apres chat gpt")

    def messangerClavierAffichage(self):
        self.affichage.cam=self.clavier.camera(self.affichage.cam,self.affichage.vitesse)
        self.affichage.echelle=self.clavier.zoom(self.affichage.echelle)

    #Print des paramsOpti et tps de sim ici pour 
    def getDonneesCPP(self):
        self.astres = self.chatGPT.astres
        self.satellite = self.chatGPT.satellite
        self.astres.append(self.satellite)
        self.nbPts = len(self.satellite.trajectoire)
        for astre in self.astres:
            if astre.nom == nomCible:
                self.cible = astre
                break

    def run(self):
        self.paramsOpti = self.chatGPT.recherche()
        self.tpsSim = pygame.time.get_ticks()/1000
        print(f"paramsOpti: \n \t phi = {self.paramsOpti.phi} \n \t theta = {self.paramsOpti.theta} \n \t vitesse = {self.paramsOpti.vitesse}")
        print(f"temps de simulation :{self.tpsSim}")
        print(f"temps par simulation de lancer:{self.tpsSim/self.chatGPT.getNbSims()}")
        self.getDonneesCPP()
        t=0
        while self.running:
            self.realTime += dt
            self.clavier.getInput()
            self.messangerClavierAffichage()
            self.affichage.affichage(self.astres,self.satellite,self.cible,self.realTime, t)
            t= (t+1)%self.nbPts
            if t == 0:
                self.realTime = 0
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
