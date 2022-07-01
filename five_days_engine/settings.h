#pragma once

#include <codecvt>
#include <cassert>
#include <fstream>

#include "SFML/Graphics.hpp"

//#define RELEASE

static class Settings
{
private:
    // window
    sf::VideoMode   _videomode;
    unsigned int    _windowStyle;
    std::string     _windowTitle;
    float           _baseUiSizeUnit;
    unsigned int    _characterSize;

    // design
    sf::Color       _buttonColorNormal;
    sf::Color       _buttonColorHover;
    sf::Color       _buttonColorPressed;
    sf::Color       _buttonOutlineColor;
    float           _buttonOutlineThickness;
    sf::Vector2f    _buttonSize;
    bool            _verticalSyncEnabled;

    //gameplay
    // ..nothing yet

    // resources
    sf::Font _font;

    void updateWindowParameters();

public:
    Settings();
    virtual ~Settings();

    void load();

    // getters
    const sf::VideoMode&    getVideomode();
    unsigned int            getWindowStyle();
    const std::string&      getWindowTitle();
    float                   getBaseUiSizeUnit();
    unsigned int            getCharacterSize();

    const sf::Color&        getButtonColorNormal();
    const sf::Color&        getButtonColorHover();
    const sf::Color&        getButtonColorPressed();
    const sf::Color&        getButtonOutlineColor();
    float                   getButtonOutlineThickness();
    const sf::Vector2f&     getButtonSize();
    bool                    getVerticalSyncEnabled();

    sf::Font&               getFont();

    // setters
    void                    setVideomode(const sf::VideoMode& videoMode);
    void                    setWindowStyle(unsigned int style);
    void                    setVerticalSyncEnabled(bool enabled);
} s;

