#ifndef XML_NIVEAU_H
#define XML_NIVEAU_H

#include "libxml2/libxml/tree.h"
#include "libxml2/libxml/xmlmemory.h"
#include "libxml2/libxml/parser.h"

#include <string>
#include <map>
#include <vector>

//Classe de chargement des niveaux.
class CXMLNiveau
{
    private:

        //Structure décrivant une arme ennemie
        struct SArmeEnnemie
        {
            unsigned int uiNbParticulesTirEnnemi;
            float fVitesseTirEnnemiY;
            float fTailleTirEnnemi;
            float fEspaceY_EntreParticulesTirEnnemi;
            float fTempsReinitParticulesTirEnnemi;
            float fDureeVieParticulesTirEnnemi;
            float fDepartY_ParticulesTirEnnemi;
        };

        SArmeEnnemie StructureArmeEnnemie;
        bool Validation (xmlDoc* pDocument);
        void Jeu (xmlNode* pNode);
        void Armee (xmlNode* pNode);
        void Ennemi (xmlNode* pNode);
        void ArmeEnnemie (xmlNode* pNode);

    public:

        //Structure décrivant une armee
        struct SArmee
        {
            float fVitesseArmeeY;
            float fAcceleration;
            float fDepartArmeeX;
            float fDepartArmeeY;
            float fDebutCourseX;
            float fFinCourseY;
            float fEspaceY_EntreEnnemis;
            float fHauteurSautYEnnemis;
            unsigned int uiIndex;
            unsigned int uiEnnemisParLignes;
            unsigned int uiNombreEnnemis;
            unsigned int uiNombreDeSautsEnnemis;
            unsigned int uiPosFinEnnemisType1;
            unsigned int uiPosFinEnnemisType2;
            unsigned int uiPosFinEnnemisType3;
        };

        struct SArmee TempStructureArmee;
		std::vector <SArmee> StructureArmee;

        //Structure décrivant un ennemi
        struct SEnnemi
        {
            unsigned int uiIndex;
            unsigned int uiPoints;
            float fTailleEnnemiX;
            float fTailleEnnemiY;
            std::string sTexture1;
            std::string sTexture2;
        };

        struct SEnnemi TempStructureEnnemi;
		std::vector <SEnnemi> StructureEnnemi;

        CXMLNiveau ();
	    ~CXMLNiveau ();

       //Chargement des données XML
	   bool Charger (const char* szFilename);

	   //Armee
       std::vector <SArmee> GetStrutureArmee ();

       //Ennemi
       std::vector <SEnnemi> GetStrutureEnnemi ();
};

#endif //XML_NIVEAU_H
