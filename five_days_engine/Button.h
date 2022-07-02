#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "Settings.h"

class Button
{
public:
    Button(const sf::Vector2u& position, const std::wstring& title, const std::function<void()>& callback, std::vector<std::string> additionalTitles = { });
    virtual ~Button();

    void updateAndDraw(sf::RenderWindow& window);
    
private:

    std::vector<std::wstring> _additionalTitles;
    sf::Vector2u _position;
    std::function<void()> _callback;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::ConvexShape _convex;
    sf::Text _text;

    void updateConvexPoints();
};

