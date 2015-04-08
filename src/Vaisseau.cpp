#include "Vaisseau.h"

CVaisseau::CVaisseau ()
{

}

CVaisseau::~CVaisseau ()
{

}

void CVaisseau::InitialiserVaisseau (sf::Image& ImageDuVaisseau1, sf::Image& ImageDuVaisseau2)
{
    //Vaisseau
    float fTailleVaisseauX = 111.6;
    float fTailleVaisseauY = 65.6;
    m_fPositionVaisseauXDepart = 400.0f;
    m_fPositionVaisseauYDepart = 500.0f;

    //Flammes
    float fTailleParticulesVaisseau = 12.f;
    float fEspaceYEntreParticulesVaisseau = 0.f;
    float fTempsReinitParticulesVaisseau = 0.03f;
    float fDureeVieParticulesVaisseau = 0.8f;
    //float fDepartYParticulesVaisseau = 0.f;
    float fVitesseParticulesReacteurEnY = 70.f;
    int iNBParticulesVaisseau = 50;

    ImageVaisseau1 = ImageDuVaisseau1;
    ImageVaisseau2 = ImageDuVaisseau2;
    SpriteVaisseau.SetImage(ImageVaisseau1);
    SpriteVaisseau.SetPosition(m_fPositionVaisseauXDepart, m_fPositionVaisseauYDepart);
    SpriteVaisseau.Resize(fTailleVaisseauX, fTailleVaisseauY);

    //sf::IntRect PositionParticules = SpriteVaisseau.GetSubRect ();

    m_bvaisseauToucheParEnnemis = false;

    sf::Vector2f toto= SpriteVaisseau.GetCenter ();// PositionParticules.Left;

    float fDepartYParticules = toto.y;

    //Position Vaisseau
    m_TailleVaisseau = GetTailleVaisseau ();
    m_PositionVaisseau = GetPositionVaisseau ();

    pParticulesVaisseau.InitialiserGenerateurParticules
                                                        (
                                                         fTailleParticulesVaisseau,
                                                         iNBParticulesVaisseau,
                                                         sf::Vector2f (0.0, 0.0),
                                                         fVitesseParticulesReacteurEnY,
                                                         fEspaceYEntreParticulesVaisseau,
                                                         sf::Color (18, 112, 253),
                                                         fTempsReinitParticulesVaisseau,
                                                         fDureeVieParticulesVaisseau,
                                                         fDepartYParticules
                                                         );

    m_PositionFlamme = PositionnerFlamme ();

    SpriteVaisseau.SetImage(ImageVaisseau1);
}

void CVaisseau::AfficherVaisseau (sf::RenderWindow& AppVaisseau)
{
    float fVitesseVaisseau = 350.f;

    if (
        AppVaisseau.GetInput().IsKeyDown(sf::Key::Left)
        ||(AppVaisseau.GetInput().GetJoystickAxis(0, sf::Joy::AxisX) < 0)
       )
        {
            m_PositionVaisseau = GetPositionVaisseau ();

            if (m_PositionVaisseau.x <= (0.f + m_TailleVaisseau.x/2))
            {
                SpriteVaisseau.SetPosition(0.f, m_fPositionVaisseauYDepart);
            }

            else
            {
                SpriteVaisseau.Move(-fVitesseVaisseau * m_fElapsedTimeVaisseau, 0);
            }

            m_PositionVaisseau = GetPositionVaisseau ();
            m_PositionFlamme = PositionnerFlamme ();
        }

    else if (
            AppVaisseau.GetInput().IsKeyDown(sf::Key::Right)
            ||(AppVaisseau.GetInput().GetJoystickAxis(0, sf::Joy::AxisX) > 0)
            )
            {
                m_PositionVaisseau = GetPositionVaisseau ();

                if (m_PositionVaisseau.x >= (LARGEUR_FENETRE - m_TailleVaisseau.x/2))
                {
                    SpriteVaisseau.SetPosition (LARGEUR_FENETRE - m_TailleVaisseau.x, m_fPositionVaisseauYDepart);
                }

                else
                {
                    SpriteVaisseau.Move(fVitesseVaisseau * m_fElapsedTimeVaisseau, 0);
                    //std::cout<<"1 - " <<m_fElapsedTimeVaisseau <<std::endl;
                }

                m_PositionVaisseau = GetPositionVaisseau ();
                m_PositionFlamme = PositionnerFlamme ();
            }

    //std::cout <<"echo" <<std::endl;

    pParticulesVaisseau.ParticuleQuad (m_PositionFlamme);

    if (!m_bvaisseauToucheParEnnemis)
    AppVaisseau.Draw(SpriteVaisseau);
}

void CVaisseau::DeplacerVaisseau ()
{

}

sf::Vector2f CVaisseau::GetPositionVaisseau ()
{
    sf::Vector2f PositionVaisseau = SpriteVaisseau.GetPosition ();
    PositionVaisseau.x = PositionVaisseau.x + m_TailleVaisseau.x/2;
    PositionVaisseau.y = PositionVaisseau.y + m_TailleVaisseau.y/2;
    return PositionVaisseau;
}

sf::Vector2f CVaisseau::GetTailleVaisseau ()
{
    return SpriteVaisseau.GetSize ();
}

sf::Vector2f CVaisseau::PositionnerFlamme ()
{
    sf::Vector2f PositionFlamme = m_PositionVaisseau;
    PositionFlamme.x = m_PositionVaisseau.x - 4.0f;
    PositionFlamme.y = m_PositionVaisseau.y + m_TailleVaisseau.y/2;

    return PositionFlamme;
}

void CVaisseau::InitialiserExplosionVaisseau ()
{
    //std::cout<<"2 - " <<m_fElapsedTimeVaisseau <<std::endl;

    pParticulesVaisseau.InitExplosion(m_TailleVaisseau.x,
    m_PositionVaisseau, 20, 1.0f, sf::Color (255, 255, 0), m_fElapsedTimeVaisseau);
}

void CVaisseau::ExplosionVaisseau ()
{
    pParticulesVaisseau.CreerExplosion();
}


