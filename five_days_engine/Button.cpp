#include "Button.h"

Button::Button(const sf::Vector2u& position, const std::wstring& title, const std::function<void()>& callback, std::vector<std::string> additionalTitles)
    : _position(position)
    , _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    // init convex
    _convex.setOutlineColor(Settings::getButtonOutlineColor());
    _convex.setOutlineThickness(Settings::getButtonOutlineThickness());
    _convex.setPointCount(6);
    updateConvexPoints();

    // init text
    _text.setFont(Settings::getFont());
    _text.setString(title);
}

Button::~Button() {
}

void Button::updateAndDraw(sf::RenderWindow& window)
{
    // normalize position and size

    // convex
    updateConvexPoints();
    _convex.setPosition(_position.x * Settings::getUiMapCellSize().x, _position.y * Settings::getUiMapCellSize().y);
    _convex.setOutlineThickness(Settings::getButtonOutlineThickness());

    //text
    _text.setCharacterSize(Settings::getCharacterSize());
    sf::Vector2f buttonSize = Settings::getButtonSize();
    sf::Vector2f rectPos = _convex.getPosition();
    _text.setPosition(buttonSize.x / 2.0f + rectPos.x, buttonSize.y / 2.0f + rectPos.y);
    sf::FloatRect textBounds = _text.getGlobalBounds();
    _text.setOrigin(textBounds.width / 2.0f, _text.getCharacterSize() / 1.5f);

    // update button state

    // if mouse pointer is in the rect
    if (_convex.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
        // if left mouse button is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            _isPressed = true;
            _convex.setFillColor(Settings::getButtonColorPressed());
        }
        else {
            // if it was pressed and now its not
            if (_isPressed) {
                _callback();
            }
            _isPressed = false;
            _convex.setFillColor(Settings::getButtonColorHover());
        }
    }
    else
    {
        _isPressed = false;
        _convex.setFillColor(Settings::getButtonColorNormal());
    }

    // render

    window.draw(_convex);
    window.draw(_text);
}

void Button::updateConvexPoints()
{
    const sf::Vector2f& buttonSize = Settings::getButtonSize();
    float edge = buttonSize.y / 3.0f;

    _convex.setPoint(0, sf::Vector2f(0, edge));
    _convex.setPoint(1, sf::Vector2f(edge, 0));
    _convex.setPoint(2, sf::Vector2f(buttonSize.x, 0));
    _convex.setPoint(3, sf::Vector2f(buttonSize.x, buttonSize.y - edge));
    _convex.setPoint(4, sf::Vector2f(buttonSize.x - edge, buttonSize.y));
    _convex.setPoint(5, sf::Vector2f(0, buttonSize.y));
}
