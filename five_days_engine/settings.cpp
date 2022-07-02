#include "Settings.h"

sf::VideoMode   Settings::_videomode                = sf::VideoMode::getDesktopMode();
unsigned int    Settings::_windowStyle              = sf::Style::Default;
std::string     Settings::_windowTitle              = "";
sf::Vector2f    Settings::_uiMapCellSize            = sf::Vector2f(0.0f, 0.0f);
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
    setVideomode(sf::VideoMode::getDesktopMode());  // native resolution
#else
    _windowStyle            = sf::Style::Default;
    setVideomode(sf::VideoMode(1280, 720, 32));     // 720p
#endif
    _windowTitle            = "five_days_engine";
    _buttonColorNormal      = sf::Color(255, 255, 255, 50);
    _buttonColorHover       = sf::Color(255, 255, 255, 100);
    _buttonColorPressed     = sf::Color(255, 255, 255, 150);
    _buttonOutlineColor     = sf::Color(255, 255, 255, 30);
    _verticalSyncEnabled    = true;

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

const sf::Vector2f& Settings::getUiMapCellSize()
{
    return _uiMapCellSize;
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

    _uiMapCellSize.x = _videomode.width / UI_MAP_SIZE.x;
    _uiMapCellSize.y = _videomode.height / UI_MAP_SIZE.y;
    _buttonSize = sf::Vector2f(_uiMapCellSize.x * 7, _uiMapCellSize.y);
    _buttonOutlineThickness = _uiMapCellSize.y / 10.0f;                 // 1/10 cell height
    _characterSize = static_cast<unsigned>(_uiMapCellSize.y / 1.25f);   // 4/5  cell height
}

void Settings::setWindowStyle(unsigned int style)
{
    _windowStyle = style;
}

void Settings::setVerticalSyncEnabled(bool enabled)
{
    _verticalSyncEnabled = enabled;
}