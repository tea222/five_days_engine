#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
}

void Player::init()
{
    _rect.setTexture(TextureManager::getTexture(TextureType::PLAYER_RED_THING));
}

void Player::update(float delta)
{
    bool blockControls = _currentAnimation == Animation::DIE || _currentAnimation == Animation::HIT;

    // update velocity
    _lastVelocityUpdateTimer += delta;
    if (_lastVelocityUpdateTimer >= _velocityUpdatesDelay) {
        if (!blockControls) {
            updateVelocity();
        }
        _lastVelocityUpdateTimer = 0.0f;
    }

    // update position
    updatePosition(delta);

    // update control
    if (!blockControls) {
        updateControl();
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
    sf::IntRect intRect = _rect.getTextureRect();

    Direction dir = getDirection();
    int currentFrame = intRect.left / ENTITY_SIZE;

    if (dir != Direction::NONE){ // if player is moving somewhere
        _currentAnimation = Animation::WALK;
        intRect.top = (int)dir * ENTITY_SIZE; // update direction
    }
    else if (_currentAnimation == Animation::WALK || _currentAnimation == Animation::WALK_R) {
         _currentAnimation = Animation::DEFAULT;
    }
    
    if (_currentAnimation != Animation::DEFAULT_R && _currentAnimation != Animation::WALK_R){
        currentFrame++;
    }
    else {
        currentFrame--;
    }

    switch (_currentAnimation)
    {
    case Entity::Animation::DEFAULT:
        if (currentFrame < _animStandBegin || currentFrame > _animStandEnd) currentFrame = _animStandBegin;
        else if (currentFrame == _animStandEnd) _currentAnimation = Animation::DEFAULT_R;
        break;
    case Entity::Animation::WALK:
        if (currentFrame < _animWalkBegin || currentFrame > _animWalkEnd) currentFrame = _animWalkBegin;
        else if (currentFrame == _animWalkEnd) _currentAnimation = Animation::WALK_R;
        break;
    case Entity::Animation::HIT:
        if (currentFrame < _animHitBegin || currentFrame > _animHitEnd) currentFrame = _animHitBegin;
        else if (currentFrame == _animHitEnd) _currentAnimation = Animation::DEFAULT;
        break;
    case Entity::Animation::DEFENCE:
        if (currentFrame < _animDefenceBegin) currentFrame = _animDefenceBegin;
        else if (currentFrame == _animDefenceEnd) _currentAnimation = Animation::DEFAULT;
        break;
    case Entity::Animation::DIE:
        if (currentFrame < _animDieBegin) currentFrame = _animDieBegin;
        else if (currentFrame > _animDieEnd) currentFrame = _animDieEnd;
        break;
    case Entity::Animation::DEFAULT_R:
        if (currentFrame == _animStandBegin) _currentAnimation = Animation::DEFAULT;
        break;
    case Entity::Animation::WALK_R:
        if (currentFrame == _animWalkBegin) _currentAnimation = Animation::WALK;
        break;
    default:
        break;
    }

    intRect.left = currentFrame * ENTITY_SIZE;

    _rect.setTextureRect(intRect);
}

void Player::updateControl()
{
    // switch weapon
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
    _rect.setTexture(TextureManager::getTexture(TextureType::PLAYER_STAFF));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
    _rect.setTexture(TextureManager::getTexture(TextureType::PLAYER_RED_THING));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
    _rect.setTexture(TextureManager::getTexture(TextureType::PLAYER_PURPLE_THING));
    }

    // attack
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        _currentAnimation = Animation::HIT;
    }



    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        die();
    }
}

void Player::onEvent(EventType eType, std::vector<void*> params)
{
}
