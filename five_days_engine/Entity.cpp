#include "Entity.h"

Entity::Direction Entity::getDirection()
{
    Direction result = Direction::NONE;

    if (_velocity.x < 0.0f) { // west
        if (_velocity.y < 0.0f) {  // north west
            result = Direction::NW;
        }
        else if (_velocity.y > 0.0f) { // south west
            result = Direction::SW;
        }
        else { // just west
            result = Direction::W;
        }
    }
    else if (_velocity.x > 0.0f) { // east
        if (_velocity.y < 0.0f) {  // north east
            result = Direction::NE;
        }
        else if (_velocity.y > 0.0f) { // south east
            result = Direction::SE;
        }
        else { // just east
            result = Direction::E;
        }
    }
    else { // north or south
        if(_velocity.y > 0.0f){ // south
            result = Direction::S;
        }
        else if (_velocity.y < 0.0f) { // north
            result = Direction::N;
        }
    }
    return result;
}

void Entity::updatePosition(float delta)
{
    const sf::Vector2f& currentPos = _rect.getPosition();
    _rect.setPosition(currentPos + _velocity * delta);
}

Entity::Entity()
    // init with default values
    : _speed(300.0f)
    , _health(0)
    , _velocity(0.0f, 0.0f)
    , _currentAnimation(Animation::DEFAULT)
    , _velocityUpdatesDelay(0.05f)
    , _lastVelocityUpdateTimer(0.0f)
    , _frameUpdatesDelay(0.05f)
    , _lastFrameUpdateTimer(0.0f)
{
    _rect.setSize(sf::Vector2f(ENTITY_SIZE, ENTITY_SIZE));
    _rect.setOrigin(_rect.getSize() / 2.0f);
    _rect.setTextureRect(sf::IntRect(0, 0, ENTITY_SIZE, ENTITY_SIZE));
}

Entity::~Entity()
{
}

void Entity::die()
{
    _currentAnimation = Animation::DIE;
}

const sf::Vector2f& Entity::getPosition()
{
    return _rect.getPosition();
}

void Entity::setPosition(const sf::Vector2f& pos)
{
    _rect.setPosition(pos);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_rect);
}
