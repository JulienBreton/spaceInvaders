#ifndef GESTION_SRIPTE_H
#define GESTION_SPRITE_H

#include <string.h>

//SFML
#include <SFML/Graphics.hpp>

//Debug
//#include "mmgr.h"

class CGestionSprite
{
    private:

    public:
            bool ChargerFichierSprite (const std::string sNomFichierACharger, sf::Image& Image);
};

#endif

