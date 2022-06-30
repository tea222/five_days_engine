#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "settings.h"

class Core
{
private:


public:
    std::wstring convertToWString(std::string str);
    std::wstring getResolutionStrFromVideoMode(sf::VideoMode& videoMode);
};

