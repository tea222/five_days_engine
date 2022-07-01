#include "Settings.h"

sf::VideoMode   Settings::_videomode                = sf::VideoMode::getDesktopMode();
unsigned int    Settings::_windowStyle              = sf::Style::Default;
std::string     Settings::_windowTitle              = "";
float           Settings::_baseUiSizeUnit           = 0.0f;
unsigned int    Settings::_characterSize            = 0;
sf::Color       Settings::_buttonColorNormal        = sf::Color::Black;
sf::Color       Settings::_buttonColorHover         = sf::Color::Black;
sf::Color       Settings::_buttonColorPressed       = sf::Color::Black;
sf::Color       Settings::_buttonOutlineColor       = sf::Color::Black;
float           Settings::_buttonOutlineThickness   = 0.0f;
sf::Vector2f    Settings::_buttonSize               = sf::Vector2f(0.0f, 0.0f);
bool            Settings::_verticalSyncEnabled      = false;
sf::Font        Settings::_font;

// TODO: if i decide to work on this engine after the contest, this shoud all be read from file
void Settings::load()
{
#ifdef RELEASE
    _windowStyle            = sf::Style::Fullscreen;
    _videomode              = sf::VideoMode::getDesktopMode();  // native resolution
#else
    _windowStyle            = sf::Style::Default;
    _videomode              = sf::VideoMode(1280, 720, 32);     // 720p
#endif
    _windowTitle            = "five_days_engine";
    _buttonColorNormal      = sf::Color(255, 255, 255, 50);
    _buttonColorHover       = sf::Color(255, 255, 255, 100);
    _buttonColorPressed     = sf::Color(255, 255, 255, 150);
    _buttonOutlineColor     = sf::Color(255, 255, 255, 30);
    _verticalSyncEnabled    = true;

    updateWindowParameters();

    _font.loadFromFile("Resources/OnestRegular1602-hint.ttf");
}

const sf::VideoMode& Settings::getVideomode()
{
    return _videomode;
}

unsigned int Settings::getWindowStyle()
{
    return _windowStyle;
}

const std::string& Settings::getWindowTitle()
{
    return _windowTitle;
}

float Settings::getBaseUiSizeUnit()
{
    return _baseUiSizeUnit;
}

unsigned int Settings::getCharacterSize()
{
    return _characterSize;
}

const sf::Color& Settings::getButtonColorNormal()
{
    return _buttonColorNormal;
}

const sf::Color& Settings::getButtonColorHover()
{
    return _buttonColorHover;
}

const sf::Color& Settings::getButtonColorPressed()
{
    return _buttonColorPressed;
}

const sf::Color& Settings::getButtonOutlineColor()
{
    return _buttonOutlineColor;
}

float Settings::getButtonOutlineThickness()
{
    return _buttonOutlineThickness;
}

const sf::Vector2f& Settings::getButtonSize()
{
    return _buttonSize;
}

bool Settings::getVerticalSyncEnabled()
{
    return _verticalSyncEnabled;
}

sf::Font& Settings::getFont()
{
    return _font;
}

void Settings::setVideomode(const sf::VideoMode& videoMode)
{
    _videomode = videoMode;

    updateWindowParameters();
}

void Settings::setWindowStyle(unsigned int style)
{
    _windowStyle = style;
}

void Settings::setVerticalSyncEnabled(bool enabled)
{
    _verticalSyncEnabled = enabled;
}

void Settings::updateWindowParameters()
{
    _baseUiSizeUnit = _videomode.height / 20.0f;                        // 1/20 window height
    _buttonSize = sf::Vector2f(_baseUiSizeUnit * 7, _baseUiSizeUnit);
    _buttonOutlineThickness = _baseUiSizeUnit / 10.0f;                  // 1/10 base ui size unit
    _characterSize = static_cast<unsigned>(_baseUiSizeUnit / 1.25f);    // 4/5  base ui size unit
}