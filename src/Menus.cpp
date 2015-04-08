#include "Menus.h"

CMenus::CMenus ()
{

}

CMenus::~CMenus ()
{
    MenuPrincipal.clear ();
}

bool CMenus::ChargerFontMenus ()
{
    bool bChargementFont = false;

    if (IFontMenus.ChargerFichierFont ("data/font/comic.ttf", 50))
    {
        bChargementFont = true;
    }

    return bChargementFont;
}

void CMenus::InitialiserAffichageMenu ()
{
    sf::String NouvellePartie =
    IFontMenus.AfficherTexte ("Nouvelle Partie", 200.f, 200.f);
    NouvellePartie.SetSize(50.f);

    MenuPrincipal.push_back(NouvellePartie);

    sf::String Quitter =
    IFontMenus.AfficherTexte ("Quitter", 200.f, 250.f);
    Quitter.SetSize(50.f);

    MenuPrincipal.push_back(Quitter);

    sf::String Curseur =
    IFontMenus.AfficherTexte (">", 180.f, 200.f);
    Curseur.SetSize(50.f);

    MenuPrincipal.push_back(Curseur);
    m_uiPointsDeVie = 0;

    /*sNouvelle = MenuPrincipal[0];
    sQuitter = MenuPrincipal[1];
    sCurseur = MenuPrincipal[2];*/
}

void CMenus::InitialiserImagesMenu (std::vector <sf::Image> ImagesMenu)
{
    m_ImageJaugeVie = ImagesMenu[0];
    m_ImageVie = ImagesMenu[1];
}

bool CMenus::AfficherFontMenus (sf::RenderWindow &AppMenus)
{
    sf::String sNouvelle = MenuPrincipal[0];
    sf::String sQuitter = MenuPrincipal[1];
    sf::String sCurseur = MenuPrincipal[2];

    bool bJeuCommence = false;

    sf::Vector2f PositionCurseur;

    //Curseur
    if (AppMenus.GetInput().IsKeyDown(sf::Key::Up))
    sCurseur.SetPosition(180, 200);

    if (AppMenus.GetInput().IsKeyDown(sf::Key::Down))
    sCurseur.SetPosition(180, 250);

    PositionCurseur = sCurseur.GetPosition ();

    MenuPrincipal[2] = sCurseur;

    if (PositionCurseur.y == 200.f
        && AppMenus.GetInput().IsKeyDown(sf::Key::Return))
        bJeuCommence = true;

    if (PositionCurseur.y == 250.f
        && AppMenus.GetInput().IsKeyDown(sf::Key::Return))
        AppMenus.Close ();

    AppMenus.Draw(sNouvelle);
    AppMenus.Draw(sQuitter);
    AppMenus.Draw(sCurseur);

    return bJeuCommence;
}

void CMenus::AfficherNiveaux (sf::RenderWindow &AppNiveaux, unsigned int uiNiveauxEnCours)
{
    sf::String sNiveau =
    IFontMenus.AfficherTexte ("Niveau " + IUtilsMenus.ConvertirFloatEnString (uiNiveauxEnCours), 180.f, 200.f);
    sNiveau.SetSize(50.f);

    AppNiveaux.Draw(sNiveau);
}

void CMenus::AfficherScore (sf::RenderWindow &AppScore, unsigned int uiScore)
{
    sf::String sScore =
    IFontMenus.AfficherTexte (IUtilsMenus.ConvertirFloatEnString (uiScore), 88.f, 570.f);
    sScore.SetSize(20.f);

    AppScore.Draw(sScore);
}

void CMenus::AfficherVie (sf::RenderWindow &AppVie, float fNiveauVie, unsigned int uiPointsDeVie)
{
    sf::Sprite SpriteJaugeVie;
    sf::Sprite SpriteVie1;
    sf::Sprite SpriteVie2;
    sf::Sprite SpriteVie3;

    //m_ImageJaugeVie.CreateMaskFromColor (sf::Color(0, 255, 255, 128), 1);

    SpriteJaugeVie.SetImage (m_ImageJaugeVie);
    SpriteVie1.SetImage (m_ImageVie);

    SpriteJaugeVie.SetPosition (2 ,567);

    SpriteJaugeVie.Resize (40, 33);
    //SpriteVie1.Resize (123, 25);

    //SpriteVie2 = SpriteVie1;
    //SpriteVie3 = SpriteVie1;

    //SpriteVie2.Resize (39 , 23);
    //SpriteVie3.Resize (39 , 23);

    SpriteVie1.SetPosition (0, 600 - 33);
    //SpriteVie2.SetPosition (12 + 40,591 - 25);
    //SpriteVie3.SetPosition (13 + 80,591 - 25);

    SpriteJaugeVie.SetColor(sf::Color(255, 255, 255, fNiveauVie));

    if (fNiveauVie == 0)
    {
        SpriteJaugeVie.SetColor(sf::Color( 1, 1, 1, 255));
    }

    //Alpha, Add, Multiply, None
    //SpriteVie1.SetBlendMode (sf::Blend::Multiply);

    AppVie.Draw(SpriteVie1);
    AppVie.Draw(SpriteJaugeVie);

    sf::String sPointsDeVie =
    IFontMenus.AfficherTexte (IUtilsMenus.ConvertirFloatEnString (uiPointsDeVie), 38.f, 570.f);
    sPointsDeVie.SetSize(20.f);

    AppVie.Draw(sPointsDeVie);

    //AppVie.Draw(SpriteVie1);
    //AppVie.Draw(SpriteVie2);
    //AppVie.Draw(SpriteVie3);
}
