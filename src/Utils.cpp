#include "Utils.h"

#include <stdlib.h>

//Convertir un float en string
std::string CUtils::ConvertirFloatEnString (float fValeurFloatAConvertir)
{
    std::string sStringARetournee;
    std::stringstream ssFluxDeSortie;
    ssFluxDeSortie << fValeurFloatAConvertir;
    sStringARetournee = ssFluxDeSortie.str();

    return sStringARetournee;
}

// Recherche d'un nombre alléatoire flottant
float CUtils::RandFloat (float fMin, float fMax)
{
	return (rand () / (float)RAND_MAX * (fMax - fMin)) + fMin;
}
