#ifndef FENETRE_SFML_H
#define FENETRE_SFML_H

#include <unistd.h>

//Projet
#include "GestionFont.h"
#include "Render.h"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define BITS_PAR_PIXEL 32
#define TITRE "Fenetre SFML"

//#define DEBUG_JEU
#define PLAY

#ifdef DEBUG_JEU
#define PLEIN_ECRAN false
#endif

#ifdef PLAY
#define PLEIN_ECRAN true
#endif

class CFenetreSFML
{
    private:
                CUtils ICUtils;
                CGestionFont IGestionFont;
                CRender IRender;

                sf::RenderWindow App;

    public:
                CFenetreSFML ();
                ~CFenetreSFML ();

                bool CreerFenetreSFML
                (unsigned int LargeurFenetre, unsigned int HauteurFenetre,
                unsigned int ProfondeursBitsParPixel, std::string Titre, bool PleinEcran);
};

#endif
