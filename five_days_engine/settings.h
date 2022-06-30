#pragma once

#include <codecvt>
#include <fstream>

#include "SFML/Graphics.hpp"

//#define RELEASE

enum class Line {
    // main and pouse menu 
    PLAY,
    CONTINUE,
    SETTINGS,
    EXIT,

    // settings 
    RESOLUTION,
    WINDOW_MODE_ON,
    WINDOW_MODE_OFF,
    VERTICAL_SYNC_ON,
    VERTICAL_SYNC_OFF,
    BACK
};

enum class ButtonType {
    // main and pause menu
    PLAY,
    CONTINUE,
    SETTINGS,
    EXIT,

    // settings 
    RESOLUTION,
    VERTICAL_SYNC,
    WINDOW_MODE,
    BACK
};

struct settings
{
    
    // window
    static sf::VideoMode videomode;
    static unsigned int windowStyle;
    static std::string windowTitle;
    static float baseUiSizeUnit;
    static unsigned int characterSize;

    // design
    static sf::Color buttonColorNormal;
    static sf::Color buttonColorHover;
    static sf::Color buttonColorPressed;
    static sf::Color buttonOutlineColor;
    static float buttonOutlineThickness;
    static sf::Vector2f buttonSize;
    static std::map<Line, std::wstring> lines;
    static bool enableVerticalSync;

    //gameplay
    // ..nothing yet

    // resources
    static sf::Font font;


    static void load();
    static void updateWindowSettings();
};

