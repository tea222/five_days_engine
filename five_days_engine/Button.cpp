#include "Button.h"

Button::Button(const sf::Vector2u& position, const std::wstring& title, ButtonCallback callback,
    bool useAdditionalLabel, const std::wstring& additionalLabelStr)
    : _type(ButtonType::CUSTOM)
    , _position(position)
    , _callback(callback) 
    , _isPressed(false)
    , _isHover(false)
    , _useAdditionalLabel(useAdditionalLabel)
{
    init(title, additionalLabelStr);
}

Button::Button(const sf::Vector2u& position, const std::wstring& title, ButtonType btnType, bool useAdditionalLabel, const std::wstring& additionalLabelStr)
    : _type(btnType)
    , _position(position)
    , _isPressed(false)
    , _isHover(false)
    , _useAdditionalLabel(useAdditionalLabel)
{
    init(title, additionalLabelStr);
}

Button::~Button() {
}

Button::ButtonType Button::getType()
{
    return _type;
}

void Button::setAdditionalLabelStr(const std::wstring& str)
{
    _additionalLabel.setString(str);
}

void Button::updateAndDraw(sf::RenderWindow& window)
{
    // normalize position and size

    // convex
    updateConvexPoints();
    _convex.setPosition(_position.x * Settings::getUiMapCellSize().x, _position.y * Settings::getUiMapCellSize().y);
    _convex.setOutlineThickness(Settings::getButtonOutlineThickness());

    sf::Vector2f buttonSize = Settings::getButtonSize();
    sf::Vector2f rectPos = _convex.getPosition();

    //text
    _title.setCharacterSize(Settings::getCharacterSize());
    sf::FloatRect textBounds = _title.getGlobalBounds();
    _title.setPosition(buttonSize.x / 2.0f + rectPos.x, buttonSize.y / 2.0f + rectPos.y);
    _title.setOrigin(textBounds.width / 2.0f, _title.getCharacterSize() / 1.5f);

    // additional label
    if (_useAdditionalLabel)
    {
        _additionalLabel.setCharacterSize(Settings::getCharacterSize());
        _additionalLabel.setPosition(buttonSize.x + rectPos.x + Settings::getButtonOutlineThickness() * 2.0f, buttonSize.y / 2.0f + rectPos.y);
        _additionalLabel.setOrigin(0.0f, _additionalLabel.getCharacterSize() / 1.5f);
    }

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
                if (_type == ButtonType::CUSTOM){
                    _callback(this);
                }
                else {
                    EventsController::notify(EventType::STOCK_BUTTON_PRESSED, {&_type, this});
                }
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
    window.draw(_title);
    if (_useAdditionalLabel)
    {
        window.draw(_additionalLabel);
    }
}

void Button::init(const std::wstring& title, const std::wstring& additionalLabelStr)
{
    // init convex
    _convex.setOutlineColor(Settings::getButtonOutlineColor());
    _convex.setOutlineThickness(Settings::getButtonOutlineThickness());
    _convex.setPointCount(6);
    updateConvexPoints();

    // init text
    _title.setFont(Settings::getFont());
    _title.setString(title);

    // init additional label
    _additionalLabel.setFont(Settings::getFont());
    _additionalLabel.setString(additionalLabelStr);
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
