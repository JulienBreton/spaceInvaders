#include "xml_niveau.h"
//#include "../MMGR/mmgr.h"

//==============================================================================
CXMLNiveau::CXMLNiveau ()
{

}
//==============================================================================
// On libère les données sauvées dans les différents dictionnaires.
// En fait, la plus part des données dynamiques sont sauvés ici car elles proviennent du fichier XML
CXMLNiveau::~CXMLNiveau ()
{
    StructureArmee.clear ();
}
//==============================================================================
// Chargement du fichier XML contenant les niveaux
bool CXMLNiveau::Charger (const char* szFilename)
{
    bool bOuvertureOK = true;

    xmlInitParser();

    // Parse le document XML et créé l'arbre DOM
	xmlDoc* pDocument = NULL;
	pDocument = xmlParseFile (szFilename);

    if (pDocument == NULL)
    bOuvertureOK = false;

    //Validation du document XML avec sa DTD
	if (!Validation (pDocument))
	{
		xmlFreeDoc (pDocument);
		xmlCleanupParser();
		bOuvertureOK = false;
		return bOuvertureOK;
	}

	// Récupère l'élément racine du document
	xmlNode* pJeu = xmlDocGetRootElement (pDocument);
	if ((!xmlStrcmp (pJeu->name, (const xmlChar *)"jeu")))
		Jeu (pJeu);

    // Libère la mémoire réservé pour l'arbre DOM
    xmlFreeDoc(pDocument);
    xmlCleanupParser();

    return bOuvertureOK;
}
//==============================================================================
//Validation du document XML avec sa DTD
bool CXMLNiveau::Validation (xmlDoc* pDocument)
{
	// Création d'un contexte de validation pour la sortie des erreurs
	xmlValidCtxt Contexte;
	Contexte.userData = (void *) stderr;
	Contexte.error    = (xmlValidityErrorFunc) fprintf;
	Contexte.warning  = (xmlValidityWarningFunc) fprintf;

	return xmlValidateDocument (&Contexte, pDocument) == 1;
}
//==============================================================================
//Parcours un élément 'jeu'
void CXMLNiveau::Jeu (xmlNode* pNode)
{
	// Parcours des éléments fils
	xmlNode* pChild = pNode->children;
	if (pChild)
	{
		do
		{
			if (pChild->type == XML_ELEMENT_NODE)
			{
				if ((!xmlStrcmp (pChild->name, (const xmlChar *)"armee")))
					Armee (pChild);
				else if ((!xmlStrcmp (pChild->name, (const xmlChar *)"ennemi")))
					Ennemi (pChild);
                else if ((!xmlStrcmp (pChild->name, (const xmlChar *)"armeEnnemie")))
					ArmeEnnemie (pChild);
			}
		}
		while ((pChild = pChild->next) != 0);
	}
}
//==============================================================================
//Parcours un élement 'armee'
void CXMLNiveau::Armee (xmlNode* pNode)
{
	//Parcours des attributs
	xmlAttribute* pAttribute = ((xmlElement*) pNode)->attributes;
	if (pAttribute)
	{
		do
		{
			if (pAttribute->type == XML_ATTRIBUTE_NODE)
			{
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Index")))
					TempStructureArmee.uiIndex = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"VitesseArmeeY")))
					TempStructureArmee.fVitesseArmeeY = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"DepartArmeeX")))
					TempStructureArmee.fDepartArmeeX = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"DepartArmeeY")))
					TempStructureArmee.fDepartArmeeY = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"DebutCourseX")))
					TempStructureArmee.fDebutCourseX = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"FinCourseY")))
					TempStructureArmee.fFinCourseY = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"EnnemisParlignes")))
					TempStructureArmee.uiEnnemisParLignes = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"EspaceY_EntreEnnemis")))
					TempStructureArmee.fEspaceY_EntreEnnemis = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"NombreDeSautsEnnemis")))
					TempStructureArmee.uiNombreDeSautsEnnemis = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"HauteurSautYEnnemis")))
					TempStructureArmee.fHauteurSautYEnnemis = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"NombreEnnemis")))
					TempStructureArmee.uiNombreEnnemis = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"PosFinEnnemisType1")))
					TempStructureArmee.uiPosFinEnnemisType1 = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"PosFinEnnemisType2")))
					TempStructureArmee.uiPosFinEnnemisType2 = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"PosFinEnnemisType3")))
					TempStructureArmee.uiPosFinEnnemisType3 = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Acceleration")))
					TempStructureArmee.fAcceleration = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
			}
		}
		while ((pAttribute = (xmlAttribute*) pAttribute->next) != 0);

        StructureArmee.push_back (TempStructureArmee);
	}
}
//==============================================================================
//Parcours un élement 'ennemi'
void CXMLNiveau::Ennemi (xmlNode* pNode)
{
	// Parcours des attributs
	xmlAttribute* pAttribute = ((xmlElement*) pNode)->attributes;
	if (pAttribute)
	{
		do
		{
			if (pAttribute->type == XML_ATTRIBUTE_NODE)
			{
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Index")))
					TempStructureEnnemi.uiIndex = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Points")))
					TempStructureEnnemi.uiPoints = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Texture1")))
					TempStructureEnnemi.sTexture1 = (const char*) xmlGetProp (pNode, pAttribute->name);
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"Texture2")))
					TempStructureEnnemi.sTexture2 = (const char*) xmlGetProp (pNode, pAttribute->name);
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"TailleEnnemiX")))
					TempStructureEnnemi.fTailleEnnemiX = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"TailleEnnemiY")))
					TempStructureEnnemi.fTailleEnnemiY = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
			}
		}
		while ((pAttribute = (xmlAttribute*) pAttribute->next) != 0);

        StructureEnnemi.push_back(TempStructureEnnemi);
	}
}
//==============================================================================
//Parcours un élement 'armeeEnnemie'
void CXMLNiveau::ArmeEnnemie (xmlNode* pNode)
{
	// Parcours des attributs
	xmlAttribute* pAttribute = ((xmlElement*) pNode)->attributes;
	if (pAttribute)
	{
		do
		{
			if (pAttribute->type == XML_ATTRIBUTE_NODE)
			{
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"VitesseTirEnnemiY")))
					StructureArmeEnnemie.fVitesseTirEnnemiY = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"TailleTirEnnemi")))
					StructureArmeEnnemie.fTailleTirEnnemi= atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"NbParticulesTirEnnemi")))
					StructureArmeEnnemie.uiNbParticulesTirEnnemi = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"EspaceY_EntreParticulesTirEnnemi")))
					StructureArmeEnnemie.fEspaceY_EntreParticulesTirEnnemi = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"TempsReinitParticulesTirEnnemi")))
					StructureArmeEnnemie.fTempsReinitParticulesTirEnnemi = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
				if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"DureeVieParticulesTirEnnemi")))
					StructureArmeEnnemie.fDureeVieParticulesTirEnnemi = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
                if ((!xmlStrcmp (pAttribute->name, (const xmlChar *)"DepartY_ParticulesTirEnnemi")))
					StructureArmeEnnemie.fDepartY_ParticulesTirEnnemi = atoi ((const char*) xmlGetProp (pNode, pAttribute->name));
			}
		}
		while ((pAttribute = (xmlAttribute*) pAttribute->next) != 0);
	}
}
//==============================================================================
std::vector <CXMLNiveau::SArmee> CXMLNiveau::GetStrutureArmee ()
{
    return StructureArmee;
}
//==============================================================================
std::vector <CXMLNiveau::SEnnemi> CXMLNiveau::GetStrutureEnnemi ()
{
    return StructureEnnemi;
}
//==============================================================================

