#include "Button.h"

Button::Button(sf::Vector2u position, std::string title, std::function<void()> callback) 
    : _title(title)
    , _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    // init rect
    _rect.setPosition(sf::Vector2f(position.x * settings::baseUiSizeUnit, position.y * settings::baseUiSizeUnit));
    _rect.setSize(settings::buttonSize);
    _rect.setOutlineColor(settings::buttonOutlineColor);
    _rect.setOutlineThickness(settings::buttonOutlineThickness);

    // init text
    _text.setFont(settings::font);
    _text.setCharacterSize(settings::characterSize);
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
            _rect.setFillColor(settings::buttonColorPressed);
        }
        else {
            // if it was pressed and now its not
            if (_isPressed) {
                _callback();
            }
            _isPressed = false;
            _rect.setFillColor(settings::buttonColorHover);
        }
    }
    else
    {
        _isPressed = false;
        _rect.setFillColor(settings::buttonColorNormal);
    }

    window.draw(_rect);
    window.draw(_text);
}
