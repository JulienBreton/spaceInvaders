#include "Fenetre_SFML.h"

CFenetreSFML::CFenetreSFML ()
{

}

CFenetreSFML::~CFenetreSFML ()
{

}

bool CFenetreSFML::CreerFenetreSFML
(unsigned int LargeurFenetre, unsigned int HauteurFenetre, unsigned int ProfondeursBitsParPixel, std::string Titre, bool PleinEcran)
{
    //Gestion des erreurs
    sf::String sFontMessageErreur = IGestionFont.AfficherTexte (" ", 0.f, 0.f);
    bool bErreur = false;

    //Process events
    sf::Event Event;

    //Affichage de la scene
    sf::View ViewScene;

    //Chargement de la Font
    if (!IGestionFont.ChargerFichierFont ("data/font/comic.ttf", 60))
    {
        return EXIT_FAILURE;
    }

    //Création de la fenêtre
    if (PleinEcran == false)
    {
        App.Create(sf::VideoMode(LargeurFenetre, HauteurFenetre, ProfondeursBitsParPixel), Titre);
        ViewScene = App.GetDefaultView();
    }

    if (PleinEcran == true)
    {
        sf::VideoMode Mode = sf::VideoMode::GetDesktopMode();

        if (!Mode.IsValid())
        {
            return EXIT_FAILURE;
        }

        App.Create(Mode, Titre, sf::Style::Fullscreen);

        sf::Vector2f CenterFullScreen(LargeurFenetre/2, HauteurFenetre/2);
        sf::Vector2f HalfSizeFullScreen(LargeurFenetre/2, HauteurFenetre/2);
        sf::View ViewFullScreen(CenterFullScreen, HalfSizeFullScreen);
        ViewScene = ViewFullScreen;
        //ViewScene = App.GetDefaultView();
    }

    //Limite à 60 images par seconde
    App.SetFramerateLimit(60);
    //Cache le curseur de la sourie
    App.ShowMouseCursor(false);

    sf::Clock TimerJeu;
    TimerJeu.Reset ();
    float fFramerate = 0.f;
    float fFramerateMin = 0.f;
    float fFramerateTemp = 0.f;
    float fTimerJeu = 0.f;

    sf::Clock TimerLiberationProcesseur;
    TimerLiberationProcesseur.Reset ();
    float fTimerLiberationProcesseur;

    int iVerifInitArmeeEnnemie = IRender.InitialiserScene ();

    if(iVerifInitArmeeEnnemie == ERREUR_CHARGEMENT_FICHIER_FONT)
    {
        sFontMessageErreur =
        IGestionFont.AfficherTexte
        ("-Le fichier comic.ttf pour le menu n'a pas ete trouve.", 5.f, 50.f);
        sFontMessageErreur.SetSize(10.f);
        bErreur = true;
    }

    if(iVerifInitArmeeEnnemie == ERREUR_INIT_ARMEE_ENNEMIE)
    {
        sFontMessageErreur =
        IGestionFont.AfficherTexte
        ("-Le fichier xml (niveau.xml/niveau.dtd) decrivant les niveaux n'a pas ete trouve ou n'est pas correct.", 5.f, 50.f);
        sFontMessageErreur.SetSize(10.f);
        bErreur = true;
    }

    if(iVerifInitArmeeEnnemie == ERREUR_CHARGEMENT_IMAGES)
    {
        sFontMessageErreur =
        IGestionFont.AfficherTexte
        ("-Erreur lors du chargement d'une ou plusieurs images", 5.f, 50.f);
        sFontMessageErreur.SetSize(10.f);
        bErreur = true;
    }

    if(iVerifInitArmeeEnnemie == ERREUR_CHARGEMENT_SONS)
    {
        sFontMessageErreur =
        IGestionFont.AfficherTexte
        ("-Erreur lors du chargement d'un ou plusieurs fichiers sons", 5.f, 50.f);
        sFontMessageErreur.SetSize(10.f);
        bErreur = true;
    }

    IRender.m_uiNiveauxEnCours = 1;

    IRender.m_uiPointsDeVieVaisseau = 5;

    sf::SoundBuffer MyBuffer;

    if (!MyBuffer.LoadFromFile("data/sounds/61648__Syna_Max__alien_scream.wav"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound MySound(MyBuffer);

    //IRender.IEnnemis.InitSonsArmeeEnnemis(MySound);

    //MySound.Play();

    //Boucle principale
    while (App.IsOpened())
    {

        if((1 / App.GetFrameTime()) > 60.f)
        {
            sf::Sleep(0.0005);
        }

        fTimerLiberationProcesseur = TimerLiberationProcesseur.GetElapsedTime ();

        if (fTimerJeu >= 1.f)
        {
            fFramerateTemp = 1.f / App.GetFrameTime();

            if (fFramerateMin > fFramerateTemp || fFramerateMin == 0)
            {
                fFramerateMin = fFramerateTemp;
                fFramerateMin = int (fFramerateMin);
            }

            fFramerate = 1.f / App.GetFrameTime();
            fFramerate = int (fFramerate);

            if (fTimerLiberationProcesseur > 20.f)
            {
                fFramerateMin = fFramerate;
                TimerLiberationProcesseur.Reset ();
            }

            TimerJeu.Reset ();
        }

        sf::String AffichageFPS = IGestionFont.AfficherTexte ("FPS: " + ICUtils.ConvertirFloatEnString (fFramerate), 5.f, 10.f);
        sf::String AffichageFPSMin = IGestionFont.AfficherTexte ("FPS Min (20s): " + ICUtils.ConvertirFloatEnString (fFramerateMin), 5.f, 20.f);

        //sf::String Debug = IGestionFont.AfficherTexte ("Niveaux: " + ICUtils.ConvertirFloatEnString (IRender.IEnnemis.m_uiNiveauxEnCours), 5.f, 40.f);

        float ElapsedTime = App.GetFrameTime();
        sf::String AffichageElapsedTime = IGestionFont.AfficherTexte (ICUtils.ConvertirFloatEnString (ElapsedTime), 5.f, 500.f);
        IRender.GetElapsedTime (ElapsedTime);

        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                {
                    App.Close();
                }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                {
                    App.Close();
                }

            if (Event.Type == sf::Event::Resized)
                {
                    sf::Vector2f CenterResize(Event.Size.Width/2, Event.Size.Height/2);
                    sf::Vector2f HalfSizeResize(Event.Size.Height, Event.Size.Height);
                    sf::View ViewResize (CenterResize, HalfSizeResize);
                    ViewScene = ViewResize;
                }

            //Screenshot
            if (Event.Key.Code == sf::Key::F1)
            {
                sf::Image Screen = App.Capture();
                Screen.SaveToFile("screenshot.jpg");
            }
        }

        App.SetView(ViewScene);

        App.Clear();

        if(bErreur)
        App.Draw(sFontMessageErreur);

        if (App.GetInput().IsKeyDown(sf::Key::Q))
        {
            IRender.InitialiserScene ();
            IRender.m_bJeuCommence = false;
            IRender.m_uiNiveauxEnCours = 1;
            IRender.m_uiScore = 0;
            IRender.m_uiPointsDeVieVaisseau = 5;
            //IRender.ISons.ChargerSon (MySound);
            //IRender.IEnnemis.PlaySonEnnemi (MySound);
        }

        if (IRender.m_uiNbEnnemisKORender == IRender.m_uiNbTotalEnnemisRender)
        {
            IRender.InitialiserScene ();
            IRender.m_uiNiveauxEnCours++;
        }


        if (iVerifInitArmeeEnnemie == INITIALISATION_SCENE_OK)
        {
            IRender.RenderScene (App);
        }

        App.Draw(AffichageFPS);
        App.Draw(AffichageFPSMin);

        //Affichage de la fenêtre à l'écran
        App.Display();

        fTimerJeu = TimerJeu.GetElapsedTime ();
    }

    return EXIT_SUCCESS;
}
