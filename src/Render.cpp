#include <iostream>

#include "Render.h"

CRender::CRender ()
{
    IRenderFont.ChargerFichierFont ("data/font/comic.ttf", 50);
    m_uiScore = 0;
}

CRender::~CRender ()
{

}
/*******************************************************************************
int InitialiserScene ()

Sorties possibles:
1 L'initialisation de la scéne s'est déroulée correctement.
-1 Le fichier de la font pour le menu n'a pas été trouvé.
-2 Le fichier xml décrivant les niveaux n'a pas été trouvé.
-3 Le chargement d'une ou plusieurs images n'a pu être fait.
-4 Le chargement d'un ou plusieurs fichiers sons n'a pu être fait.
*******************************************************************************/
int CRender::InitialiserScene ()
{
    if(IMenus.ChargerFontMenus())
    {
        IMenus.InitialiserAffichageMenu ();
    }
    else
    {
        return ERREUR_CHARGEMENT_FICHIER_FONT;
    }

    if (IEnnemis.InitArmmeEnnemie ())
    {
        m_uiNbTotalEnnemisRender = IEnnemis.m_uiNombreTotalEnnemis;
        m_uiNbEnnemisKORender = 0;
    }
    else
    {
        return ERREUR_INIT_ARMEE_ENNEMIE;
    }

    sf::Image ImageVaisseau1;
    sf::Image ImageVaisseau2;
    sf::Image ImageVaisseauBonus;
    sf::Image ImageEnnemi1;
    sf::Image ImageEnnemi1bis;
    sf::Image ImageEnnemi2;
    sf::Image ImageEnnemi2bis;
    sf::Image ImageEnnemi3;
    sf::Image ImageEnnemi3bis;
    sf::Image ImageArmeEnnemi;
    sf::Image ImageJaugeVie;
    sf::Image ImageContenuJaugeVie;

    //Background
    if (!IGestionSprite.ChargerFichierSprite ("data/images/espace.tga", ImageBackGround))
    return ERREUR_CHARGEMENT_IMAGES;

    //Vaisseau
    if (!IGestionSprite.ChargerFichierSprite ("data/images/vaisseau1.tga", ImageVaisseau1))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite ("data/images/vaisseau2.tga", ImageVaisseau2))
    return ERREUR_CHARGEMENT_IMAGES;

    //Particules
    if (!IGestionSprite.ChargerFichierSprite ("data/images/particule.tga", ImageParticule))
    return ERREUR_CHARGEMENT_IMAGES;

    //Vaisseau bonus
    if (!IGestionSprite.ChargerFichierSprite ("data/images/vaisseaubonus.tga", ImageVaisseauBonus))
    return ERREUR_CHARGEMENT_IMAGES;

    //Images des ennemies
    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi1, ImageEnnemi1))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi1bis, ImageEnnemi1bis))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi2, ImageEnnemi2))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi2bis, ImageEnnemi2bis))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi3, ImageEnnemi3))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite (IEnnemis.sTextureEnnemi3bis, ImageEnnemi3bis))
    return ERREUR_CHARGEMENT_IMAGES;

    //Images des armes ennemies
    if (!IGestionSprite.ChargerFichierSprite ("data/images/Arme1.tga", ImageArmeEnnemi))
    return ERREUR_CHARGEMENT_IMAGES;

    //Image de la jauge de vie
    if (!IGestionSprite.ChargerFichierSprite ("data/images/jauge3.tga", ImageJaugeVie))
    return ERREUR_CHARGEMENT_IMAGES;

    if (!IGestionSprite.ChargerFichierSprite ("data/images/vie2.tga", ImageContenuJaugeVie))
    return ERREUR_CHARGEMENT_IMAGES;

    //Background
    SpriteBackGround.SetImage(ImageBackGround);

    std::vector <sf::Image> ImagesEnnemis;
    ImagesEnnemis.clear ();

    ImagesEnnemis.push_back(ImageEnnemi1);
    ImagesEnnemis.push_back(ImageEnnemi1bis);
    ImagesEnnemis.push_back(ImageEnnemi2);
    ImagesEnnemis.push_back(ImageEnnemi2bis);
    ImagesEnnemis.push_back(ImageEnnemi3);
    ImagesEnnemis.push_back(ImageEnnemi3bis);

    std::vector <sf::Image> ImagesArmeEnnemis;
    ImagesArmeEnnemis.clear ();

    ImagesArmeEnnemis.push_back(ImageArmeEnnemi);

    std::vector <sf::SoundBuffer> SonsArmeEnnemis;
    SonsArmeEnnemis.clear ();

    sf::SoundBuffer BufferSonEnnemiKO;

    if(!IRenderSons.ChargerSon ("data/sounds/61648__Syna_Max__alien_scream.wav", BufferSonEnnemiKO))
    return ERREUR_CHARGEMENT_SONS;

    IEnnemis.InitSonsArmeeEnnemis (BufferSonEnnemiKO);

    sf::SoundBuffer BufferTirNouvelleRocket;

    if(!IRenderSons.ChargerSon ("data/sounds/30935__aust_paul__possiblelazer.wav", BufferTirNouvelleRocket))
    return ERREUR_CHARGEMENT_SONS;

    IRocket.InitialiserSonsRocket(BufferTirNouvelleRocket);

    //Initialisation Vaisseau
    IVaisseau.InitialiserVaisseau (ImageVaisseau1,ImageVaisseau2);

    //Initialisation Vaisseau bonus
    IVaisseauBonus.InitialiserVaisseauBonus(ImageVaisseauBonus);

    //Initialisation Images Armee Ennemie
    IEnnemis.InitImageArmeeEnnemis (ImagesEnnemis, ImagesArmeEnnemis);

    IEnnemis.AppliquerImageSurSpritesEnnemis();

    //Particules pour les différentes entités.
    //Vaisseau
    IVaisseau.pParticulesVaisseau.InitialiserImageParticule (ImageParticule);
    //Rocket
    IRocket.InitialiserRocket ();
    IRocket.TempParametrageRocket.pRocketsParticules.InitialiserImageParticule (ImageParticule);
    //Ennemis
    IEnnemis.TempParametrageTirEnnemi.ITirEnnemisParticules.InitialiserImageParticule (ImageParticule);

    IEnnemis.PositionVaisseauTerrien = IVaisseau.m_PositionVaisseau;

    //Images du menu
    std::vector <sf::Image> vImagesMenu;
    vImagesMenu.clear ();

    vImagesMenu.push_back(ImageJaugeVie);
    vImagesMenu.push_back(ImageContenuJaugeVie);

    IMenus.InitialiserImagesMenu (vImagesMenu);

    //Niveaux
    if (m_bJeuCommence)
    TimeAffichageNiveauEnCours.Reset ();

    m_bVieVaisseau = true;
    m_fDegatsVaisseau = 255.f;

    //m_uiPointsDeVieVaisseau = 6; //Pour debug

    return INITIALISATION_SCENE_OK;
}

void CRender::RenderScene(sf::RenderWindow &AppRender)
{
    if (m_bJeuCommence == false)
    {
        m_bJeuCommence = IMenus.AfficherFontMenus (AppRender);
        IEnnemis.m_uiNiveauxEnCours = 0;
        IEnnemis.m_bNiveauUpdate = false;

        if (m_bJeuCommence)
        {
            TimeAffichageNiveauEnCours.Reset ();
        }
    }

    else
    {
        //Niveaux
        if (TimeAffichageNiveauEnCours.GetElapsedTime () <= 1.f)
        {
            IMenus.AfficherNiveaux (AppRender, m_uiNiveauxEnCours);
        }

        else
        {
            AppRender.Draw(SpriteBackGround);

            if (!IRocket.ParametrageRocket.empty ())
            {
                RenderCollisions();
            }

            IEnnemis.PositionVaisseauTerrien = IVaisseau.m_PositionVaisseau;
            IEnnemis.TailleVaisseauTerrien = IVaisseau.m_TailleVaisseau;

          if(m_fDegatsVaisseau > 0.f)
           {
                bool bResLancerTirEnnemis = IEnnemis.LancerTirEnnemis(AppRender);

                if (bResLancerTirEnnemis && m_bVieVaisseau && m_uiPointsDeVieVaisseau != 0)
                {
                    m_fDegatsVaisseau -= 51.f;
                    m_uiPointsDeVieVaisseau--;
                    m_bVieVaisseau = false;
                    //std::cout <<"1 - " <<m_fDegatsVaisseau <<std::endl;
                }

                if (m_uiPointsDeVieVaisseau == 0)
                {
                    //std::cout<<"init explosition" <<std::endl;
                    IVaisseau.InitialiserExplosionVaisseau ();
                    IVaisseau.m_TimerEplosionVaisseau.Reset ();
                    IVaisseau.ExplosionVaisseau ();
                }


                else if (!bResLancerTirEnnemis && !m_bVieVaisseau)
                {
                    m_bVieVaisseau = true;
                    //std::cout <<"2 - " <<m_fDegatsVaisseau <<std::endl;
                }
           }

           IMenus.AfficherVie (AppRender, m_fDegatsVaisseau, m_uiPointsDeVieVaisseau);

           IMenus.AfficherScore (AppRender, m_uiScore);

           IEnnemis.AnimerArmeeEnnemie (AppRender);

           if (m_fDegatsVaisseau > 0.f)
           {

                IVaisseau.AfficherVaisseau (AppRender);
                IRocket.DessinerRocket (AppRender, IVaisseau.m_PositionVaisseau);
                IEnnemis.GererDeplacementsArmee();
           }

           else
           {
                if(!m_bVieVaisseau)
                {
                    //std::cout<<"init" <<std::endl;
                    IVaisseau.InitialiserExplosionVaisseau ();
                    IVaisseau.m_TimerEplosionVaisseau.Reset ();
                    m_bVieVaisseau = true;
                }

                if (IVaisseau.m_TimerEplosionVaisseau.GetElapsedTime () < 1.f)
                {
                    //std::cout<<"exploooooooooooooooooooooooo" <<std::endl;
                    IVaisseau.ExplosionVaisseau ();
                }
           }

            IVaisseauBonus.AfficherVaisseauBonus (AppRender);
        }
    }
}

void CRender::GetElapsedTime (float fElapsedTime)
{
    m_fElapsedTimeRender = fElapsedTime;
    IVaisseau.m_fElapsedTimeVaisseau = fElapsedTime;
    IRocket.m_fElapsedTimeRocket = fElapsedTime;
    IVaisseau.pParticulesVaisseau.m_fElapsedTimeParticule = fElapsedTime;
    IRocket.TempParametrageRocket.pRocketsParticules.m_fElapsedTimeParticule = fElapsedTime;
    IEnnemis.m_fElapsedTimeEnnemis = fElapsedTime;
    IVaisseauBonus.m_fElapsedTimeVaisseauBonus = fElapsedTime;

}

void CRender::RenderCollisions()
{
    sf::Vector2f PositionVaisseauBonus = IVaisseauBonus.GetPositionVaisseauBonus ();

    for (
            IRocket.it_ParametrageRocket = IRocket.ParametrageRocket.begin();
            IRocket.it_ParametrageRocket != IRocket.ParametrageRocket.end();
            ++IRocket.it_ParametrageRocket
        )
        {
            if (
                (*IRocket.it_ParametrageRocket).rocketExplosee == false
                && (*IRocket.it_ParametrageRocket).rocketOut == false
               )
            {
                if ((*IRocket.it_ParametrageRocket).bSonNouvelleRocketJoue == false)
                {
                    (*IRocket.it_ParametrageRocket).SonNouveauTir.SetVolume(20);
                    (*IRocket.it_ParametrageRocket).SonNouveauTir.Play ();
                    (*IRocket.it_ParametrageRocket).bSonNouvelleRocketJoue = true;
                }

                (*IRocket.it_ParametrageRocket).pRocketsParticules.ParticuleQuad
                (sf::Vector2f (((*IRocket.it_ParametrageRocket).rocketTranslationX),
                (*IRocket.it_ParametrageRocket).rocketTranslationY));

               (*IRocket.it_ParametrageRocket).rocketTranslationY += (IRocket.m_fVistesseRocket * IRocket.m_fElapsedTimeRocket);

                sf::Vector2f PositionRocket =
                sf::Vector2f ((*IRocket.it_ParametrageRocket).rocketTranslationX,
                (*IRocket.it_ParametrageRocket).rocketTranslationY);

                if(!IEnnemis.ParametrageTirEnnemi.empty ())
                {
                    //DetecterCollisionRocketTirEnnemi
                    for (
                            IEnnemis.it_ParametrageTirEnnemi = IEnnemis.ParametrageTirEnnemi.begin();
                            IEnnemis.it_ParametrageTirEnnemi != IEnnemis.ParametrageTirEnnemi.end();
                            ++IEnnemis.it_ParametrageTirEnnemi)
                        {

                        if ((*IEnnemis.it_ParametrageTirEnnemi).ExplosionTir == false)
                        {
                            sf::Vector2f PositionTirEnnemi =
                            sf::Vector2f  ((*IEnnemis.it_ParametrageTirEnnemi).PositionTirEnnemiX,
                            (*IEnnemis.it_ParametrageTirEnnemi).PositionTirEnnemiY);

                            (*IEnnemis.it_ParametrageTirEnnemi).TirEnnemiExplose =
                            ICollisions.DetecterCollisionRocketTirEnnemi(PositionRocket, PositionTirEnnemi, IEnnemis.m_TailleTirEnnemi);

                            if((*IEnnemis.it_ParametrageTirEnnemi).TirEnnemiExplose == true)
                            {
                                (*IRocket.it_ParametrageRocket).rocketExplosee = true;
                                (*IEnnemis.it_ParametrageTirEnnemi).ExplosionTir = true;

                                (*IEnnemis.it_ParametrageTirEnnemi).
                                ITirEnnemisParticules.InitExplosion(16.0f, PositionTirEnnemi + sf::Vector2f (IEnnemis.m_TailleEnnemi.x/2, IEnnemis.m_TailleEnnemi.y/2),
                                20, 1.0f, sf::Color (255, 128, 51), m_fElapsedTimeRender);

                            (*IEnnemis.it_ParametrageTirEnnemi).TimerExplosionTirEnnemi.Reset();
                            }
                        }
                    }
                }

                //DectecterCollisionTirVaisseauEnnemi
                for (unsigned int uiEnnemis = 0; uiEnnemis < IEnnemis.m_uiNombreTotalEnnemis; uiEnnemis++)
                {
                    sf::Vector2f PositionEnnemi = IEnnemis.ParametrageEnnemi[uiEnnemis].PositionEnnemi + IEnnemis.PositionArmee;

                    if (IEnnemis.ParametrageEnnemiCadrage[uiEnnemis].EnnemiDetruit == false)
                    {
                        IEnnemis.ParametrageEnnemiCadrage[uiEnnemis].EnnemiDetruit =
                        ICollisions.DectecterCollisionTirVaisseauEnnemi(PositionRocket, PositionEnnemi, IEnnemis.m_TailleEnnemi);

                        if(IEnnemis.ParametrageEnnemiCadrage[uiEnnemis].EnnemiDetruit == true
                           && IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].ExplosionEnnemi == false)
                        {
                            m_uiScore += IEnnemis.ParametrageEnnemiProprietes[uiEnnemis].uiPoints;

                           (*IRocket.it_ParametrageRocket).rocketExplosee = true;

                            if (IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].pExplosionEnnemis == 0)
                            {
                                IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].pExplosionEnnemis = new CExplosion ();

                                IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].pExplosionEnnemis->pParticulesExplosion->InitialiserImageParticule (ImageParticule);

                                IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].pExplosionEnnemis
                                ->pParticulesExplosion->InitExplosion(IEnnemis.m_TailleEnnemi.x, PositionEnnemi, 20, 1.0f, sf::Color (255, 255, 0), m_fElapsedTimeRender);

                                //std::cout<<"3 - " << m_fElapsedTimeRender <<std::endl;

                                IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].TimerEplosionEnnemis.Reset();
                            }
                        }

                        else if(IEnnemis.ParametrageEnnemiCadrage[uiEnnemis].EnnemiDetruit == true
                           && IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].ExplosionEnnemi == true)
                        {
                            delete IEnnemis.ParametrageEnnemiExplosion[uiEnnemis].pExplosionEnnemis;
                        }
                    }
                }

                if ((*IRocket.it_ParametrageRocket).rocketTranslationY < 0.0)
                {
                    (*IRocket.it_ParametrageRocket).rocketOut = true;
                    IRocket.it_ParametrageRocket = IRocket.ParametrageRocket.erase(IRocket.it_ParametrageRocket);
                }

                if (IVaisseauBonus.bVaisseauBonusKO == false)
                {
                    IVaisseauBonus.bVaisseauBonusKO =
                    ICollisions.DectecterCollisionTirVaisseauEnnemi
                    (PositionRocket, PositionVaisseauBonus, IVaisseauBonus.m_TailleVaisseauBonus);

                    if (
                        IVaisseauBonus.bVaisseauBonusKO == true
                        && IVaisseauBonus.bVaisseauBonusExplose == false
                        )
                    {
                        m_uiScore += 30;
                        IVaisseauBonus.IExplosionVaisseauBonus.pParticulesExplosion->InitialiserImageParticule (ImageParticule);
                        IVaisseauBonus.IExplosionVaisseauBonus.pParticulesExplosion->InitExplosion(IVaisseauBonus.m_TailleVaisseauBonus.x/4, PositionVaisseauBonus + sf::Vector2f (IVaisseauBonus.m_TailleVaisseauBonus.x/2, IVaisseauBonus.m_TailleVaisseauBonus.y/2), 20, 1.0f, sf::Color (255, 128, 51), m_fElapsedTimeRender);
                        IVaisseauBonus.TimerExplosionVaisseauBonus.Reset ();
                        IVaisseauBonus.bVaisseauBonusExplose = true;
                    }
                }
            }

            else if ((*IRocket.it_ParametrageRocket).rocketExplosee == true)
            {
                (*IRocket.it_ParametrageRocket).rocketOut = true;
                IRocket.it_ParametrageRocket = IRocket.ParametrageRocket.erase(IRocket.it_ParametrageRocket);
            }
        }

        m_uiNbEnnemisKORender = IEnnemis.m_uiNbEnnemisKO;
}
