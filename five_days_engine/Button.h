#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "Settings.h"

class Button
{
public:
    Button(const sf::Vector2u& position, const std::wstring &title, const std::function<void()> &callback);
    virtual ~Button();

    void updateAndDraw(sf::RenderWindow& window);

    sf::Vector2u getPosition();
    static void setButtonsParameters(const sf::Vector2f& size, unsigned characterSize, const sf::Color& colorNormal, const sf::Color& colorHover,
        const sf::Color& colorPressed, const sf::Color& outlineColor, float outlineThickness, float baseUiSizeUnit, const sf::Font& font);
    
private:

    sf::Vector2u _position;
    std::function<void()> _callback;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::RectangleShape _rect;
    sf::Text _text;

    // general buttons parameters
    static sf::Vector2f _size;
    static unsigned _characterSize;
    static sf::Color _colorNormal;
    static sf::Color _colorHover;
    static sf::Color _colorPressed;
    static sf::Color _outlineColor;
    static float _outlineThickness;
    static float _baseUiSizeUnit;
    static const sf::Font* _font;
};

