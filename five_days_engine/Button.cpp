#include "Button.h"

Button::Button(sf::Vector2u position, std::string title, std::function<void()> callback) 
    : _position(position)
    , _title(title)
    , _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    // init rect
    _rect.setPosition(sf::Vector2f(position.x * s.baseUiSizeUnit, position.y * s.baseUiSizeUnit));
    _rect.setSize(s.buttonSize);
    _rect.setOutlineColor(s.buttonOutlineColor);
    _rect.setOutlineThickness(s.buttonOutlineThickness);

    // init text
    _text.setFont(s.font);
    _text.setString(title);
    sf::Vector2f rectSize = _rect.getSize();
    sf::Vector2f rectPos = _rect.getPosition();
    _text.setPosition(rectSize.x / 2.0f + rectPos.x, rectSize.y  / 2.0f + rectPos.y);
    sf::FloatRect textBounds = _text.getGlobalBounds();
    _text.setOrigin(textBounds.width / 2.0f, textBounds.height);
}

Button::~Button() {
}

void Button::updateAndDraw(sf::RenderWindow& window)
{
    // if mouse pointer is in the rect
    if (_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
        // if left mouse button is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            _isPressed = true;
            _rect.setFillColor(s.buttonColorPressed);
        }
        else {
            // if it was pressed and now its not
            if (_isPressed) {
                _callback();
            }
            _isPressed = false;
            _rect.setFillColor(s.buttonColorHover);
        }
    }
    else
    {
        _isPressed = false;
        _rect.setFillColor(s.buttonColorNormal);
    }

    window.draw(_rect);
    window.draw(_text);
}
