#ifndef PARTICULES_H
#define PARTICULES_H

#include <list>

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
        unsigned int m_uiNbParticules;
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

        //ParametresParticules ParametrageParticules[NB_MAX_PARTICULES];

        struct ParametresParticules TempParametrageParticules;
        std::vector <ParametresParticules> ParametrageParticules;
        std::vector <ParametresParticules>::iterator it_ParametrageParticules;

        bool bFirstTour;

        CParticules();
        ~CParticules ();

        void InitialiserParticule (std::vector <ParametresParticules>::iterator &it, sf::Vector2f PositionVaisseau);
        void InitialiserImageParticule (sf::Image ImageDesParticules);
        void InitialiserGenerateurParticules(float tailleParticules, int nbParticules,
        sf::Vector2f fVitesseGenerateur, float fVitesseParticuleEnY, float espaceParticulesY,
        sf::Color couleurParticules, float tempsInitParticules, float dureeVieParticules,
        float departParticulesY);
        void ParticuleQuad (sf::Vector2f PositionVaisseau);
        sf::Vector2f GetPosition (std::vector <ParametresParticules>::iterator &it);
        float GetTransparence (std::vector <ParametresParticules>::iterator &it) const;
        bool GetFinVie (std::vector <ParametresParticules>::iterator &it) const;

        //Explosion
        void InitExplosion (float fTailleParticule, const sf::Vector2f & Position,
        unsigned int uiForce, float fDureeVie, sf::Color Couleur, float fElapsedTime);

        void CreerExplosion ();
};

#endif
