from myVecteur import Vecteur, VecteurList
from myAstre import Astre, AstreList
from cstes import *
import vpython as vp

class Affichage:
    def __init__(self):
        # initialisation de la scene
        vp.scene.title = """Modélisation du système solaire"""

        # taille de la fenêtre VPython
        vp.scene.width = 1600
        vp.scene.height = 900

        # position et caméra
        vp.scene.center = vp.vector(0, 0, 0)
        vp.scene.forward = vp.vector(-1, -1, -1)
        vp.scene.range = 200

        self.echelle_distances = 1e-9
        self.i_centre = 0
        self.i_cible = 0
        self.representants = []
        

    
    def creerAstres(self,astres,i_cible):
        self.i_cible = i_cible
        couleurs_planetes=[vp.color.red, vp.color.yellow,vp.vector(0,0.58,0.69),vp.color.white]
        taille_planetes = [6,40,10,7]
        for i,astre in enumerate(astres):
            #print(f"creation de l'astre: {astre.nom}")
            if astre.nom != "satellite":
                self.representants.append(vp.sphere(pos=(vp.vector(astre.trajectoire[0].x,astre.trajectoire[0].y,astre.trajectoire[0].z))*self.echelle_distances,radius=taille_planetes[i],color=couleurs_planetes[i],make_trail =True))
                if astre.nom == "Soleil":
                    self.representants[i].emissive =True
                    self.representants[i].make_trail = False
            else:
                self.representants.append(vp.sphere(pos=vp.vector((vp.vector(astre.trajectoire[0].x + astres[i_cible].trajectoire[0].x,astre.trajectoire[0].y + astres[i_cible].trajectoire[0].y,astre.trajectoire[0].z +astres[i_cible].trajectoire[0].z))*self.echelle_distances),radius=taille_planetes[i],color=couleurs_planetes[i],make_trail =True))
        return self.representants

    def creer_boutons(self,astres):
        def mode_cinematique(evt):
            if evt.checked:
                vp.scene.lights=[]
                vp.local_light(pos=vp.vec(0, 0, 0), color=vp.color.yellow)
            else:
                vp.scene.lights=[]
                vp.distant_light(direction=vp.vec( 0.22, 0.44, 0.88), color=vp.color.white*0.8)
                vp.distant_light(direction=vp.vec( -0.88, -0.22, -0.44), color=vp.color.white*0.3)
                vp.scene.ambient = vp.color.white*0.2
        def centre_astre(evt):
            self.i_centre=evt.index
        bouton_cinematique = vp.checkbox( bind=mode_cinematique, text='mode cinématique\n', checked=False)
        choicelist = [astre.nom for astre in astres]
        vp.menu(choices=choicelist, bind=centre_astre,index = self.i_centre,selected="Choisir le centre")


    def afficheAstres(self,astres,t,i_cible):
        i_centre=self.i_centre
        if astres[i_centre].nom == "satellite":
            vp.scene.center=vp.vector((vp.vector(astres[i_centre].trajectoire[t].x + astres[i_cible].trajectoire[t].x,astres[i_centre].trajectoire[t].y + astres[i_cible].trajectoire[t].y,astres[i_centre].trajectoire[t].z +astres[i_cible].trajectoire[t].z))*self.echelle_distances)
        else:
            vp.scene.center=vp.vector(astres[i_centre].trajectoire[t].x,astres[i_centre].trajectoire[t].y,astres[i_centre].trajectoire[t].z)*self.echelle_distances

        
        for i,astre in enumerate(astres):
            if t==0:
                self.representants[i].clear_trail()
            if astre.nom!="satellite":
                self.representants[i].pos=vp.vector((vp.vector(astre.trajectoire[t].x,astre.trajectoire[t].y,astre.trajectoire[t].z))*self.echelle_distances)
            else:
                self.representants[i].pos=vp.vector((vp.vector(astre.trajectoire[t].x + astres[i_cible].trajectoire[t].x,astre.trajectoire[t].y + astres[i_cible].trajectoire[t].y,astre.trajectoire[t].z +astres[i_cible].trajectoire[t].z))*self.echelle_distances)
            

    def afficheTemps(self,realTime,tpsSim):
        global earthYear
        year=round(realTime/earthYear,3)
        #vp.scene.caption= (f"\n\n\n\nTemps réel : {year} années \nTemps simulation : {round(tpsSim,2)} secondes")


    def affichage(self,astres,realTime,tpsSim,t,i_cible):
        self.afficheAstres(astres,t,i_cible)
        self.afficheTemps(realTime,tpsSim)  

            
