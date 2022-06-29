#include "GlobalSettings.h"

// TODO: if i decide to continue working on this after the contest, this should all be read from file 
GlobalSettings::GlobalSettings()
#ifdef RELEASE
    : windowStyle(sf::Style::Fullscreen)
    , videomode(sf::VideoMode::getFullscreenModes().at(0))  // native resolution
#else
    : windowStyle(sf::Style::Default)
    , videomode(1280, 720, 32)                              // 720p
#endif
    , windowTitle("five_days_engine")
    , baseUiSizeUnit(videomode.height / 20.0f)              // 1/20 window height
    , buttonColorNormal(sf::Color(255, 255, 255, 50))
    , buttonColorHover(sf::Color(255, 255, 255, 100))
    , buttonColorPressed(sf::Color(255, 255, 255, 150))
    , buttonOutlineColor(sf::Color(255, 255, 255, 30))
    , buttonSize(baseUiSizeUnit * 6, baseUiSizeUnit)
    , buttonOutlineThickness(baseUiSizeUnit / 10.0f)        // 1/10 base ui size unit
{
    font.loadFromFile("Resources/OnestRegular1602-hint.ttf");
}
