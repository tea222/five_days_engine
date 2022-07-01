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
    
private:

    sf::Vector2u _position;
    std::function<void()> _callback;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::RectangleShape _rect;
    sf::Text _text;
};

