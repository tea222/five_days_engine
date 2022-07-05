#include "Entity.h"

Entity::Entity()
    : _speed(0.0f)
    , _health(0)
    , _velocity(0.0f, 0.0f)
{
}

Entity::~Entity()
{
}

void Entity::die()
{
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
