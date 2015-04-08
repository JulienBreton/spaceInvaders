#include "Particules.h"
//#include "mmgr.h"

//==============================================================================
CParticules::CParticules ()
{
    Timer.Reset ();
    bFirstTour = true;
    Acceleration = sf::Vector2f(0.f, 0.f);;
    PositionVaisseau = sf::Vector2f(0.f, 0.f);;
    m_nbParticules = 0;
    m_espaceYEntreParticules = 0.f;
    m_tempsInitParticules = 0.f;
    m_dureeVieParticules = 0.f;
    m_departParticulesY = 0.f;
    m_fPositionYGenerateur = 0.f;
    m_fVitesseParticuleEnY = 0.f;
    m_ftailleParticules = 0.f;
    m_fElapsedTimeParticule = 0.f;
    m_VitesseF = sf::Vector2f(0.f, 0.f);
    m_Position = sf::Vector2f(0.f, 0.f);
    m_VitesseGenerateur = sf::Vector2f(0, 0);
    m_Couleur = sf::Color(0, 0, 0);
}
//==============================================================================
CParticules::~CParticules()
{

}

void CParticules::InitialiserImageParticule (sf::Image ImageDesParticules)
{
    ImageParticule = ImageDesParticules;
}

//==============================================================================
void CParticules::InitialiserGenerateurParticules(
                                                  float tailleParticules,
                                                  int nbParticules,
                                                  sf::Vector2f fVitesseGenerateur,
                                                  float fVitesseParticuleEnY,
                                                  float espaceParticulesY,
                                                  sf::Color couleurParticules,
                                                  float tempsInitParticules,
                                                  float dureeVieParticules,
                                                  float departParticulesY
                                                  )
{
    m_ftailleParticules = tailleParticules;
    m_nbParticules = nbParticules;
    m_VitesseGenerateur = fVitesseGenerateur;
    m_fVitesseParticuleEnY = fVitesseParticuleEnY;
    m_espaceYEntreParticules = espaceParticulesY;
    m_Couleur = couleurParticules;
    m_tempsInitParticules = tempsInitParticules;
    m_dureeVieParticules = dureeVieParticules;
    m_departParticulesY = departParticulesY;
    Acceleration = sf::Vector2f (0.0, 0.0);
}
//==============================================================================
void CParticules::InitialiserParticule(int iIndexParticules, sf::Vector2f PositionVaisseau)
{
    //Temps de création entre 2 particules
    if (Timer.GetElapsedTime () > m_tempsInitParticules)
    {
        Timer.Reset ();

        ParametrageParticules[iIndexParticules].Temps.Reset ();

        PositionVaisseau += sf::Vector2f (0, m_departParticulesY);

        ParametrageParticules[iIndexParticules].PositionParticule = PositionVaisseau;

        float fTempsVie = m_dureeVieParticules;

        ParametrageParticules[iIndexParticules].fTempsVieParicule = fTempsVie > 0.0f ? fTempsVie : 1.0f;

        ParametrageParticules[iIndexParticules].fTransparenceParticule = 1.0f;
    }

    else
    {
        ParametrageParticules[iIndexParticules].PositionParticule = sf::Vector2f(-800, -600);
    }
}
//==============================================================================
sf::Vector2f CParticules::GetPosition (int iIndexParticules)
{
    float fTemps = ParametrageParticules[iIndexParticules].Temps.GetElapsedTime ();

    ParametrageParticules[iIndexParticules].VitesseParticule =
    sf::Vector2f (0.0, m_fVitesseParticuleEnY)*fTemps;

    //m_VitesseF =
    //ParametrageParticules[iIndexParticules].VitesseParticule;

    return  ParametrageParticules[iIndexParticules].VitesseParticule/* * fTemps*/ +
    ParametrageParticules[iIndexParticules].PositionParticule;

    /*
    m_VitesseF = Acceleration * fTemps +
    ParametrageParticules[iIndexParticules].VitesseParticule;

    return Acceleration * 0.5f * fTemps * fTemps + m_VitesseF * fTemps +
    ParametrageParticules[iIndexParticules].PositionParticule + sf::Vector2f (0.0, 0.0);
    */
}
//==============================================================================
// Pour affiner les effets de particules, plus le temps de vie d'une particule
//avance plus elle devient transparente, c'est à dire de moins en moins visible.
float CParticules::GetTransparence (int iIndexParticules) const
{
    return  0.5 + ParametrageParticules[iIndexParticules].fTransparenceParticule
     / 2 - ((ParametrageParticules[iIndexParticules].Temps.GetElapsedTime () /
     ParametrageParticules[iIndexParticules].fTempsVieParicule));
}
//==============================================================================
bool CParticules::GetFinVie (int iIndexParticules) const
{
    return ParametrageParticules[iIndexParticules].Temps.GetElapsedTime ()
    >= m_dureeVieParticules; //ParametrageParticules[iIndexParticules].fTempsVieParicule;
}
//==============================================================================
void CParticules::ParticuleQuad (sf::Vector2f PositionVaisseau)
{
    //Rien de commenté charge CPU max 24% (mais 20% la plus part du temps)

    //Ces 3 lignes ne génèrent pas de dégradations des performances.
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    ImageParticule.Bind ();
    glBegin(GL_QUADS);

    int iIndexParticules = 0;

    //for (int iIndexParticules = 0; iIndexParticules < m_nbParticules; iIndexParticules++)
    do
    {
        //tout commenté charge CPU max 2%

        //1
        //Tout commenté sauf ce if et son contenu alors charge CPU max 9%
        if (GetFinVie (iIndexParticules))
        {
            InitialiserParticule(iIndexParticules, PositionVaisseau);
            iIndexParticules++;
            continue;
        }

        else
        {

        //2
        //1+2 charge CPU max 12%
        m_Position = GetPosition (iIndexParticules);

        //3
        //1+2+3 charge CPU max 17%
        ParametrageParticules[iIndexParticules].fTransparenceParticule =
        GetTransparence (iIndexParticules);

        //4
        //1+2+3+4 charge CPU max 25%

            glColor4f (m_Couleur.r, m_Couleur.g, m_Couleur.b, ParametrageParticules[iIndexParticules].fTransparenceParticule);
            glTexCoord2f (0, 1); glVertex2f (m_Position.x - m_ftailleParticules, m_Position.y - m_ftailleParticules);
            glTexCoord2f (1, 1); glVertex2f (m_Position.x + m_ftailleParticules, m_Position.y - m_ftailleParticules);
            glTexCoord2f (1, 0); glVertex2f (m_Position.x + m_ftailleParticules, m_Position.y + m_ftailleParticules);
            glTexCoord2f (0, 0); glVertex2f (m_Position.x - m_ftailleParticules, m_Position.y + m_ftailleParticules);

            iIndexParticules++;
        }
    }
    while (iIndexParticules < m_nbParticules);

    glEnd();
    glDisable (GL_BLEND);
}
//==============================================================================
void CParticules::InitExplosion (float fTailleParticule, const sf::Vector2f & Position,
                    unsigned int uiForce, float fDureeVie, sf::Color Couleur, float fElapsedTime)
{
    //Init de l'effet d'explosion
    m_fTailleParticule_Explosion = fTailleParticule;
    m_Position_Explosion = Position;
    m_fDureeVie_Explosion = fDureeVie;
    m_uiForce = uiForce;
    m_Couleur_Explosion = Couleur;

    m_DureeVie_Explosion.Reset ();

    //int test = 0;

    for (unsigned int uiNb_particules = 0; uiNb_particules < 50; uiNb_particules++)
	{
	    //for (unsigned int i = 0; i < m_uiForce; i++)
	   //{
            float fRandAngle = IUtilsParticules.RandFloat (-M_PI, M_PI);
            float fRandCos = cos (fRandAngle);
            float fRandSin = sin (fRandAngle);
            //float fRandForce = RandFloat (0.0f, (float)m_uiForce/1500);
            float fRandForce = IUtilsParticules.RandFloat (0.0f, 2500/*(float)m_uiForce*/);
            //fRandForce *= m_fElapsedTimeParticule;

            sf::Vector2f Vitesse = sf::Vector2f (fRandCos * fRandForce, fRandSin * fRandForce);
            //std::cout <<"fRandCos "<<fRandCos <<std::endl;
            //std::cout <<"fRandSin "<<fRandSin <<std::endl;

            ParametrageParticules[uiNb_particules].PositionParticule = m_Position_Explosion;
            ParametrageParticules[uiNb_particules].VitesseParticule = sf::Vector2f(Vitesse.x*fElapsedTime, Vitesse.y*fElapsedTime);
            //std::cout <<"VitesseX "<<Vitesse.x <<std::endl;
            //std::cout <<"VitesseY "<<Vitesse.y <<std::endl;
            ParametrageParticules[uiNb_particules].fTempsVieParicule = m_fDureeVie_Explosion > 0.0f ? m_fDureeVie_Explosion : 1.0f;
            ParametrageParticules[uiNb_particules].fTransparenceParticule = 1.0f;
            //Plus le nombre diviseur est petit plus les particules partent loin
            ParametrageParticules[uiNb_particules].AccelerationParticule.x = 0.f;
            ParametrageParticules[uiNb_particules].AccelerationParticule.y = 0.f;//((-Vitesse.y) / 1.5)*fElapsedTime;//( * fElapsedTime);//(250.f * fElapsedTime);

            //if (test < 10)
            //{
            //std::cout <<"Acceleration "<<ParametrageParticules[34].AccelerationParticule.y <<std::endl;
            //std::cout <<"fElapsedTime "<<fElapsedTime <<std::endl;
            //}

            //test += 1;

            ParametrageParticules[uiNb_particules].Temps.Reset ();
	   //}
    }
}
//==============================================================================
void CParticules::CreerExplosion ()
{
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);

    ImageParticule.Bind ();

    glBegin(GL_QUADS);

    if (m_DureeVie_Explosion.GetElapsedTime () < m_fDureeVie_Explosion)
    {
        for (unsigned int uiNb_particules = 0; uiNb_particules < 50; uiNb_particules++)
	   {
       	    float fTemps = ParametrageParticules[uiNb_particules].Temps.GetElapsedTime ();

            sf::Vector2f m_VitesseF = ParametrageParticules[uiNb_particules].AccelerationParticule *
            fTemps + ParametrageParticules[uiNb_particules].VitesseParticule;

	        m_Position_Explosion = ParametrageParticules[uiNb_particules].PositionParticule =
            ParametrageParticules[uiNb_particules].AccelerationParticule * 0.5f * fTemps * fTemps
            + m_VitesseF * fTemps + ParametrageParticules[uiNb_particules].PositionParticule;

            ParametrageParticules[uiNb_particules].fTransparenceParticule =
            0.5f + ParametrageParticules[uiNb_particules].fTransparenceParticule
            / 12 - ParametrageParticules[uiNb_particules].Temps.GetElapsedTime () /
            m_fDureeVie_Explosion;

            glColor4f (255, 255, 0,
            ParametrageParticules[uiNb_particules].fTransparenceParticule);

            glTexCoord2f (0, 0);
            glVertex2f (m_Position_Explosion.x - m_fTailleParticule_Explosion, m_Position_Explosion.y - m_fTailleParticule_Explosion);

            glTexCoord2f (1, 0);
            glVertex2f (m_Position_Explosion.x + m_fTailleParticule_Explosion, m_Position_Explosion.y - m_fTailleParticule_Explosion);

            glTexCoord2f (1, 1);
            glVertex2f (m_Position_Explosion.x + m_fTailleParticule_Explosion, m_Position_Explosion.y + m_fTailleParticule_Explosion);

            glTexCoord2f (0, 1);
            glVertex2f (m_Position_Explosion.x - m_fTailleParticule_Explosion, m_Position_Explosion.y + m_fTailleParticule_Explosion);
        }
    }

    glEnd();
    glDisable (GL_BLEND);
}
//==============================================================================

