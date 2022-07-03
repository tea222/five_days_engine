#pragma once

#include "SFML/Graphics.hpp"

class Entity
{
private:

    sf::Vector2f _velocity;
    float _health;

public:
    Entity();
    virtual ~Entity();

    virtual void update(float delta) = 0;

};

