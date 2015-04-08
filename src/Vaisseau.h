#ifndef VAISSEAU_H
#define VAISSEAU_H

//Projet
//#include "Particules.h" //#include <SFML/Window.hpp> #include <SFML/Graphics.hpp> #include "Utils.h"
#include "Explosion.h"

//Debug
//#include "mmgr.h"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

class CVaisseau
{
    private:
                sf::Sprite SpriteVaisseau;
                sf::Image ImageVaisseau1;
                sf::Image ImageVaisseau2;

                float m_fPositionVaisseauXDepart;
                float m_fPositionVaisseauYDepart;
                sf::Vector2f m_PositionFlamme;

                CExplosion IExplosionVaisseau;

                void DeplacerVaisseau ();
                sf::Vector2f PositionnerFlamme ();

    public:
                CVaisseau ();
                ~CVaisseau ();

                CParticules pParticulesVaisseau;

                float m_fElapsedTimeVaisseau;
                bool m_bvaisseauToucheParEnnemis;
                sf::Vector2f m_TailleVaisseau;
                sf::Vector2f m_PositionVaisseau;
                sf::Clock m_TimerEplosionVaisseau;

                struct ParametresTirEnnemi
                {
                    unsigned int uiEnergiebouclier;
                    float fTransparenceBouclier;
                };

                void InitialiserVaisseau (sf::Image& ImageDuVaisseau1, sf::Image& ImageDuVaisseau2);
                void AfficherVaisseau (sf::RenderWindow& AppVaisseau);
                void InitialiserExplosionVaisseau ();
                void ExplosionVaisseau ();
                sf::Vector2f GetPositionVaisseau ();
                sf::Vector2f GetTailleVaisseau ();
};

#endif
