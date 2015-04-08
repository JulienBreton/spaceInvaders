#ifndef __ENNEMIS_H
#define __ENNEMIS_H

#include <vector>
#include <list>

//Projet
#include "Particules.h" //#include <SFML/Window.hpp> #include <SFML/Graphics.hpp>
#include "RecupDonneesXML.h" //#include "xml_niveau.h"
#include "Explosion.h"
#include "Collisions.h"
#include "Sons.h"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

#define DEBUT_COURSE_X  0
#define FIN_COURSE_X 810

#define ECART_ENTRE_ENNEMIS 10

#define VITESSE_TIR_ENNEMI 250.f
#define TAILLE_PARTICULES_TIRS_ENNEMIS 15.0
#define NB_PARTICULES_TIRS_ENNEMIS 50
#define ESPACE_Y_ENTRE_PARTICULES_TIRS_ENNEMIS 0.0f
#define TEMPS_REINIT_PARTICULES_TIRS_ENNEMIS 0.01f
#define DUREE_VIE_PARTICULES_TIRS_ENNEMIS 0.5f
#define DEPART_Y_PARTICULES_TIRS_ENNEMIS 0.0f

class CEnnemis
{
	private:

        //Affichage ennemis
        sf::Sprite SpriteEnnemi;
        std::vector <sf::Sprite> SpritesEnnemis;

        sf::Image ImageEnnemi1;
        sf::Image ImageEnnemi1bis;
        sf::Image ImageEnnemi2;
        sf::Image ImageEnnemi2bis;
        sf::Image ImageEnnemi3;
        sf::Image ImageEnnemi3bis;
        sf::Clock TimeToChangeTextureEnnemi;
		bool m_bChangementTexture;

		//Affichage armes ennemis;
        sf::Image ImageArmeEnnemi;

        std::vector <CXMLNiveau::SArmee> StructureArmeeEnnemie;
        std::vector <CXMLNiveau::SEnnemi> StructureEnnemi;

        bool m_bVaisseauTerrienTouche;

		//Position ennemis
		sf::Vector2f m_PositionEnnemi;
        unsigned int m_uidEnnemi; //Pour entrée ennemis

        //Déplacements armee
		bool recule;
		bool m_bStopArmee;
		float debutCourseX;
		bool bEntreeEnnemis;
        sf::Clock EntreeEnnemis;
        std::vector <unsigned int> m_vColonnesEnnemisAvantDetruites;

		unsigned int m_uiNbTypesEnnemis;

        unsigned int m_uiTempNbEnnemisKO;
        unsigned int m_uiNbEnnemisKOCadrage;
        unsigned int m_uiNbEnnemisKOTireur;
        unsigned int m_uiNbEnnemisTest;

        //Cadrage de l'armee
        unsigned int m_uiCadrageX;
        unsigned int m_uiCadrageY;

        //Tirs
        bool m_bLancementTirPossible;
        bool m_bInitRandom;
        //Debut et Fin en int car c'est ce que prend en param la fonction pour rechercher un nombre aléatoire.
        int m_iDebutPlageNombresAleatoires;
        int m_iFinPlageNombresAleatoires;
        float m_fTpsRenitTir;
        sf::Clock m_LancementTir;
        unsigned int m_uiPlage;
        float fCoeffTpsRenitTir;
        std::vector  <unsigned int> m_vEnnemisPouvantTirer;

        //XML
		CRecupDonneesXML  m_iRecupDonneesXML;

        //XML Armee
        unsigned int m_uiNbEnnemisParLignes;
        unsigned int m_uiNombreLignesEnnemis;
        unsigned int m_uiNombreDeSautsEnnemis;
        unsigned int m_uiIndexArmee;
        unsigned int m_uiPosFinEnnemisType1;
        unsigned int m_uiPosFinEnnemisType2;
        unsigned int m_uiPosFinEnnemisType3;
        float m_fHauteurSautYEnnemis;
        float m_uiEspaceY_EntreEnnemis;
        float m_fDepartArmeeX;
        float m_fDepartArmeeY;
        float m_fAcceleration;

        //XML Ennemis
        struct SDonneesXMLEnnemi
        {
            float m_fTailleEnnemiX;
            float m_fTailleEnnemiY;
            unsigned int m_uiIndexEnnemi;
            unsigned int m_uiPoints;
            std::string m_sTexture1;
            std::string m_sTexture2;
        };

        struct SDonneesXMLEnnemi TempDonnesXMLEnnemi;
        std::vector <SDonneesXMLEnnemi> DonnesXMLEnnemi;

        sf::Clock TimerTireur;

        //CVaisseau IVaisseauTerrien;
        CCollisions ICollisions;
        //CSons ISonsEnnemis;

        //Sons
        //sf::Sound m_SonEnnemiKO;
        sf::SoundBuffer m_BufferSonEnnemiKO;

		//Ennemi
		//void DessinerEnnemi(unsigned int i, sf::Vector2f Position, sf::RenderWindow& AppEnnemi);
        void GererEntreeEnnemis (sf::RenderWindow& AppEntreeEnnemi);

		//Armee

        //Affichage
		void DessinerArmeeEnnemie(sf::RenderWindow& AppEnnemi);

        //Deplacement
        void AccelererVitesseArmee();

        //Cadrage
		void PositionnerColonnes(unsigned int i);
		void CadrerDebutCourseArmee(unsigned int i);
		void CadrerFinCourseArmee(unsigned int i);
		unsigned int VerifierColonneAvantDetruites();
		int VerifierColonneApresDetruites();
		void VerifierLignesPrecedentesDetruites(unsigned int i);
        bool VerifierTousEnnemisDessousDetruit(unsigned int i);
        bool VerifierTousEnnemisDessousDetruitDansColonne (unsigned int i);
        bool VerifierTousEnnemisADroiteDetruits (unsigned int i);
        bool VerifierTousEnnemisAGaucheDetruits (unsigned int i);
        bool VerifierSiPlusPetitEnnemiPouvantTirer (unsigned int i);
        //std::vector <unsigned int> CreerVectorAvecEnnemisPouvantTirer (std::vector <ParametresEnnemi>::iterator it);

        //Tirs
		bool DeterminerTirsSimultanesPossiblesDroite(unsigned int i);
		bool DeterminerTirsSimultanesPossiblesGauche(unsigned int i);
        //void EstDansEcran (float fRayon, int iNbTirs);

	public:

        //Niveaux
        unsigned int m_uiNiveauxEnCours;
        bool m_bNiveauUpdate;

        float m_fElapsedTimeEnnemis;
        float m_fVitesseArmee;
		int m_iNbColonnesDebutOK;
		int m_iNbColonnesFinOK;
        unsigned int m_uiNombreTotalEnnemis;
        unsigned int m_uiNbEnnemisKO;
        unsigned int m_uiNbColonnesKO;
        sf::Vector2f m_TailleEnnemi;
        sf::Vector2f m_CentreEnnemi;
        float m_TailleTirEnnemi;

        //Position armee
		sf::Vector2f PositionArmee;
		float finCourseX;
        float m_fFinCourseY;
        float m_fChangeTexture;

        std::string sTextureEnnemi1;
        std::string sTextureEnnemi1bis;
        std::string sTextureEnnemi2;
        std::string sTextureEnnemi2bis;
        std::string sTextureEnnemi3;
        std::string sTextureEnnemi3bis;

		struct ParametresEnnemi
		{
            sf::Sprite SpriteEnnemi1;
            sf::Sprite SpriteEnnemi2;
            sf::Vector2f PositionEnnemi;
		};

        struct ParametresEnnemi TempParametrageEnnemi;
		std::vector <ParametresEnnemi> ParametrageEnnemi;
        std::vector <ParametresEnnemi>::iterator it_ParametrageEnnemi;

       void DessinerEnnemi(unsigned int i, sf::Vector2f Position, sf::RenderWindow& AppEnnemi, unsigned int uiTextureSprite);
       std::vector <unsigned int> CreerVectorAvecEnnemisPouvantTirer (unsigned int i);
        //std::list <ParametresTirEnnemi>::iterator it_ParametrageTirEnnemi;

		struct ParametresEnnemiProprietes
		{
            sf::Vector2f CentreEnnemi;
            float fTailleEnnemiX;
            float fTailleEnnemiY;
            unsigned int uiIndexEnnemi;
            unsigned int uiPoints;
            std::string sTexture1;
            std::string sTexture2;
		};

        struct ParametresEnnemiProprietes TempParametrageEnnemiProprietes;
		std::vector <ParametresEnnemiProprietes> ParametrageEnnemiProprietes;

		struct ParametresEnnemiCadrage
		{
            bool EnnemiDetruit;
			bool EnnemiDessousDetruit;
			bool EnnemiPeutTirer;
			bool EnnemiDetruitComptabilise;
			bool ColonneDetruite;
			bool LigneDetruite;
			bool CadrageOK;
            //bool CadrageColonneOK;
            bool LigneKO;
            bool EnnemiDessusDetruit;
            unsigned int uiJeSuisDansLaColonne;
            unsigned int uiJeSuisDansLaLigne;
            unsigned int uiLePremierDeMaLigneEst;
            unsigned int uiLeDernierDeMaLigneEst;
            bool bTousEnnemisDessousDansColonneDetruit;
            bool bEntreeOK;
		};

        struct ParametresEnnemiCadrage TempParametrageEnnemiCadrage;
		std::vector <ParametresEnnemiCadrage> ParametrageEnnemiCadrage;
        std::vector <ParametresEnnemiCadrage>::iterator it_ParametrageEnnemiCadrage;

		struct ParametresEnnemiExplosion
		{
			//Explosion
			sf::Clock TimerEplosionEnnemis;
            bool ExplosionEnnemi;
			CExplosion * pExplosionEnnemis;
		};

        struct ParametresEnnemiExplosion TempParametrageEnnemiExplosion;
		std::vector <ParametresEnnemiExplosion> ParametrageEnnemiExplosion;
        std::vector <ParametresEnnemiExplosion>::iterator it_ParametresEnnemiExplosion;

		struct ParametresEnnemiSon
		{
            bool bSonExplosionEnnemiJoue;
            CSons ISonsEnnemis;
            sf::Sound SonExplosionEnnemi;
		};

        struct ParametresEnnemiSon TempParametrageEnnemiSon;
		std::vector <ParametresEnnemiSon> ParametrageEnnemiSon;
        std::vector <ParametresEnnemiSon>::iterator it_ParametresEnnemiSon;

		//Pour la détection des collisions
		sf::Vector2f PositionVaisseauTerrien;
		sf::Vector2f TailleVaisseauTerrien;
		sf::Vector2f PositionRocket;

		struct ParametresTirEnnemi
		{
			float PositionTirEnnemiX;
			float PositionTirEnnemiY;
			bool TirEnnemiExplose;
            CParticules ITirEnnemisParticules;
            sf::Clock TimerExplosionTirEnnemi;
            sf::Vector2f PositionExplosionRockets;
            bool ExplosionTir;
            bool bTirOut;
            sf::Sprite SpriteArme;
		};

        struct ParametresTirEnnemi TempParametrageTirEnnemi;
		//Utilisation d'une list bien que deque peut être plus approprié.
		std::list <ParametresTirEnnemi> ParametrageTirEnnemi;
        std::list <ParametresTirEnnemi>::iterator it_ParametrageTirEnnemi;

        //Constructeur
		CEnnemis()
		{
            m_uiNiveauxEnCours = 0;
		}

		//Destructeur
		~CEnnemis()
		{
		    for (unsigned int nbEnnemis=0; nbEnnemis<m_uiNombreTotalEnnemis; nbEnnemis++)
            {
                if (ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis != 0)
                {
                    delete ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis;
                    ParametrageEnnemiExplosion[nbEnnemis].pExplosionEnnemis = 0;
                }
            }
        }

		//void InitImageArmeeEnnemis (sf::Image& ImageDeEnnemi1, sf::Image& ImageDeEnnemi1bis);
        void InitImageArmeeEnnemis (std::vector <sf::Image> ImageDeEnnemi, std::vector <sf::Image> ImageDeArmeEnnemi);
		void InitSonsArmeeEnnemis (sf::SoundBuffer& BufferSonEnnemi);
		bool InitArmmeEnnemie();
		void InitCadrageArmee();
		void AnimerArmeeEnnemie(sf::RenderWindow& AppEnnemi);
		void VerifierEnnemiDessousDetruit(unsigned int i);
		bool LancerTirEnnemis(sf::RenderWindow& AppTir);
		void InitialiserTirs();
		void DeterminerPlageTirage(unsigned int uiEnnemi);
		void ReglerTempsReinitTir();
        void CadrerLignes(unsigned int i);
        bool ChoisirTireur(int i);
		bool VerifLignesKO(unsigned int i);
		//int TirerNombreAleatoire(long int liPlageNombres);
        int TirerNombreAleatoire(int iDebutPlage, int iFinPlage);
		float GetTailleTirEnnemi ();
        sf::Vector2f GetCentreEnnemi ();
        sf::Vector2f GetTailleEnnemi ();
        void EstDansEcran (float fRayon, std::list<ParametresTirEnnemi>::iterator it);
        void AppliquerImageSurSpritesEnnemis ();
        void GererDeplacementsArmee();
        void JouerSonEnnemiKO (unsigned int i);
};

#endif
