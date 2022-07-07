#pragma once

#include "SFML/Graphics.hpp"
#include "IEventsListener.h"
#include "TextureManager.h"

#define ENTITY_SIZE 256

class Entity
    : public sf::Drawable
    , public IEventsListener
{
protected:

    enum class Direction {
        NONE    = -1,
        W       = 0,
        NW      = 1,
        N       = 2,
        NE      = 3,
        E       = 4,
        SE      = 5,
        S       = 6,
        SW      = 7
    };

    

    sf::RectangleShape _rect;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    float _speed; // speed in px/sec

    float _velocityUpdatesDelay; // delay between velocity updates in seconds
    float _lastVelocityUpdateTimer; // time since last velocity update in seconds

    float _frameUpdatesDelay; // delay between frame updates in seconds
    float _lastFrameUpdateTimer; // time since last frame update in seconds

    enum class Animation {
        DEFAULT = 0,
        WALK,
        HIT,
        ATTACK,
        DEFENCE,
        DIE,

        // reversed animations
        DEFAULT_R,
        WALK_R
    };

    float _health;

    Animation _currentAnimation;

    Direction getDirection();
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

