#pragma once

#include "SFML/Graphics.hpp"
#include "IEventsListener.h"
#include "TextureManager.h"

class Entity
    : public sf::Drawable
    , public IEventsListener
{
protected:

    sf::RectangleShape _rect;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    float _speed; // speed in px/sec

    float _velocityUpdatesDelay; // delay between velocity updates in seconds
    float _lastVelocityUpdateTimer; // time since last velocity update in seconds

    float _frameUpdatesDelay; // delay between frame updates in seconds
    float _lastFrameUpdateTimer; // time since last frame update in seconds

    float _health;
    virtual void updateFrame() = 0;
    virtual void updateVelocity() = 0;
    virtual void updatePosition(float delta);

public:
    Entity();
    virtual ~Entity();

    virtual void die();
    virtual void update(float delta) = 0;
    virtual const sf::Vector2f& getPosition();
    virtual void setPosition(const sf::Vector2f& pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

