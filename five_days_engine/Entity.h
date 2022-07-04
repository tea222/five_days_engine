#pragma once

#include "SFML/Graphics.hpp"

class Entity
    : public sf::Drawable
{
protected:

    sf::RectangleShape _rect;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    float _health;

public:
    Entity();
    virtual ~Entity();

    virtual void update(float delta) = 0;
    virtual const sf::Vector2f& getPosition();
    virtual void setPosition(const sf::Vector2f& pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

