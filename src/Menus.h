#ifndef MENUS_H
#define MENUS_H

#include "GestionFont.h"
#include "Utils.h"

class CMenus
{
    private:

        CGestionFont IFontMenus;
        CUtils IUtilsMenus;

        std::vector <sf::String> MenuPrincipal;
        sf::Image m_ImageJaugeVie;
        sf::Image m_ImageVie;
        unsigned int m_uiPointsDeVie;

    public:

        CMenus ();
        ~CMenus ();

        bool ChargerFontMenus ();
        void InitialiserAffichageMenu ();
        void InitialiserImagesMenu (std::vector <sf::Image> ImagesMenu);
        bool AfficherFontMenus (sf::RenderWindow &AppMenus);
        void AfficherNiveaux (sf::RenderWindow &AppNiveaux, unsigned int uiNiveauxEnCours);
        void AfficherScore (sf::RenderWindow &AppScore, unsigned int uiScore);
        void AfficherVie (sf::RenderWindow &AppVie, float fNiveauVie, unsigned int uiPointsDeVie);

};
#endif
