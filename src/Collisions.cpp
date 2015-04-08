#include "Collisions.h"

bool CCollisions::DectecterCollisionTirVaisseauEnnemi (sf::Vector2f PositionRocket, sf::Vector2f PositionEnnemi, sf::Vector2f EcartTir)
{
    bool bCollisionDetecter = false;

    /*if (
        (PositionRocket.x <= (PositionEnnemi.x+EcartTir.x)) && (PositionRocket.x >= (PositionEnnemi.x-EcartTir.x))
        &&
        (PositionRocket.y <= (PositionEnnemi.y+EcartTir.y)) && (PositionRocket.y >= (PositionEnnemi.y-EcartTir.y))
       )
        {
            bCollisionDetecter = true;
        }*/

    if (
        (PositionRocket.x <= (PositionEnnemi.x+EcartTir.x)) && (PositionRocket.x >= (PositionEnnemi.x))
        &&
        (PositionRocket.y <= (PositionEnnemi.y+EcartTir.y)) && (PositionRocket.y >= (PositionEnnemi.y))
       )
        {
            bCollisionDetecter = true;
        }


    return bCollisionDetecter;
}

bool CCollisions::DetecterCollisionRocketTirEnnemi (sf::Vector2f PositionRocket, sf::Vector2f PositionTirEnnemi, float EcartTir)
{
    bool bCollisionDetecter = false;

    if (
        (PositionRocket.x <= (PositionTirEnnemi.x+EcartTir/2)) && (PositionRocket.x >= (PositionTirEnnemi.x-EcartTir/2))
        &&
        (PositionRocket.y <= (PositionTirEnnemi.y+EcartTir/2)) && (PositionRocket.y >= (PositionTirEnnemi.y-EcartTir/2))
       )
        {
            bCollisionDetecter = true;
        }

    return bCollisionDetecter;
}

bool CCollisions::DetecterCollisionTirEnnemiVaisseau (sf::Vector2f PositionTirEnnemi, sf::Vector2f PositionVaisseau, sf::Vector2f EcartTir)
{
    bool bCollisionDetecter = false;

    if (
        (PositionTirEnnemi.x <= (PositionVaisseau.x+EcartTir.x/2)) && (PositionTirEnnemi.x >= (PositionVaisseau.x-EcartTir.x/2))
        &&
        (PositionTirEnnemi.y <= (PositionVaisseau.y+EcartTir.y/2)) && (PositionTirEnnemi.y >= (PositionVaisseau.y-EcartTir.y/2))
       )
        {
            bCollisionDetecter = true;
        }

    return bCollisionDetecter;
}

/*bool DetecterCollisionVaisseauEnnemi (sf::Vector2f PositionVaisseau, sf::Vector2f PositionEnnemi, sf::Vector2f Ecart);
{
    bool bCollisionDetecter = false;

    if (
        (PositionTirEnnemi.x <= (PositionVaisseau.x+EcartTir.x/2)) && (PositionTirEnnemi.x >= (PositionVaisseau.x-EcartTir.x/2))
        &&
        (PositionTirEnnemi.y <= (PositionVaisseau.y+EcartTir.y/2)) && (PositionTirEnnemi.y >= (PositionVaisseau.y-EcartTir.y/2))
       )
        {
            bCollisionDetecter = true;
        }

    return bCollisionDetecter;
}*/
