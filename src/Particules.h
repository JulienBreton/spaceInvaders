#ifndef PARTICULES_H
#define PARTICULES_H

#include <vector>
#include <iostream>

//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Projet
#include "Utils.h"

#define NB_MAX_PARTICULES 100

class CParticules
{
    public:

        sf::Clock Timer;

        sf::Vector2f Acceleration;
        sf::Vector2f PositionVaisseau;

        sf::Image ImageParticule;
        sf::Sprite SpriteParticule;

        CUtils IUtilsParticules;

        //Particules
        int m_nbParticules;
        float m_espaceYEntreParticules;
        float m_tempsInitParticules;
        float m_dureeVieParticules;
        float m_departParticulesY;
        float m_fPositionYGenerateur;
        float m_fVitesseParticuleEnY;
        float m_ftailleParticules;
        float m_fElapsedTimeParticule;
        sf::Vector2f m_VitesseF;
        sf::Vector2f m_Position;
        sf::Vector2f m_VitesseGenerateur;
        sf::Color m_Couleur;

        //Explosion
	    float m_fTailleParticule_Explosion;
	    float m_fDureeVie_Explosion;
	    unsigned int m_uiForce;
	    sf::Vector2f m_Position_Explosion;
	    sf::Color m_Couleur_Explosion;
	    sf::Clock m_DureeVie_Explosion;
	    sf::Clock m_TempsExplosion;

        struct ParametresParticules
        {
            sf::Clock Temps;
            sf::Vector2f PositionParticule;
            sf::Vector2f VitesseParticule;
            float fTempsVieParicule;
            float fTransparenceParticule;
            sf::Vector2f AccelerationParticule;
        };

        ParametresParticules ParametrageParticules[NB_MAX_PARTICULES];

        bool bFirstTour;

        CParticules();
        ~CParticules ();

        void InitialiserParticule (int iIndexParticules, sf::Vector2f PositionVaisseau);
        void InitialiserImageParticule (sf::Image ImageDesParticules);
        void InitialiserGenerateurParticules(float tailleParticules, int nbParticules,
        sf::Vector2f fVitesseGenerateur, float fVitesseParticuleEnY, float espaceParticulesY,
        sf::Color couleurParticules, float tempsInitParticules, float dureeVieParticules,
        float departParticulesY);
        void ParticuleQuad (sf::Vector2f PositionVaisseau);
        sf::Vector2f GetPosition (int iIndexParticules);
        float GetTransparence (int iIndexParticules) const;
        bool GetFinVie (int iIndexParticules) const;

        //Explosion
        void InitExplosion (float fTailleParticule, const sf::Vector2f & Position,
        unsigned int uiForce, float fDureeVie, sf::Color Couleur, float fElapsedTime);

        void CreerExplosion ();
};

#endif
