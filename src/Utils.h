#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <sstream>

class CUtils
{
    private:

    public:
            //Conveterti un float en string
            std::string ConvertirFloatEnString (float ValeurFloatAConvertir);
            //Recherche d'un nombre flottant 'al�atoirement'
            float RandFloat (float fMin, float fMax);
};

#endif

