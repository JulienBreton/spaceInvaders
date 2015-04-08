//Includes
#include "Rocket.h"
//#include "../MMGR/mmgr.h"
//==============================================================================
CRocket::CRocket()
{
    //Rocket
    m_fDepartRocket = 0.f;
    m_fVistesseRocket = -250.f;

    //Flamme
    m_fTailleParticuleRocket = 4.f;
    m_fEspaceYEntreParticulesRockets = 0.f;
    m_fTempsReinitParticulesRockets = 0.005f;
    m_fDureeVieParticulesRockets = 0.5f;
    m_fVitesseParticulesEnY = 0.f;
    m_iNbParticulesRocket = 50;

    espace_appuye = false;
    espace_gere = false;
    RocketTempsInitParticules  = m_fTempsReinitParticulesRockets;
    TpsCadenceTirsJoueur.Reset ();
}
//==============================================================================
CRocket::~CRocket()
{

}
//==============================================================================
void CRocket::InitialiserRocket ()
{
    ParametrageRocket.clear ();
}
//==============================================================================
void CRocket::DessinerRocket(sf::RenderWindow& AppRocket, sf::Vector2f PositionDuVaisseau)
{
    if (
        (
         (AppRocket.GetInput().IsKeyDown(sf::Key::Space))
         || (AppRocket.GetInput().IsJoystickButtonDown (0, 1))
        )
        && TpsCadenceTirsJoueur.GetElapsedTime () > 0.5f
       )


    {
        TpsCadenceTirsJoueur.Reset ();
        espace_appuye = true;
        CreerNouvelleRocket(PositionDuVaisseau);
    }

    else
    {
        espace_appuye = false;
        espace_gere = false;
    }
}
//==============================================================================
void CRocket::CreerNouvelleRocket(sf::Vector2f PositionVaisseau)
{
	if((espace_appuye) && (!espace_gere))
   	{
	   espace_gere = true;

       TempParametrageRocket.rocketTranslationX = PositionVaisseau.x;
       TempParametrageRocket.rocketTranslationY = PositionVaisseau.y;

       TempParametrageRocket.rocketExplosee = false;
       TempParametrageRocket.rocketOut = false;

       TempParametrageRocket.pRocketsParticules.InitialiserGenerateurParticules
       (
        m_fTailleParticuleRocket,
        m_iNbParticulesRocket,
        sf::Vector2f (0.0, 0.0),
        m_fVitesseParticulesEnY  * m_fElapsedTimeRocket,
        m_fEspaceYEntreParticulesRockets,
        sf::Color(255, 255, 0),
        RocketTempsInitParticules,
        m_fDureeVieParticulesRockets,
        0.f
        );

        TempParametrageRocket.SonNouveauTir.SetBuffer(m_BufferNouvelleRocket);
        TempParametrageRocket.bSonNouvelleRocketJoue = false;

        ParametrageRocket.push_back(TempParametrageRocket);
    }
}
//==============================================================================
void CRocket::EstDansEcran (float fRayon, std::list <ParametresRocket>::iterator it)
{
	if ((*it).rocketTranslationY < 0.0 - fRayon)
    {
            (*it).rocketOut = true;
            it = ParametrageRocket.erase(it);
    }
}
//==============================================================================
void CRocket::InitialiserSonsRocket (sf::SoundBuffer& BufferTirRocket)
{
    m_BufferNouvelleRocket = BufferTirRocket;
}
//==============================================================================



















