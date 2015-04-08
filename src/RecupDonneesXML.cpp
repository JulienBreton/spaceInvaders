#include "RecupDonneesXML.h"
//#include "../MMGR/mmgr.h"

//==============================================================================
bool CRecupDonneesXML::OuvrirFichierXML ()
{
    m_bChargementFichier_XML_OK = true;

    // Chargement des niveaux, en cas d'echec on renvoie une erreur.
    if (!m_iXMLNiveau.Charger ("data/xml/niveau.xml"))
		m_bChargementFichier_XML_OK = false;

	return m_bChargementFichier_XML_OK;
}
//==============================================================================
std::vector <CXMLNiveau::SArmee> CRecupDonneesXML::RecupStructureArmee ()
{
    return m_iXMLNiveau.GetStrutureArmee ();
}
//==============================================================================
std::vector <CXMLNiveau::SEnnemi> CRecupDonneesXML::RecupStructureEnnemi ()
{
    return m_iXMLNiveau.GetStrutureEnnemi ();
}
//==============================================================================


