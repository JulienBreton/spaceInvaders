#ifndef SONS_H
#define SONS_H

#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>

class CSons
{
        public:

                CSons ();
                ~CSons ();

                 bool ChargerSon (std::string sSonACharger, sf::SoundBuffer& BufferSonACharger);
                 void JouerSon (sf::Sound& Sound);

        private:

};

#endif
