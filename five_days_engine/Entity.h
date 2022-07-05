#pragma once

#include "SFML/Graphics.hpp"
#include "IEventsListener.h"

class Entity
    : public sf::Drawable
    , public IEventsListener
{
protected:

    sf::RectangleShape _rect;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    float _speed; // speed in px/sec
    float _health;

public:
    Entity();
    virtual ~Entity();

    virtual void die();
    virtual void update(float delta) = 0;
    virtual void updateMovement() = 0;
    virtual const sf::Vector2f& getPosition();
    virtual void setPosition(const sf::Vector2f& pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

