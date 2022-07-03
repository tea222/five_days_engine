#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Player
    : public sf::Drawable
    , public Entity
{
private:
    sf::RectangleShape _rect;
    sf::Vector2f _direction;
    sf::Texture _texture;

public:
    virtual void update(float delta) override;

};

