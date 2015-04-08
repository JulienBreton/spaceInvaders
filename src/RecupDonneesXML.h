#ifndef __RECUPDONNEESXML_H
#define __RECUPDONNEESXML_H

#include "xml_niveau.h"

#define FICHIER_XML_NIVEAU "data/xml/niveau.xml"

class CRecupDonneesXML
{
        public:

            //Constructeur
            CRecupDonneesXML()
            {

            }

            //Destructeur
            ~CRecupDonneesXML()
            {

            }

            bool OuvrirFichierXML();

            //Armee
            std::vector <CXMLNiveau::SArmee> RecupStructureArmee ();

            //Ennemi
            std::vector <CXMLNiveau::SEnnemi> RecupStructureEnnemi ();

            //Ennemi
            float RecupTailleEnnemiX ();
            float RecupTailleEnnemiY ();

        private:

            bool m_bChargementFichier_XML_OK;

            //Instances
             CXMLNiveau m_iXMLNiveau;
};

#endif
