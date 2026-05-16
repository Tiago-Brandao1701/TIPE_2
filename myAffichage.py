from myVecteur import Vecteur, VecteurList
from myAstre import Astre, AstreList
from cstes import *
import pygame

'''
Gere simplement l'affichage de la solution
'''

class Affichage:
    def __init__(self):
        #camera
        self.cam = Vecteur(0,0,0)
        self.echelle = 1e-9  
        self.vitesse = 5
        #ecran
        self.screen = pygame.display.set_mode((1280, 720))
        self.screen_dim = Vecteur(self.screen.get_width(), self.screen.get_height(), 0)

    #l'affichage est fait en 2D, puisque tout est globalement dans le meme plan
    def affichage(self,astres,satellite,cible,realTime,t):
        self.screen.fill("black")
        self.afficheAstres(astres,satellite,cible,t)
        self.afficheTemps(realTime)
        pygame.display.update()
    
    def afficheAstres(self,astres, satellite,cible,t):
        for astre in astres:
            if astre.nom == satellite.nom :
                position_x_y = (
                    self.screen_dim.x/2 + (cible.trajectoire[t].x+astre.trajectoire[t].x)*self.echelle +self.cam.x,
                    self.screen_dim.y/2 + (cible.trajectoire[t].y+astre.trajectoire[t].y)*self.echelle + self.cam.y
                    )
            else:   
                position_x_y = (
                    self.screen_dim.x/2 + astre.trajectoire[t].x*self.echelle +self.cam.x,
                    self.screen_dim.y/2 + astre.trajectoire[t].y*self.echelle + self.cam.y
                    )
            pygame.draw.circle(self.screen, astre.couleur, position_x_y , astre.taille_aff)
            #print(f"{astre.nom} screen position: ({position_x_y}),({astre.acc.x},{astre.acc.y},{astre.acc.z})")

    def afficheTemps(self,t):
        global earthYear
        year=round(t/earthYear,3)
        font=pygame.font.Font(None,16)
        txt=font.render(f"{year} années ou {t} secondes",True,(255,255,255))
        self.screen.blit(txt,(100,650))
            

            
