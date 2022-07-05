#include "Player.h"

Player::Player()
{
    _speed = 100.0f;
    _rect.setSize(sf::Vector2f(50, 150));
    _rect.setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

void Player::update(float delta)
{
    // update position
    const sf::Vector2f& currentPos = _rect.getPosition();
    _rect.setPosition(currentPos + _velocity * delta);
}

void Player::updateMovement()
{
    _velocity.x = 0.0f;
    _velocity.y = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        _velocity.y = -_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocity.x = -_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        _velocity.y = _speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocity.x = _speed;
    }
}

void Player::onEvent(EventType eType, std::vector<void*> params)
{
}
