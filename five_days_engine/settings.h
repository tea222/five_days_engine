#pragma once
#include "SFML/Graphics.hpp"

//#define RELEASE

struct settings
{
    
    // window
    static sf::VideoMode videomode;
    static unsigned int windowStyle;
    static std::string windowTitle;
    static float baseUiSizeUnit;

    // design
    static sf::Color buttonColorNormal;
    static sf::Color buttonColorHover;
    static sf::Color buttonColorPressed;
    static sf::Color buttonOutlineColor;
    static float buttonOutlineThickness;
    static sf::Vector2f buttonSize;

    //gameplay
    // ..nothing yet

    // resources
    static sf::Font font;


    static void load();
};

