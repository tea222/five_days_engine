#pragma once
#include "SFML/Graphics.hpp"

//#define RELEASE

struct GlobalSettings
{
    GlobalSettings();

    // window
    const sf::VideoMode videomode;
    const unsigned int windowStyle;
    const std::string windowTitle;
    const float baseUiSizeUnit;

    // design
    const sf::Color buttonColorNormal;
    const sf::Color buttonColorHover;
    const sf::Color buttonColorPressed;
    const sf::Color buttonOutlineColor;
    const float buttonOutlineThickness;
    const sf::Vector2f buttonSize;

    //gameplay
    // ..nothing yet

    // resources
    sf::Font font;

} static s;

