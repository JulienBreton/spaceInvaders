#ifndef GESTION_FONT_H
#define GESTION_FONT_H

#include <string.h>

//SFML
#include <SFML/Graphics.hpp>

class CGestionFont
{
    private:
                sf::Font MyFont;

    public:
                bool ChargerFichierFont (const std::string sNomFichierACharger, int iTailleDeLaPoliceChargee);
                sf::String AfficherTexte (std::string sTexteAAfficherfloat, float PosTexteX, float PosTexteY);
};

#endif
