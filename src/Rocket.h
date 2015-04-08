#ifndef __ROCKET_H
#define __ROCKET_H

#include <list>

//Projet
#include "Particules.h" //#include <SFML/Window.hpp> #include <SFML/Graphics.hpp> #include "Utils.h"
#include "Sons.h"

class CRocket
{
	private:

        //Rocket
        float m_fDepartRocket;


        //Flamme
        float m_fTailleParticuleRocket;
        float m_fEspaceYEntreParticulesRockets;
        float m_fTempsReinitParticulesRockets;
        float m_fDureeVieParticulesRockets;
        float m_fVitesseParticulesEnY;
        unsigned int m_iNbParticulesRocket;

        sf::Clock TpsCadenceTirsJoueur;

        sf::SoundBuffer m_BufferNouvelleRocket;

	public:

        float m_fVistesseRocket;

		//Structure rocket
        struct ParametresRocket
        {
  			float rocketTranslationX;
		   	float rocketTranslationY;

            bool rocketExplosee;
		   	bool rocketOut;

            CParticules pRocketsParticules;

            sf::Sound SonNouveauTir;
            bool bSonNouvelleRocketJoue;
		};

  		struct ParametresRocket TempParametrageRocket;
	    std::list <ParametresRocket> ParametrageRocket;
        std::list <ParametresRocket>::iterator it_ParametrageRocket;

        float RocketTempsInitParticules;
        float m_fElapsedTimeRocket;

		//Clavier
        bool espace_appuye;
		bool espace_gere;

        unsigned int nbRockets;

        CRocket();
        ~CRocket();

        //Fonctions
		void InitialiserRocket ();
		void InitialiserSonsRocket (sf::SoundBuffer& BufferTirRocket);
		void DessinerRocket(sf::RenderWindow& AppRocket, sf::Vector2f PositionDuVaisseau);
		void CreerNouvelleRocket(sf::Vector2f PositionVaisseau);
		void EstDansEcran (float fRayon, std::list <ParametresRocket>::iterator it);
};

#endif
