#include "GestionSprite.h"

bool CGestionSprite::ChargerFichierSprite (const std::string sNomFichierACharger, sf::Image& MonImage)
{
   bool bChargementImage = false;

   bChargementImage = MonImage.LoadFromFile(sNomFichierACharger);

   return bChargementImage;
}

