#include <iostream>

#include "Ennemis.h"
//=============================================================================
bool CEnnemis::InitArmmeEnnemie()
{
    bool bInitArmeeEnnemie = true;
    m_bNiveauUpdate = false;
    unsigned int uiLigneOuSeTrouveEnnemi = 0;

    StructureArmeeEnnemie.clear ();
    StructureEnnemi.clear ();
    DonnesXMLEnnemi.clear ();
    ParametrageEnnemi.clear ();
    ParametrageEnnemiExplosion.clear ();
    ParametrageEnnemiProprietes.clear ();
    ParametrageEnnemiCadrage.clear ();
    ParametrageTirEnnemi.clear ();
    m_vEnnemisPouvantTirer.clear ();
    m_vColonnesEnnemisAvantDetruites.clear ();
    ParametrageEnnemiSon.clear ();

    if (m_iRecupDonneesXML.OuvrirFichierXML ())
    {
        m_fVitesseArmee = 0.0f;
        PositionArmee.x = 0.0f;
        PositionArmee.y = 0.0f;
        recule = false;
        debutCourseX = DEBUT_COURSE_X;
        finCourseX = FIN_COURSE_X;
        m_uiNbEnnemisKO = 0;
        m_uiTempNbEnnemisKO = 0;
        m_uiNbEnnemisKOCadrage = 0;
        m_uiNbEnnemisKOTireur = 0;
        m_uiNbEnnemisTest = 0;
        m_uiNbColonnesKO = 0;
        TimeToChangeTextureEnnemi.Reset();
        m_bChangementTexture = true;
        m_bInitRandom = true;
        m_fElapsedTimeEnnemis = 0.f;
        m_uiNbTypesEnnemis = 0;

        //Tirs ennemis
        m_LancementTir.Reset ();
        m_bLancementTirPossible = true;

        //On récupére les données du fichier XML

        //Armee
        StructureArmeeEnnemie = m_iRecupDonneesXML.RecupStructureArmee ();

        for (unsigned int uiNbArmees = 0; uiNbArmees < StructureArmeeEnnemie.size (); uiNbArmees++)
        {
            if (m_uiNiveauxEnCours == uiNbArmees)
            {
                m_uiNombreTotalEnnemis = StructureArmeeEnnemie[uiNbArmees].uiNombreEnnemis;
                m_uiEspaceY_EntreEnnemis = StructureArmeeEnnemie[uiNbArmees].fEspaceY_EntreEnnemis;
                m_uiIndexArmee = StructureArmeeEnnemie[uiNbArmees].uiIndex;
                m_uiNbEnnemisParLignes = StructureArmeeEnnemie[uiNbArmees].uiEnnemisParLignes;
                m_uiNombreDeSautsEnnemis = StructureArmeeEnnemie[uiNbArmees].uiNombreDeSautsEnnemis;
                m_fVitesseArmee = StructureArmeeEnnemie[uiNbArmees].fVitesseArmeeY;
                m_fDepartArmeeX = StructureArmeeEnnemie[uiNbArmees].fDepartArmeeX;
                m_fDepartArmeeY = StructureArmeeEnnemie[uiNbArmees].fDebutCourseX;
                m_uiPosFinEnnemisType1 = StructureArmeeEnnemie[uiNbArmees].uiPosFinEnnemisType1;
                m_uiPosFinEnnemisType2 = StructureArmeeEnnemie[uiNbArmees].uiPosFinEnnemisType2;
                m_uiPosFinEnnemisType3 = StructureArmeeEnnemie[uiNbArmees].uiPosFinEnnemisType3;
                m_fAcceleration = StructureArmeeEnnemie[uiNbArmees].fAcceleration;
            }
        }

        //Ennemi
        StructureEnnemi = m_iRecupDonneesXML.RecupStructureEnnemi ();

        for (unsigned int uiNbTypesEnnemis = 0; uiNbTypesEnnemis < StructureEnnemi.size (); uiNbTypesEnnemis++)
        {
            TempDonnesXMLEnnemi.m_fTailleEnnemiX = StructureEnnemi[uiNbTypesEnnemis].fTailleEnnemiX;
            TempDonnesXMLEnnemi.m_fTailleEnnemiY = StructureEnnemi[uiNbTypesEnnemis].fTailleEnnemiY;
            TempDonnesXMLEnnemi.m_uiIndexEnnemi = StructureEnnemi[uiNbTypesEnnemis].uiIndex;
            TempDonnesXMLEnnemi.m_uiPoints = StructureEnnemi[uiNbTypesEnnemis].uiPoints;
            TempDonnesXMLEnnemi.m_sTexture1 = StructureEnnemi[uiNbTypesEnnemis].sTexture1;
            TempDonnesXMLEnnemi.m_sTexture2 = StructureEnnemi[uiNbTypesEnnemis].sTexture2;

            DonnesXMLEnnemi.push_back (TempDonnesXMLEnnemi);
            m_uiNbTypesEnnemis++;
        }

        //Tir
        //m_iPlageNombresAleatoires = m_uiNbEnnemisParLignes;
        m_iDebutPlageNombresAleatoires = 0; //m_uiNombreTotalEnnemis - m_uiNbEnnemisParLignes;
        m_iFinPlageNombresAleatoires = m_uiNombreTotalEnnemis - 1;

        m_uiPlage = (m_iFinPlageNombresAleatoires - m_iDebutPlageNombresAleatoires) + 1;

        //fCoeffTpsRenitTir = 0.5; //1.28f;
        m_fTpsRenitTir = .8f; //1.6f - fCoeffTpsRenitTir;
        //m_fTpsRenitTir = ((m_fTpsRenitTir * uiPlage) / m_uiNbEnnemisParLignes);

        int icranX = 0;
        m_uiCadrageX = 0;
        m_uiCadrageY = 0;

        if( m_uiNbEnnemisParLignes != 0)
        {
            m_uiNombreLignesEnnemis = m_uiNombreTotalEnnemis / m_uiNbEnnemisParLignes;
        }

        else
        {
            m_uiNombreLignesEnnemis = 0;
            bInitArmeeEnnemie = false;
        }

        m_iNbColonnesDebutOK = 0;
        m_iNbColonnesFinOK = m_uiNbEnnemisParLignes;

        ParametrageEnnemi.clear ();

        /*Le nombre d'ennemis doit être supérieur à 9*/
        for (unsigned int i = 0; i < m_uiNombreTotalEnnemis; i++)
        {
            unsigned int uiTypeEnnemi = 0;

            if (i > m_uiPosFinEnnemisType2)
            {
                uiTypeEnnemi = 0;
                sTextureEnnemi1 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi1bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[0];
                    TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[1];
                }
            }

            else if (i > m_uiPosFinEnnemisType1)
            {
                uiTypeEnnemi = 1;
                sTextureEnnemi2 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi2bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[2];
                    TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[3];
                }
            }

            else if (i < m_uiPosFinEnnemisType1)
            {
                uiTypeEnnemi = 2;
                sTextureEnnemi3 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi3bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[4];
                    TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[5];
                }
            }

            TempParametrageEnnemiProprietes.fTailleEnnemiX = DonnesXMLEnnemi[uiTypeEnnemi].m_fTailleEnnemiX;
            TempParametrageEnnemiProprietes.fTailleEnnemiY = DonnesXMLEnnemi[uiTypeEnnemi].m_fTailleEnnemiY;
            TempParametrageEnnemiProprietes.uiIndexEnnemi = DonnesXMLEnnemi[uiTypeEnnemi].m_uiIndexEnnemi;
            TempParametrageEnnemiProprietes.uiPoints = DonnesXMLEnnemi[uiTypeEnnemi].m_uiPoints;

            if (i == (m_uiNbEnnemisParLignes) || i == m_uiCadrageX + m_uiNbEnnemisParLignes)
            {
                icranX = 0;
                m_uiCadrageX = i;
            }

            TempParametrageEnnemi.PositionEnnemi.x = m_fDepartArmeeX + (ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*icranX ;

            if (i == 0)
            {
                TempParametrageEnnemi.PositionEnnemi.y = m_fDepartArmeeY;
                uiLigneOuSeTrouveEnnemi++;
            }

            else if (i == m_uiCadrageY + m_uiNbEnnemisParLignes)
            {
                TempParametrageEnnemi.PositionEnnemi.y =
                ParametrageEnnemi[i-m_uiNbEnnemisParLignes].PositionEnnemi.y + DonnesXMLEnnemi[0].m_fTailleEnnemiY + m_uiEspaceY_EntreEnnemis;
                m_uiCadrageY = i;
                //std::cout <<"m_uiCadrageY" <<m_uiCadrageY <<std::endl;
                uiLigneOuSeTrouveEnnemi++;
            }

            TempParametrageEnnemiCadrage.uiJeSuisDansLaLigne = uiLigneOuSeTrouveEnnemi;
            TempParametrageEnnemiCadrage.uiLePremierDeMaLigneEst = m_uiCadrageY;
            TempParametrageEnnemiCadrage.uiLeDernierDeMaLigneEst = m_uiCadrageY + m_uiNbEnnemisParLignes -1;

            //std::cout <<"TempParametrageEnnemiCadrage.uiLePremierDeMaLigneEst" <<TempParametrageEnnemiCadrage.uiLePremierDeMaLigneEst <<" - i:" <<i <<std::endl;
            //std::cout <<"TempParametrageEnnemiCadrage.uiLeDernierDeMaLigneEst" <<TempParametrageEnnemiCadrage.uiLeDernierDeMaLigneEst <<" - i:" <<i <<std::endl;

            if (i != (m_uiNbEnnemisParLignes) || i != m_uiCadrageX + m_uiNbEnnemisParLignes)
            {
                icranX++;
                TempParametrageEnnemiCadrage.uiJeSuisDansLaColonne = icranX - 1;
                //std::cout <<i <<"-" <<TempParametrageEnnemiCadrage.uiJeSuisDansLaColonne <<std::endl;
            }

            TempParametrageEnnemiCadrage.EnnemiDetruit = false; //true;
            TempParametrageEnnemiCadrage.EnnemiDetruitComptabilise = false;
            TempParametrageEnnemiCadrage.bEntreeOK = false;
            TempParametrageEnnemiExplosion.ExplosionEnnemi = false;
            TempParametrageEnnemiCadrage.EnnemiPeutTirer = true;
            TempParametrageEnnemiExplosion.pExplosionEnnemis = 0;

            if (i >= (m_uiNombreTotalEnnemis - m_uiNbEnnemisParLignes))
            {
                TempParametrageEnnemiCadrage.EnnemiDessousDetruit = true;
                TempParametrageEnnemiCadrage.bTousEnnemisDessousDansColonneDetruit = true;
            }
            else
            {
                TempParametrageEnnemiCadrage.EnnemiDessousDetruit = false;
                TempParametrageEnnemiCadrage.bTousEnnemisDessousDansColonneDetruit = false;
            }

            if (i < m_uiNbEnnemisParLignes)
            {
                TempParametrageEnnemiCadrage.EnnemiDessusDetruit = true;
            }
            else
            {
                TempParametrageEnnemiCadrage.EnnemiDessusDetruit = false;
            }

            /*Initialisation du cadrage de l'armée*/
            TempParametrageEnnemiCadrage.ColonneDetruite = false;
            TempParametrageEnnemiCadrage.CadrageOK = false;
            TempParametrageEnnemiCadrage.LigneKO = false;

            TempParametrageEnnemiProprietes.fTailleEnnemiX = 5.f;
            TempParametrageEnnemiProprietes.fTailleEnnemiY = 5.f;

            /*if(!SpritesEnnemis.empty())
            {
                TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[0];
                TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[1];
            }*/

            //SpriteEnnemi.Resize (TempParametrageEnnemi.fTailleEnnemiX, TempParametrageEnnemi.fTailleEnnemiY);

            ParametrageEnnemi.push_back(TempParametrageEnnemi);
            ParametrageEnnemiExplosion.push_back(TempParametrageEnnemiExplosion);
            ParametrageEnnemiProprietes.push_back(TempParametrageEnnemiProprietes);
            ParametrageEnnemiCadrage.push_back(TempParametrageEnnemiCadrage);
        }

        /*Calcul du point limite en Y jusqu'où l'armèe peut descendre*/
        int iNombreLignesEnnemis = m_uiNombreLignesEnnemis;
        m_fFinCourseY =
        (HAUTEUR_FENETRE) -
        ((((iNombreLignesEnnemis-1)*m_uiEspaceY_EntreEnnemis) + (DonnesXMLEnnemi[0].m_fTailleEnnemiY*iNombreLignesEnnemis)));

        m_fHauteurSautYEnnemis = m_fFinCourseY / m_uiNombreDeSautsEnnemis;

        m_bStopArmee = false;

        m_bVaisseauTerrienTouche = false;
    }

    else
    {
        bInitArmeeEnnemie = false;
    }

    TimerTireur.Reset ();
    bEntreeEnnemis = false;
    EntreeEnnemis.Reset ();
    m_uidEnnemi = 0;
    m_CentreEnnemi = GetCentreEnnemi ();

    /*for (unsigned int nbEnnemis = 0; nbEnnemis < m_uiNombreTotalEnnemis;  nbEnnemis++)
    {
        ParametrageEnnemi[nbEnnemis].fTailleEnnemiX = 5.f;
        ParametrageEnnemi[nbEnnemis].fTailleEnnemiY = 5.f;
    }*/

    return bInitArmeeEnnemie;
}
//==============================================================================
void CEnnemis::InitImageArmeeEnnemis (std::vector <sf::Image> ImageDeEnnemi, std::vector <sf::Image> ImageDeArmeEnnemi)
{
        for (unsigned int i = 0; i < m_uiNombreTotalEnnemis; i++)
        {
            unsigned int uiTypeEnnemi = 0;

            if (i > m_uiPosFinEnnemisType2)
            {
                uiTypeEnnemi = 0;
                sTextureEnnemi1 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi1bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    ParametrageEnnemi[i].SpriteEnnemi1 = SpritesEnnemis[0];
                    ParametrageEnnemi[i].SpriteEnnemi2 = SpritesEnnemis[1];
                }
            }

            else if (i > m_uiPosFinEnnemisType1)
            {
                uiTypeEnnemi = 1;
                sTextureEnnemi2 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi2bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[2];
                    TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[3];
                }
            }

            else if (i < m_uiPosFinEnnemisType1)
            {
                uiTypeEnnemi = 2;
                sTextureEnnemi3 = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture1;
                sTextureEnnemi3bis = DonnesXMLEnnemi[uiTypeEnnemi].m_sTexture2;

                if(!SpritesEnnemis.empty())
                {
                    TempParametrageEnnemi.SpriteEnnemi1 = SpritesEnnemis[4];
                    TempParametrageEnnemi.SpriteEnnemi2 = SpritesEnnemis[5];
                }
            }
        }

    //Ennemis
    ImageEnnemi1 = ImageDeEnnemi[0];
    ImageEnnemi1bis = ImageDeEnnemi[1];
    ImageEnnemi2 = ImageDeEnnemi[2];
    ImageEnnemi2bis = ImageDeEnnemi[3];
    ImageEnnemi3 = ImageDeEnnemi[4];
    ImageEnnemi3bis = ImageDeEnnemi[5];

    /*SpriteEnnemi.Resize(
    ParametrageEnnemi[i].fTailleEnnemiX,
    ParametrageEnnemi[i].fTailleEnnemiY);*/

    SpriteEnnemi.SetImage(ImageEnnemi1);
    SpriteEnnemi.Resize(35, 35);

    m_TailleEnnemi = GetTailleEnnemi ();
    m_TailleTirEnnemi = GetTailleTirEnnemi ();

    sf::Sprite SpriteEnnemi1;
    sf::Sprite SpriteEnnemi1bis;
    sf::Sprite SpriteEnnemi2;
    sf::Sprite SpriteEnnemi2bis;
    sf::Sprite SpriteEnnemi3;
    sf::Sprite SpriteEnnemi3bis;

    SpriteEnnemi1.SetImage(ImageEnnemi1);
    SpriteEnnemi1.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi1);

    SpriteEnnemi1bis.SetImage(ImageEnnemi1bis);
    SpriteEnnemi1bis.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi1bis);

    SpriteEnnemi2.SetImage(ImageEnnemi2);
    SpriteEnnemi2.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi2);

    SpriteEnnemi2bis.SetImage(ImageEnnemi2bis);
    SpriteEnnemi2bis.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi2bis);

    SpriteEnnemi3.SetImage(ImageEnnemi3);
    SpriteEnnemi3.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi3);

    SpriteEnnemi3bis.SetImage(ImageEnnemi3bis);
    SpriteEnnemi3bis.Resize(35, 35);

    SpritesEnnemis.push_back(SpriteEnnemi3bis);

    //Armes
    ImageArmeEnnemi = ImageDeArmeEnnemi[0];
}
//==============================================================================
void CEnnemis::InitSonsArmeeEnnemis (sf::SoundBuffer& BufferSonEnnemi)
{
    m_BufferSonEnnemiKO = BufferSonEnnemi;

    sf::Sound SonEnnemiKO(m_BufferSonEnnemiKO);

    for (unsigned int i = 0; i < m_uiNombreTotalEnnemis; i++)
    {
        //std::cout <<i <<std::endl;
        TempParametrageEnnemiSon.SonExplosionEnnemi = SonEnnemiKO;
        TempParametrageEnnemiSon.bSonExplosionEnnemiJoue = false;
        ParametrageEnnemiSon.push_back(TempParametrageEnnemiSon);
    }

    std::cout <<ParametrageEnnemiSon.size ()  <<std::endl;

    ParametrageEnnemiSon[52].SonExplosionEnnemi.Play ();

    while (  ParametrageEnnemiSon[52].SonExplosionEnnemi.GetStatus() == sf::Sound::Playing)
    {
        sf::Sleep(0.1f);
    }
}
//==============================================================================
void CEnnemis::VerifierEnnemiDessousDetruit(unsigned int i)
{
    if (ParametrageEnnemiCadrage[i+m_uiNbEnnemisParLignes].EnnemiDetruit == true)
    {
        ParametrageEnnemiCadrage[i].EnnemiDessousDetruit = true;
    }
}
//==============================================================================
void CEnnemis::DessinerEnnemi(unsigned int i, sf::Vector2f Position, sf::RenderWindow& AppEnnemi, unsigned int uiTextureSprite)
{
    if (uiTextureSprite == 1)
    {
        ParametrageEnnemi[i].SpriteEnnemi1.SetPosition(Position);
        AppEnnemi.Draw(ParametrageEnnemi[i].SpriteEnnemi1);
    }

    else if (uiTextureSprite == 2)
    {
        ParametrageEnnemi[i].SpriteEnnemi2.SetPosition(Position);
        AppEnnemi.Draw(ParametrageEnnemi[i].SpriteEnnemi2);
    }
}
//==============================================================================
void CEnnemis::DessinerArmeeEnnemie(sf::RenderWindow& AppEnnemi)
{
    unsigned int nbEnnemis = 0;
    bool bEnnemisDetruit = false;
    unsigned int uiTexture = 0;

    /*if (!bEntreeEnnemis)
    {
        GererEntreeEnnemis (AppEnnemi);
    }*/

    m_fChangeTexture = TimeToChangeTextureEnnemi.GetElapsedTime();

    if (m_fChangeTexture < 0.5)
    {
        uiTexture = 1;
    }

    else
    {
        if (m_fChangeTexture > 1.0)
        {
            TimeToChangeTextureEnnemi.Reset();
        }

        if (m_fChangeTexture > 0.5)
        {
            uiTexture = 2;
        }
    }

    do
    {
        bEnnemisDetruit = ParametrageEnnemiCadrage[nbEnnemis].EnnemiDetruit;

        if (!bEnnemisDetruit)
        {
            m_PositionEnnemi = ParametrageEnnemi[nbEnnemis].PositionEnnemi + PositionArmee;

            DessinerEnnemi(nbEnnemis, m_PositionEnnemi, AppEnnemi, uiTexture);

            if(
                m_vEnnemisPouvantTirer.size () < m_uiNbEnnemisParLignes - m_uiNbColonnesKO
                || m_uiNbEnnemisKOTireur != m_uiNbEnnemisKO
              )
            {
                //std::cout <<"tireur - " <<nbEnnemis <<std::endl;

                if (VerifierTousEnnemisDessousDetruitDansColonne(nbEnnemis))
                {
                    m_vEnnemisPouvantTirer = CreerVectorAvecEnnemisPouvantTirer (nbEnnemis);
                    //std::cout <<"tireur - " <<nbEnnemis <<std::endl;
                }
            }

            nbEnnemis++;
        }

        else if (bEnnemisDetruit)
        {
            if(ParametrageEnnemiCadrage[nbEnnemis].EnnemiDetruitComptabilise == false)
            {
              m_uiNbEnnemisKO++;
              ParametrageEnnemiCadrage[nbEnnemis].EnnemiDetruitComptabilise = true;
            }

            if (m_uiNbEnnemisKOCadrage != m_uiNbEnnemisKO)
            {
                //std::cout <<"nbEnnemis: " <<nbEnnemis <<std::endl;

                if (ParametrageEnnemiCadrage[nbEnnemis].ColonneDetruite == false)
                {
                    PositionnerColonnes(nbEnnemis);
                }

                if (ParametrageEnnemiCadrage[nbEnnemis].LigneDetruite == false)
                {
                    VerifierLignesPrecedentesDetruites(nbEnnemis);
                }

                m_uiNbEnnemisKOCadrage = m_uiNbEnnemisKO;
            }

            if (ParametrageEnnemiExplosion[nbEnnemis].ExplosionEnnemi == false)
            {
                if (ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis != 0)
                {
                    //std::cout<< "explo" << nbEnnemis <<std::endl;

                    ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis->Explosion();

                    if(ParametrageEnnemiSon[nbEnnemis].bSonExplosionEnnemiJoue == false)
                    {
                        JouerSonEnnemiKO (nbEnnemis);
                        ParametrageEnnemiSon[nbEnnemis].bSonExplosionEnnemiJoue = true;
                    }
                }

                if(ParametrageEnnemiExplosion[nbEnnemis].TimerEplosionEnnemis.GetElapsedTime() > 1.0f)
                {
                    ParametrageEnnemiExplosion[nbEnnemis].ExplosionEnnemi = true;

                    if (ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis != 0)
                    {
                        delete ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis;
                        ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis = 0;
                    }
                }
            }

            nbEnnemis++;
        }
    }
    while(nbEnnemis <= m_uidEnnemi);

    //std::cout <<"------------------------------------------" <<std::endl;

    if (
        m_uiNbEnnemisKO == m_uiNombreTotalEnnemis
        && m_bNiveauUpdate == false
       )
       {
            m_uiNiveauxEnCours++;
            m_bNiveauUpdate = true;
       }
}
//==============================================================================
void CEnnemis::GererDeplacementsArmee()
{
    if(m_uiNbEnnemisKO >= (m_uiTempNbEnnemisKO + 1))
    {
        AccelererVitesseArmee();
    }

    float fVitesseX  = m_fVitesseArmee * m_fElapsedTimeEnnemis;
    float fVitesseY  = m_fHauteurSautYEnnemis;// * m_fElapsedTimeEnnemis;

    if (PositionArmee.y <= m_fFinCourseY && m_bStopArmee == false)
    {
        if (PositionArmee.x <= finCourseX-(ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*m_iNbColonnesFinOK && recule == false)
        {
            if ((PositionArmee.x + fVitesseX) <
               finCourseX-(ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*m_iNbColonnesFinOK)
            {
                PositionArmee.x += fVitesseX;
            }

            else
            {
                fVitesseX = finCourseX-(ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*m_iNbColonnesFinOK - PositionArmee.x;
                PositionArmee.x += fVitesseX;
                fVitesseX = m_fVitesseArmee * m_fElapsedTimeEnnemis;
            }
        }

        if (PositionArmee.x >= finCourseX-(ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*m_iNbColonnesFinOK && recule == false)
        {
            if ((PositionArmee.y + fVitesseY) <= m_fFinCourseY)
            {
                PositionArmee.y += fVitesseY;
                recule = true;
            }

            else
            {
                fVitesseY = m_fFinCourseY - PositionArmee.y;
                PositionArmee.y += fVitesseY;
                m_bStopArmee = true;
            }
        }

        if (recule == true)
        {
            PositionArmee.x -= fVitesseX;

            if (PositionArmee.x <= debutCourseX+(ECART_ENTRE_ENNEMIS+DonnesXMLEnnemi[0].m_fTailleEnnemiX)*m_iNbColonnesDebutOK)
            {
                if ((PositionArmee.y + fVitesseY) <= m_fFinCourseY)
                {
                    PositionArmee.y += fVitesseY;
                    recule = false;
                }

                else
                {
                    fVitesseY = m_fFinCourseY - PositionArmee.y;
                    PositionArmee.y += fVitesseY;
                    recule = false;
                }
            }
        }
    }
}
//==============================================================================
void CEnnemis::AnimerArmeeEnnemie(sf::RenderWindow& AppEnnemi)
{
    if (bEntreeEnnemis)
    {
        //LancerTirEnnemis(AppEnnemi);
        //GererDeplacementsArmee();
        DessinerArmeeEnnemie(AppEnnemi);
    }

    else
    {
       GererEntreeEnnemis (AppEnnemi);
    }
}
//==============================================================================
void CEnnemis::PositionnerColonnes(unsigned int i)
{
    unsigned int uiCptLignesEnnemis = 0;
    std::vector <int> EnnemiKO;
    EnnemiKO.clear ();
    bool bEnnemisDessousKO = true;

    //std::cout <<"debut-------------i------------- "<<i <<std::endl;

    for (int y = m_uiNombreLignesEnnemis; y > 0; y--)
    {
        if (i >= m_uiNbEnnemisParLignes)
        {
            unsigned int k = i+(m_uiNbEnnemisParLignes*(m_uiNombreLignesEnnemis-y))-i+ParametrageEnnemiCadrage[i].uiJeSuisDansLaColonne;//m_uiNbEnnemisParLignes;

            if (k < m_uiNombreTotalEnnemis && ParametrageEnnemiCadrage[k].EnnemiDetruit == true
                && bEnnemisDessousKO == true)
            {
                uiCptLignesEnnemis++;
                EnnemiKO.push_back(k);
                //std::cout <<"k -"<<k;
            }

            else
            {
                bEnnemisDessousKO = false;
            }
        }

        else
        if (ParametrageEnnemiCadrage[i+(m_uiNbEnnemisParLignes*(m_uiNombreLignesEnnemis-y))].EnnemiDetruit == true
            &&  bEnnemisDessousKO == true)
        {
            uiCptLignesEnnemis++;
            EnnemiKO.push_back(i+(m_uiNbEnnemisParLignes*(m_uiNombreLignesEnnemis-y)));
        }

        else
        {
                bEnnemisDessousKO = false;
        }
    }

     //std::cout <<std::endl;

    //std::cout <<"1 - uiCptLignesEnnemis "<<uiCptLignesEnnemis <<std::endl;

    if (uiCptLignesEnnemis < m_uiNombreLignesEnnemis && bEnnemisDessousKO == true)
    {
        for (unsigned int x = (m_uiNombreLignesEnnemis - uiCptLignesEnnemis ); x > 0; x--)
        {
            if(ParametrageEnnemiCadrage[i - (m_uiNbEnnemisParLignes * x)].EnnemiDetruit == true
               && i > (m_uiNombreTotalEnnemis - m_uiNbEnnemisParLignes)
               && ParametrageEnnemiCadrage[i].EnnemiDessusDetruit == false
               )
            {
                uiCptLignesEnnemis++;
                ParametrageEnnemiCadrage[i].EnnemiDessusDetruit = true;
                EnnemiKO.push_back(i - (m_uiNbEnnemisParLignes * x));
            }
        }
    }

    //std::cout <<"3 - uiCptLignesEnnemis "<<uiCptLignesEnnemis <<std::endl;

    //std::cout <<"EnnemiKO.size()" <<EnnemiKO.size() <<std::endl;
    if (EnnemiKO.size() == m_uiNombreLignesEnnemis)
    {
        for (unsigned int w = 0; w < EnnemiKO.size(); w++)
        {
            ParametrageEnnemiCadrage[EnnemiKO[w]].ColonneDetruite = true;
            //std::cout <<EnnemiKO[w] <<" - " <<ParametrageEnnemiCadrage[EnnemiKO[w]].ColonneDetruite <<std::endl;

        }

        if (ParametrageEnnemiCadrage[i].ColonneDetruite == true)
        {
            unsigned int uiNbColonnesAvantDetruites = VerifierColonneAvantDetruites ();

            //std::cout <<"uiNbColonnesAvantDetruites" <<uiNbColonnesAvantDetruites <<std::endl;

            //if (uiNbColonnesAvantDetruites > 0)
            //{
                m_iNbColonnesDebutOK = -uiNbColonnesAvantDetruites;

                //std::cout <<"Colonnes detruites avant" <<m_iNbColonnesDebutOK <<std::endl;

               m_iNbColonnesFinOK = VerifierColonneApresDetruites();

               //std::cout <<"Colonnes detruites apres" <<m_iNbColonnesFinOK  <<std::endl;
            //}

            //std::cout <<"nombre de colonnes detruites debut" <<m_iNbColonnesDebutOK <<std::endl;

            //std::cout <<"nombre de colonnes detruites fin" <<m_iNbColonnesFinOK <<std::endl;
        }
    }

    //std::cout <<"fin-------------i------------- "<<i <<std::endl;
}
//==============================================================================
unsigned int CEnnemis::VerifierColonneAvantDetruites()
{
    unsigned int uiNbColonnesAvantDetruites = 0;

    for (unsigned int uiNbColonnesAvant = 0; uiNbColonnesAvant < m_uiNbEnnemisParLignes; uiNbColonnesAvant++)
    {
        if(ParametrageEnnemiCadrage[uiNbColonnesAvant].ColonneDetruite == true)
        {
            uiNbColonnesAvantDetruites++;
        }

        else if(ParametrageEnnemiCadrage[uiNbColonnesAvant].ColonneDetruite == false)
        {
            return uiNbColonnesAvantDetruites;
        }
    }

    //std::cout <<"uiNbColonnesAvantDetruites" <<uiNbColonnesAvantDetruites <<std::endl;//
    return uiNbColonnesAvantDetruites;
}
//==============================================================================
int CEnnemis::VerifierColonneApresDetruites()
{
    unsigned int uiNbColonnesApresDetruites = 0;

    for (unsigned int uiNbColonnesApres = m_uiNbEnnemisParLignes - 1; uiNbColonnesApres > 0; uiNbColonnesApres--)
    {
        if(ParametrageEnnemiCadrage[uiNbColonnesApres].ColonneDetruite == true)
        {
            uiNbColonnesApresDetruites++;
        }

        else if(ParametrageEnnemiCadrage[uiNbColonnesApres].ColonneDetruite == false)
        {
            return m_uiNbEnnemisParLignes - uiNbColonnesApresDetruites;
        }
    }

    //std::cout <<"uiNbColonnesApresDetruites" <<uiNbColonnesApresDetruites <<std::endl;
    return m_uiNbEnnemisParLignes - uiNbColonnesApresDetruites;
}
//==============================================================================
bool CEnnemis::LancerTirEnnemis(sf::RenderWindow& AppTir)
{
    //Pour debug
    m_bVaisseauTerrienTouche = false;

    if (m_bLancementTirPossible == true)
    {
        InitialiserTirs();
    }

    else if (m_LancementTir.GetElapsedTime () > m_fTpsRenitTir && m_bLancementTirPossible == false)
    {
        m_LancementTir.Reset ();
        m_bLancementTirPossible = true;
        //ParametrageEnnemiCadrage[m_uiTireur].EnnemiPeutTirer = false;
    }

    for (
            it_ParametrageTirEnnemi = ParametrageTirEnnemi.begin();
            it_ParametrageTirEnnemi != ParametrageTirEnnemi.end();
            ++it_ParametrageTirEnnemi
        )
    {
            if (
                    (*it_ParametrageTirEnnemi).TirEnnemiExplose == false
                    && (*it_ParametrageTirEnnemi).ExplosionTir == false
                    && (*it_ParametrageTirEnnemi).bTirOut == false
                )
            {
                (*it_ParametrageTirEnnemi).ITirEnnemisParticules.ParticuleQuad
                (sf::Vector2f ((*it_ParametrageTirEnnemi).PositionTirEnnemiX, (*it_ParametrageTirEnnemi).PositionTirEnnemiY));

                (*it_ParametrageTirEnnemi).PositionTirEnnemiY += (VITESSE_TIR_ENNEMI * m_fElapsedTimeEnnemis);
                (*it_ParametrageTirEnnemi).SpriteArme.SetImage(ImageArmeEnnemi);
                (*it_ParametrageTirEnnemi).SpriteArme.SetPosition(sf::Vector2f ((*it_ParametrageTirEnnemi).PositionTirEnnemiX - (*it_ParametrageTirEnnemi).SpriteArme.GetSize().x/2, (*it_ParametrageTirEnnemi).PositionTirEnnemiY - (*it_ParametrageTirEnnemi).SpriteArme.GetSize().y-5));
                (*it_ParametrageTirEnnemi).SpriteArme.Resize(20, 20);

                AppTir.Draw( (*it_ParametrageTirEnnemi).SpriteArme);

                if(!m_bVaisseauTerrienTouche)
                {
                    m_bVaisseauTerrienTouche =
                    ICollisions.DetecterCollisionTirEnnemiVaisseau
                    (sf::Vector2f ((*it_ParametrageTirEnnemi).PositionTirEnnemiX,(*it_ParametrageTirEnnemi).PositionTirEnnemiY),
                    PositionVaisseauTerrien, TailleVaisseauTerrien);

                    if (m_bVaisseauTerrienTouche)
                    {
                        (*it_ParametrageTirEnnemi).ExplosionTir = true;
                    }
                }

                if (
                        (*it_ParametrageTirEnnemi).PositionTirEnnemiY  >= 650
                        && (*it_ParametrageTirEnnemi).bTirOut == false
                   )
                {
                    (*it_ParametrageTirEnnemi).bTirOut = true;
                    it_ParametrageTirEnnemi = ParametrageTirEnnemi.erase(it_ParametrageTirEnnemi);
                    continue;
                }
           }

            else if (
                    (*it_ParametrageTirEnnemi).TimerExplosionTirEnnemi.GetElapsedTime () < 1.0f
                    && (*it_ParametrageTirEnnemi).ExplosionTir == true
               )
            {
                (*it_ParametrageTirEnnemi).ITirEnnemisParticules.CreerExplosion ();
            }

            else if (
                        (*it_ParametrageTirEnnemi).TimerExplosionTirEnnemi.GetElapsedTime () > 1.0f
                        && (*it_ParametrageTirEnnemi).TirEnnemiExplose == true
                    )
            {
                it_ParametrageTirEnnemi = ParametrageTirEnnemi.erase(it_ParametrageTirEnnemi);
                continue;
            }

           else
           {
                it_ParametrageTirEnnemi = ParametrageTirEnnemi.erase(it_ParametrageTirEnnemi);
           }
    }

    return m_bVaisseauTerrienTouche;
}
//==============================================================================
void CEnnemis::InitialiserTirs()
{
    unsigned int m_uiTireur = 0;
    unsigned int uiNombreAleatoire = 0;


    //sf::Vector2f TailleEnnemi = GetTailleEnnemi ();

    //if (m_bLancementTirPossible == true)
    //{
        m_bLancementTirPossible = false;

        if(m_vEnnemisPouvantTirer.size () > 0)
        uiNombreAleatoire = TirerNombreAleatoire(0, m_vEnnemisPouvantTirer.size () - 1);

        if (!m_vEnnemisPouvantTirer.empty ())
        m_uiTireur = m_vEnnemisPouvantTirer[uiNombreAleatoire];

        if
        (
            ParametrageEnnemiCadrage[m_uiTireur].EnnemiDetruit == false
            && !m_vEnnemisPouvantTirer.empty ()
        )
        {
            //std::cout <<"m_uiTireur: " <<m_uiTireur  <<std::endl;
            //std::cout <<"TimerTireur: " <<TimerTireur.GetElapsedTime ()  <<std::endl;

            TimerTireur.Reset ();

            TempParametrageTirEnnemi.SpriteArme.SetImage(ImageArmeEnnemi);

            TempParametrageTirEnnemi.ITirEnnemisParticules.InitialiserGenerateurParticules
            (
                TAILLE_PARTICULES_TIRS_ENNEMIS,
                NB_PARTICULES_TIRS_ENNEMIS,
                sf::Vector2f (0.0, 0.0),
                0.0,
                ESPACE_Y_ENTRE_PARTICULES_TIRS_ENNEMIS,
                sf::Color(255, 255, 0),
                TEMPS_REINIT_PARTICULES_TIRS_ENNEMIS,
                DUREE_VIE_PARTICULES_TIRS_ENNEMIS,
                DEPART_Y_PARTICULES_TIRS_ENNEMIS
            );

            TempParametrageTirEnnemi.PositionTirEnnemiX =
            ParametrageEnnemi[m_uiTireur].PositionEnnemi.x + PositionArmee.x + m_CentreEnnemi.x + m_TailleEnnemi.x/2;

            TempParametrageTirEnnemi.PositionTirEnnemiY =
            ParametrageEnnemi[m_uiTireur].PositionEnnemi.y + PositionArmee.y + m_CentreEnnemi.y + m_TailleEnnemi.y/2;

            TempParametrageTirEnnemi.TirEnnemiExplose = false;
            TempParametrageTirEnnemi.bTirOut = false;
            TempParametrageTirEnnemi.ExplosionTir = false;

            TempParametrageTirEnnemi.TimerExplosionTirEnnemi.Reset ();

            ParametrageTirEnnemi.push_back(TempParametrageTirEnnemi);

            ParametrageEnnemiCadrage[m_uiTireur].EnnemiPeutTirer = false;
        }
    //}

    else if (m_LancementTir.GetElapsedTime () > m_fTpsRenitTir && m_bLancementTirPossible == false)
    {
        m_LancementTir.Reset ();
        m_bLancementTirPossible = true;
        ParametrageEnnemiCadrage[m_uiTireur].EnnemiPeutTirer = false;
    }
}
//==============================================================================
void CEnnemis::VerifierLignesPrecedentesDetruites(unsigned int i)
{
    unsigned int uiEnnemisDetruitsDansLigne = 0;
    std::vector <unsigned int> vEnnemisDetruits;
    vEnnemisDetruits.clear ();

    for (unsigned int uiEnnemiDansLigne = ParametrageEnnemiCadrage[i].uiLePremierDeMaLigneEst;
         uiEnnemiDansLigne <= ParametrageEnnemiCadrage[i].uiLeDernierDeMaLigneEst;
         uiEnnemiDansLigne++)
    {
        if(ParametrageEnnemiCadrage[uiEnnemiDansLigne].EnnemiDetruit == true)
        {
            uiEnnemisDetruitsDansLigne++;
            vEnnemisDetruits.push_back(uiEnnemiDansLigne);
        }
    }

    if(uiEnnemisDetruitsDansLigne == m_uiNbEnnemisParLignes)
    {

        for (unsigned int uiDansVector = 0; uiDansVector < vEnnemisDetruits.size(); uiDansVector++)
        {
            ParametrageEnnemiCadrage[vEnnemisDetruits[uiDansVector]].LigneDetruite = true;

            //std::cout <<vEnnemisDetruits[uiDansVector] <<std::endl;
        }

        //m_fFinCourseY += (DonnesXMLEnnemi[0].m_fTailleEnnemiY + m_uiEspaceY_EntreEnnemis);

        unsigned int uiNbLignes = 0;

        //Pour verifier qu'il n'y a pas de ligne encore dessous
        if(ParametrageEnnemiCadrage[i].uiLePremierDeMaLigneEst+m_uiNbEnnemisParLignes < m_uiNombreTotalEnnemis)
        {
            for (unsigned int uiLigne = ParametrageEnnemiCadrage[i].uiLePremierDeMaLigneEst+m_uiNbEnnemisParLignes;
                uiLigne < m_uiNombreTotalEnnemis;
                uiLigne += m_uiNbEnnemisParLignes)
            {
                if(ParametrageEnnemiCadrage[uiLigne].LigneDetruite == true)
                {
                    uiNbLignes++;
                }
            }
        }

        if (uiNbLignes + ParametrageEnnemiCadrage[i].uiJeSuisDansLaLigne == m_uiNombreLignesEnnemis)
        {
            //std::cout <<"1111111111111111111111111111111" <<" - "  <<i <<std::endl;
            m_fFinCourseY += ((DonnesXMLEnnemi[0].m_fTailleEnnemiY + m_uiEspaceY_EntreEnnemis));
        }

        uiNbLignes = 0;

        if(i >= m_uiNbEnnemisParLignes)
        {
            for (unsigned int uiLigne = ParametrageEnnemiCadrage[i].uiLePremierDeMaLigneEst-m_uiNbEnnemisParLignes;
                uiLigne > 0;
                uiLigne -= m_uiNbEnnemisParLignes)
            {
                if(ParametrageEnnemiCadrage[uiLigne].LigneDetruite == true)
                {
                    uiNbLignes++;
                }

                else
                {
                   break;
                }
            }

            //std::cout <<"2222222222222222222222222222" <<" - " <<i <<" - " <<uiNbLignes <<std::endl;
            m_fFinCourseY += (DonnesXMLEnnemi[0].m_fTailleEnnemiY + m_uiEspaceY_EntreEnnemis)*uiNbLignes;
        }
    }
}
//==============================================================================
void CEnnemis::EstDansEcran (float fRayon, std::list<ParametresTirEnnemi>::iterator it)
{
    if (
        (*it).PositionTirEnnemiY  >= fRayon
        && (*it).bTirOut == false
       )
    {
        (*it).bTirOut = true;
    }
}
//==============================================================================
int CEnnemis::TirerNombreAleatoire(int iDebutPlage, int iFinPlage)
{
    return sf::Randomizer::Random(iDebutPlage, iFinPlage);
}
//==============================================================================
void CEnnemis::ReglerTempsReinitTir()
{

    if(m_uiNbEnnemisKO == (m_uiTempNbEnnemisKO + 8))
    {
        if(m_fTpsRenitTir > 0.1)
        {
            m_fTpsRenitTir = m_fTpsRenitTir - 0.2;
        }

        else
        {
            m_fTpsRenitTir = 0.1;
        }

        m_fVitesseArmee = m_fVitesseArmee + 15;
        m_uiTempNbEnnemisKO = m_uiNbEnnemisKO;
    }
}
//==============================================================================
sf::Vector2f CEnnemis::GetCentreEnnemi ()
{
    return SpriteEnnemi.GetCenter ();
}
//==============================================================================
sf::Vector2f CEnnemis::GetTailleEnnemi ()
{
    return SpriteEnnemi.GetSize ();
}
//==============================================================================
float CEnnemis::GetTailleTirEnnemi ()
{
    return TAILLE_PARTICULES_TIRS_ENNEMIS;
}
//==============================================================================
bool CEnnemis::VerifierTousEnnemisDessousDetruitDansColonne (unsigned int i)
{
    for (unsigned int uiPos = i+m_uiNbEnnemisParLignes;
         uiPos < m_uiNombreTotalEnnemis;
         uiPos += m_uiNbEnnemisParLignes)
         {
             if (ParametrageEnnemiCadrage[uiPos].EnnemiDetruit == false)
             {
                return false;
             }
         }

    return true;
}
//==============================================================================
void CEnnemis::AccelererVitesseArmee()
{
    //if(m_uiNbEnnemisKO >= (m_uiTempNbEnnemisKO + 8))
    //{
        m_fVitesseArmee = m_fVitesseArmee + m_fAcceleration;
        m_uiTempNbEnnemisKO = m_uiNbEnnemisKO;
        //std::cout <<"m_fVitesseArmee "<<m_fVitesseArmee <<std::endl;
    //}
}
//==============================================================================
void CEnnemis::GererEntreeEnnemis (sf::RenderWindow& AppEntreeEnnemi)
{
    if(m_uidEnnemi < m_uiNombreTotalEnnemis
       && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiX < DonnesXMLEnnemi[0].m_fTailleEnnemiY
       && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiY < DonnesXMLEnnemi[0].m_fTailleEnnemiY)
    {
            if (EntreeEnnemis.GetElapsedTime () > .01f
                && ParametrageEnnemiCadrage[m_uidEnnemi].bEntreeOK == false
                && !bEntreeEnnemis)
            {
                ParametrageEnnemiCadrage[m_uidEnnemi].bEntreeOK = true;
            }

            if (ParametrageEnnemiCadrage[m_uidEnnemi].bEntreeOK  == true)
            {
                //std::cout <<"echo" <<std::endl;
                ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiX += 10.f;
                ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiY += 10.f;
            }
    }

    if (m_uidEnnemi == m_uiNombreTotalEnnemis - 1
    && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiX >= DonnesXMLEnnemi[0].m_fTailleEnnemiY
    && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiY >= DonnesXMLEnnemi[0].m_fTailleEnnemiY)
    {
        bEntreeEnnemis = true;
    }

    if (m_uidEnnemi < m_uiNombreTotalEnnemis
       && bEntreeEnnemis == false
       && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiX >= DonnesXMLEnnemi[0].m_fTailleEnnemiY
       && ParametrageEnnemiProprietes[m_uidEnnemi].fTailleEnnemiY >= DonnesXMLEnnemi[0].m_fTailleEnnemiY)
       {
            m_uidEnnemi++;
            EntreeEnnemis.Reset ();
       }

    unsigned int uiTexture = 0;

    m_fChangeTexture = TimeToChangeTextureEnnemi.GetElapsedTime();

    if (m_fChangeTexture < 0.5)
    {
        uiTexture = 1;
    }

    else
    {
        if (m_fChangeTexture > 1.0)
        {
            TimeToChangeTextureEnnemi.Reset();
        }

        if (m_fChangeTexture > 0.5)
        {
            uiTexture = 2;
        }
    }

    for (unsigned int uiNbEnnemis = 0; uiNbEnnemis <= m_uidEnnemi;  uiNbEnnemis++)
    {
        m_PositionEnnemi = (ParametrageEnnemi[uiNbEnnemis].PositionEnnemi
        + PositionArmee);

        DessinerEnnemi(uiNbEnnemis, m_PositionEnnemi, AppEntreeEnnemi, uiTexture);
    }
}
//==============================================================================
std::vector <unsigned int> CEnnemis::CreerVectorAvecEnnemisPouvantTirer (unsigned int i)
{
    if(m_uiNbEnnemisKOTireur != m_uiNbEnnemisKO && !m_vEnnemisPouvantTirer.empty ())
    {
        //std::cout <<"taillenulle " <<m_vEnnemisPouvantTirer.size () <<std::endl;

        m_vEnnemisPouvantTirer.clear ();
        m_uiNbEnnemisKOTireur = m_uiNbEnnemisKO;
    }

    //std::cout <<"col " <<m_uiNbColonnesKO <<std::endl;

    if(m_vEnnemisPouvantTirer.size () < m_uiNbEnnemisParLignes - m_uiNbColonnesKO)
    {
        /*if(
            VerifierTousEnnemisDessousDetruitDansColonne (i)
            && ParametrageEnnemiCadrage[i].EnnemiDetruit == false
            && ParametrageEnnemiCadrage[i].ColonneDetruite == false
            //&& ParametrageEnnemiCadrage[i].EnnemiDessousDetruit == true
          )
        {*/
            //std::cout <<"taille " <<m_vEnnemisPouvantTirer.size () <<std::endl;
            m_vEnnemisPouvantTirer.push_back (i);
        //}
    }

    /*for (unsigned int i=0; i < m_vEnnemisPouvantTirer.size (); i++)
    {
        std::cout <<m_vEnnemisPouvantTirer[i] <<"-" ;
    }*/

    //std::cout <<std::endl;

    return m_vEnnemisPouvantTirer;
}
//==============================================================================
void CEnnemis::AppliquerImageSurSpritesEnnemis()
{
    for (unsigned int i = 0; i < ParametrageEnnemi.size() ; i++)
    {
        if (i > m_uiPosFinEnnemisType2)
        {
            if(!SpritesEnnemis.empty())
            {
                ParametrageEnnemi[i].SpriteEnnemi1 = SpritesEnnemis[0];
                ParametrageEnnemi[i].SpriteEnnemi2 = SpritesEnnemis[1];
            }
        }

        else if (i > m_uiPosFinEnnemisType1)
        {
            if(!SpritesEnnemis.empty())
            {
                ParametrageEnnemi[i].SpriteEnnemi1 = SpritesEnnemis[2];
                ParametrageEnnemi[i].SpriteEnnemi2 = SpritesEnnemis[3];
            }
        }

        else if (i <= m_uiPosFinEnnemisType1)
        {
            if(!SpritesEnnemis.empty())
            {
                ParametrageEnnemi[i].SpriteEnnemi1 = SpritesEnnemis[4];
                ParametrageEnnemi[i].SpriteEnnemi2 = SpritesEnnemis[5];
            }
        }
    }
}
//==============================================================================
void CEnnemis::JouerSonEnnemiKO (unsigned int i)
{
    ParametrageEnnemiSon[i].SonExplosionEnnemi.SetVolume(20);
    ParametrageEnnemiSon[i].SonExplosionEnnemi.Play ();
}
//==============================================================================
