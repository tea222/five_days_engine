#pragma once

#include <codecvt>
#include <cassert>
#include <fstream>

#include "SFML/Graphics.hpp"

//#define RELEASE

class Settings
{
private:
    // window
    static sf::VideoMode   _videomode;
    static unsigned int    _windowStyle;
    static std::string     _windowTitle;
    static float           _baseUiSizeUnit;
    static unsigned int    _characterSize;

    // design
    static sf::Color       _buttonColorNormal;
    static sf::Color       _buttonColorHover;
    static sf::Color       _buttonColorPressed;
    static sf::Color       _buttonOutlineColor;
    static float           _buttonOutlineThickness;
    static sf::Vector2f    _buttonSize;
    static bool            _verticalSyncEnabled;

    //gameplay
    // ..nothing yet

    // resources
    static sf::Font _font;

    static void updateWindowParameters();

public:

    static void load();

    // getters
    static const sf::VideoMode& getVideomode();
    static unsigned int         getWindowStyle();
    static const std::string&   getWindowTitle();
    static float                getBaseUiSizeUnit();
    static unsigned int         getCharacterSize();

    static const sf::Color&     getButtonColorNormal();
    static const sf::Color&     getButtonColorHover();
    static const sf::Color&     getButtonColorPressed();
    static const sf::Color&     getButtonOutlineColor();
    static float                getButtonOutlineThickness();
    static const sf::Vector2f&  getButtonSize();
    static bool                 getVerticalSyncEnabled();

    static sf::Font&            getFont();

    // setters
    static void setVideomode(const sf::VideoMode& videoMode);
    static void setWindowStyle(unsigned int style);
    static void setVerticalSyncEnabled(bool enabled);
};

