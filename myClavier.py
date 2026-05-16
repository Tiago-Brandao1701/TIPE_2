import pygame

'''
Gere les inputs de l'utilisateur
'''

class Clavier:

    def __init__(self):
        self.keys=pygame.key.get_pressed()

    def getInput(self):
        self.keys=pygame.key.get_pressed()

    def camera(self,cam,vitesse):
        keys = self.keys
        if keys[pygame.K_LEFT]:
            cam.x +=1/vitesse
        if keys[pygame.K_RIGHT]:
            cam.x -=1/vitesse
        if keys[pygame.K_UP]:
            cam.y +=1/vitesse
        if keys[pygame.K_DOWN]:
            cam.y -=1/vitesse
        return cam
    
    def zoom(self,echelle):
        keys = self.keys
        if keys[pygame.K_KP_PLUS]:
            echelle*=1.001
        if keys[pygame.K_KP_MINUS]:
            echelle/=1.001
        return echelle
    
    def debut(self):
        return (self.keys[pygame.K_SPACE])
        