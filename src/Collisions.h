#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Window.hpp>

class CCollisions
{
    private:

    public:

        bool DectecterCollisionTirVaisseauEnnemi (sf::Vector2f PositionRocket, sf::Vector2f PositionEnnemi, sf::Vector2f EcartTir);
        bool DetecterCollisionRocketTirEnnemi (sf::Vector2f PositionRocket, sf::Vector2f PositionTirEnnemi, float EcartTir);
        bool DetecterCollisionTirEnnemiVaisseau (sf::Vector2f PositionTirEnnemi, sf::Vector2f PositionVaisseau, sf::Vector2f EcartTir);
        bool DetecterCollisionVaisseauEnnemi (sf::Vector2f PositionVaisseau, sf::Vector2f PositionEnnemi, sf::Vector2f Ecart);
};

#endif
