#include "GestionAffichage.h"

float CGestionAffichage::GetElapsedTime (sf::RenderWindow& App)
{
        float fFramerate = 0.f;
        fFramerate  = 1.f / App.GetFrameTime();
        return fFramerate;
}
