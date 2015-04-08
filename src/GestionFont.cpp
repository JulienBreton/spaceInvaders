#include "GestionFont.h"

bool CGestionFont::ChargerFichierFont (const std::string sNomFichierACharger, int iTailleDeLaPoliceChargee)
{
    //[!] Request to deallocate RAM that was never allocated
    if (!MyFont.LoadFromFile(sNomFichierACharger, iTailleDeLaPoliceChargee))
        return false;
    else
        return true;
}

sf::String CGestionFont::AfficherTexte (std::string sTexteAAfficher, float fPosTexteX, float fPosTexteY)
{
    sf::String Texte(sTexteAAfficher, MyFont, 10);
    Texte.SetPosition(fPosTexteX, fPosTexteY);

    return Texte;
}
