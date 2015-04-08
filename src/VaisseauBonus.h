#ifndef VAISSEAU_BONUS_H
#define VAISSEAU_BONUS_H

//Projet
#include "Particules.h" //#include <SFML/Window.hpp> #include <SFML/Graphics.hpp> #include "Utils.h"
#include "Explosion.h"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

class CVaisseauBonus
{
    private:
        sf::Image ImageVaisseauBonus;
        sf::Sprite SpriteVaisseauBonus;
        sf::Clock TimerVaisseauBonus;

        void DeplacerVaisseauBonus ();

    public:

        float m_fElapsedTimeVaisseauBonus;
        bool bVaisseauBonusKO;
        bool bVaisseauBonusExplose;
        sf::Vector2f m_TailleVaisseauBonus;

        CExplosion IExplosionVaisseauBonus;
        sf::Clock TimerExplosionVaisseauBonus;

        bool InitialiserVaisseauBonus (sf::Image& ImageDuVaisseauBonus);
        void AfficherVaisseauBonus (sf::RenderWindow& AppVaisseauBonus);
        sf::Vector2f GetPositionVaisseauBonus ();
        sf::Vector2f GetTailleVaisseauBonus ();
        sf::Vector2f GetCentreVaisseauBonus ();
};

#endif
