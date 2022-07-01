#include "Button.h"

sf::Vector2f Button::_size(0.0f, 0.0f);
unsigned Button::_characterSize(0);
sf::Color Button::_colorNormal(sf::Color::Black);
sf::Color Button::_colorHover(sf::Color::Black);
sf::Color Button::_colorPressed(sf::Color::Black);
sf::Color Button::_outlineColor(sf::Color::Black);
float Button::_outlineThickness(0.0f);
float Button::_baseUiSizeUnit(0.0f);
const sf::Font* Button::_font(nullptr);

Button::Button(const sf::Vector2u& position, const std::wstring& title, const std::function<void()>& callback)
    : _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
{
    s.setVerticalSyncEnabled(false);
    // init rect
    _rect.setPosition(sf::Vector2f(position.x * _baseUiSizeUnit, position.y * _baseUiSizeUnit));
    _rect.setSize(_size);
    _rect.setOutlineColor(_outlineColor);
    _rect.setOutlineThickness(_outlineThickness);

    // init text
    _text.setFont(*_font);
    _text.setCharacterSize(_characterSize);
    _text.setString(title);
    sf::Vector2f rectSize = _rect.getSize();
    sf::Vector2f rectPos = _rect.getPosition();
    _text.setPosition(rectSize.x / 2.0f + rectPos.x, rectSize.y  / 2.0f + rectPos.y);
    sf::FloatRect textBounds = _text.getGlobalBounds();
    _text.setOrigin(textBounds.width / 2.0f, _characterSize / 1.5f);
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
            _rect.setFillColor(_colorPressed);
        }
        else {
            // if it was pressed and now its not
            if (_isPressed) {
                _callback();
            }
            _isPressed = false;
            _rect.setFillColor(_colorHover);
        }
    }
    else
    {
        _isPressed = false;
        _rect.setFillColor(_colorNormal);
    }

    window.draw(_rect);
    window.draw(_text);
}

void Button::setButtonsParameters(const sf::Vector2f& size, unsigned characterSize, const sf::Color& colorNormal, const sf::Color& colorHover,
    const sf::Color& colorPressed, const sf::Color& outlineColor, float outlineThickness, float baseUiSizeUnit, const sf::Font& font)
{
    _size = size;
    _characterSize = characterSize;
    _colorNormal = colorNormal;
    _colorHover = colorHover;
    _colorPressed = colorPressed;
    _outlineColor = outlineColor;
    _outlineThickness = outlineThickness;
    _baseUiSizeUnit = baseUiSizeUnit;
    _font = &font;
}

sf::Vector2u Button::getPosition()
{
    return _position;
}
