#include "Button.h"

Button::Button(const sf::Vector2u& position, const std::wstring& title, const std::function<void()>& callback)
    : _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    // init rect
    _rect.setPosition(sf::Vector2f(position.x * Settings::getBaseUiSizeUnit(), position.y * Settings::getBaseUiSizeUnit()));
    _rect.setSize(Settings::getButtonSize());
    _rect.setOutlineColor(Settings::getButtonOutlineColor());
    _rect.setOutlineThickness(Settings::getButtonOutlineThickness());

    // init text
    _text.setFont(Settings::getFont());
    _text.setCharacterSize(Settings::getCharacterSize());
    _text.setString(title);
    sf::Vector2f rectSize = _rect.getSize();
    sf::Vector2f rectPos = _rect.getPosition();
    _text.setPosition(rectSize.x / 2.0f + rectPos.x, rectSize.y  / 2.0f + rectPos.y);
    sf::FloatRect textBounds = _text.getGlobalBounds();
    _text.setOrigin(textBounds.width / 2.0f, _text.getCharacterSize() / 1.5f);
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
            _rect.setFillColor(Settings::getButtonColorPressed());
        }
        else {
            // if it was pressed and now its not
            if (_isPressed) {
                _callback();
            }
            _isPressed = false;
            _rect.setFillColor(Settings::getButtonColorHover());
        }
    }
    else
    {
        _isPressed = false;
        _rect.setFillColor(Settings::getButtonColorNormal());
    }

    window.draw(_rect);
    window.draw(_text);
}

sf::Vector2u Button::getPosition()
{
    return _position;
}
