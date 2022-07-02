#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "Settings.h"

class Button
{
public:
    using ButtonCallback = std::function<void(Button*)>;

    Button(const sf::Vector2u& position, const std::wstring& title, ButtonCallback callback,
        bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());
    virtual ~Button();

    void setAdditionalLabelStr(const std::wstring& str);
    void updateAndDraw(sf::RenderWindow& window);
    
private:

    sf::Vector2u _position;
    ButtonCallback _callback;
    const bool _useAdditionalLabel;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::ConvexShape _convex;
    sf::Text _title;
    sf::Text _additionalLabel;

    void updateConvexPoints();
};

