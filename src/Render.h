#ifndef RENDER_H
#define RENDER_H

//Projet
#include "GestionSprite.h"  //#include <string.h> #include <SFML/Graphics.hpp>
#include "Vaisseau.h" //#include "Particules.h"
#include "Rocket.h" //#include "Particules.h"
#include "Ennemis.h" //#include "Particules.h" #include "RecupDonneesXML.h
#include "Collisions.h"
#include "Menus.h"
#include "VaisseauBonus.h"
#include "Sons.h"

//Initialisation de la scéne
#define INITIALISATION_SCENE_OK 1
#define ERREUR_CHARGEMENT_FICHIER_FONT -1
#define ERREUR_INIT_ARMEE_ENNEMIE -2
#define ERREUR_CHARGEMENT_IMAGES -3
#define ERREUR_CHARGEMENT_SONS -4

class CRender
{
    private:
            CGestionSprite IGestionSprite;
            CVaisseau IVaisseau;
            CCollisions ICollisions;
            CMenus IMenus;
            CGestionFont IRenderFont;
            CVaisseauBonus IVaisseauBonus;
            //CEnnemis IEnnemis;
            CRocket IRocket;
            CSons IRenderSons;

            sf::Image ImageParticule;

            sf::Image ImageBackGround;
            sf::Sprite SpriteBackGround;

            //Niveaux
            sf::Clock TimeAffichageNiveauEnCours;

            //Affichage
            float m_fElapsedTimeRender;

            void RenderCollisions();

    public:
            CRender ();
            ~CRender ();

            CEnnemis IEnnemis;

            bool m_bJeuCommence;
            bool m_bVieVaisseau;
            float m_fDegatsVaisseau;
            unsigned int m_uiPointsDeVieVaisseau;

            //Score
            unsigned int m_uiScore;

            unsigned int m_uiNbTotalEnnemisRender;
            unsigned int m_uiNbEnnemisKORender;
            unsigned int m_uiNiveauxEnCours;

            int InitialiserScene ();
            void RenderScene(sf::RenderWindow& AppRender);
            void GetElapsedTime (float ElapsedTime);
};

#endif

