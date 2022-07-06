#include "Player.h"

Player::Player()
{
    

}

Player::~Player()
{
}

void Player::init()
{
    _frameUpdatesDelay = 0.2f;
    _velocityUpdatesDelay = 0.05f;
    _speed = 300.0f;
    _rect.setSize(sf::Vector2f(50, 150));
    _rect.setTexture(TextureManager::getTexture(TextureType::PLAYER));
}

void Player::update(float delta)
{
    // update position
    updatePosition(delta);

    // update velocity
    _lastVelocityUpdateTimer += delta;
    if (_lastVelocityUpdateTimer >= _velocityUpdatesDelay) {
        updateVelocity();
        _lastVelocityUpdateTimer = 0.0f;
    }

    // update frame
    _lastFrameUpdateTimer += delta;
    if (_lastFrameUpdateTimer >= _frameUpdatesDelay) {
        updateFrame();
        _lastFrameUpdateTimer = 0.0f;
    }
}

void Player::updateVelocity()
{
    _velocity.x = 0.0f;
    _velocity.y = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        _velocity.y = -_speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        _velocity.y = _speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocity.x = -_speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocity.x = _speed;
    }
}

void Player::updateFrame()
{
}

void Player::onEvent(EventType eType, std::vector<void*> params)
{
}
