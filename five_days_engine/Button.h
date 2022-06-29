#pragma once
#include <functional>
#include "SFML/Graphics.hpp"

#include "settings.h"

class Button
{
public:
    Button(sf::Vector2u position, std::string title, std::function<void()> callback);
    virtual ~Button();

    void updateAndDraw(sf::RenderWindow& window);
    
private:
    std::string _title;
    std::function<void()> _callback;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::RectangleShape _rect;
    sf::Text _text;
};

