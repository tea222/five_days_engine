#pragma once
#include <functional>
#include "SFML/Graphics.hpp"

#include "settings.h"

class Button
{
public:
    Button(ButtonType type, sf::Vector2u position, std::wstring &title, std::function<void()> callback);
    virtual ~Button();

    void updateAndDraw(sf::RenderWindow& window);
    void setTitle(std::wstring &title);
    ButtonType getType();
    
private:
    ButtonType _type;
    std::function<void()> _callback;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::RectangleShape _rect;
    sf::Text _text;
};

