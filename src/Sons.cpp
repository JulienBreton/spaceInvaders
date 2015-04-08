#include "Sons.h"

CSons::CSons ()
{

}

CSons::~CSons ()
{

}

bool CSons::ChargerSon (std::string sSonACharger, sf::SoundBuffer& BufferSonACharger)
{
    if (!BufferSonACharger.LoadFromFile(sSonACharger))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void CSons::JouerSon (sf::Sound& Sound)
{
    Sound.Play();
}
