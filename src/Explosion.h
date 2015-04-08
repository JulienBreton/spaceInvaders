#ifndef __EXPLOSIONS_H
#define __EXPLOSIONS_H

//Includes
#include "Particules.h"

class CExplosion
{
	private:

    public:

        CParticules * pParticulesExplosion;

        void Explosion();

        CExplosion()
            {
                pParticulesExplosion = 0;

                if (pParticulesExplosion == 0)
                {
                    pParticulesExplosion = new CParticules;
                }
            }

        ~CExplosion()
            {
                if (pParticulesExplosion != 0)
                {
                    delete pParticulesExplosion;
                    pParticulesExplosion = 0;
                }
            }
};

#endif

