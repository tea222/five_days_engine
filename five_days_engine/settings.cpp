#include "settings.h"


// TODO: if i decide to continue working on this after the contest, this should all be reworked


// declare every static variable
sf::VideoMode settings::videomode;
unsigned int settings::windowStyle;
std::string settings::windowTitle;
float settings::baseUiSizeUnit;
sf::Color settings::buttonColorNormal;
sf::Color settings::buttonColorHover;
sf::Color settings::buttonColorPressed;
sf::Color settings::buttonOutlineColor;
float settings::buttonOutlineThickness;
sf::Vector2f settings::buttonSize;
sf::Font settings::font;

void settings::load()
{
#ifdef RELEASE
    windowStyle = sf::Style::Fullscreen;
    videomode = sf::VideoMode::getFullscreenModes().at(0);          // native resolution
#else
    windowStyle = sf::Style::Default;
    videomode = sf::VideoMode(1280, 720, 32);                       // 720p
#endif
    windowTitle = "five_days_engine";
    baseUiSizeUnit = videomode.height / 20.0f;                      // 1/20 window height
    buttonColorNormal = sf::Color(255, 255, 255, 50);
    buttonColorHover = sf::Color(255, 255, 255, 100);
    buttonColorPressed = sf::Color(255, 255, 255, 150);
    buttonOutlineColor = sf::Color(255, 255, 255, 30);
    buttonSize = sf::Vector2f(baseUiSizeUnit * 6, baseUiSizeUnit);
    buttonOutlineThickness = baseUiSizeUnit / 10.0f;                // 1/10 base ui size unit

    font.loadFromFile("Resources/OnestRegular1602-hint.ttf");
}
