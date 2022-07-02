#include "Button.h"

Button::Button(const sf::Vector2u& position, const std::wstring& title, const std::function<void()>& callback, std::vector<std::string> additionalTitles)
    : _position(position)
    , _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    // init rect
    _rect.setSize(Settings::getButtonSize());
    _rect.setOutlineColor(Settings::getButtonOutlineColor());
    _rect.setOutlineThickness(Settings::getButtonOutlineThickness());

    // init text
    _text.setFont(Settings::getFont());
    _text.setString(title);
}

Button::~Button() {
}

void Button::updateAndDraw(sf::RenderWindow& window)
{
    // normalize position and size

    // rectangle
    _rect.setSize(Settings::getButtonSize());
    _rect.setPosition(_position.x * Settings::getUiMapCellSize().x, _position.y * Settings::getUiMapCellSize().y);
    _rect.setOutlineThickness(Settings::getButtonOutlineThickness());

    //text
    _text.setCharacterSize(Settings::getCharacterSize());
    sf::Vector2f rectSize = _rect.getSize();
    sf::Vector2f rectPos = _rect.getPosition();
    _text.setPosition(rectSize.x / 2.0f + rectPos.x, rectSize.y / 2.0f + rectPos.y);
    sf::FloatRect textBounds = _text.getGlobalBounds();
    _text.setOrigin(textBounds.width / 2.0f, _text.getCharacterSize() / 1.5f);

    // update button state

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

    // render

    window.draw(_rect);
    window.draw(_text);
}
