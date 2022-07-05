#pragma once

#include "SFML/Graphics.hpp"
#include "Settings.h"

class World
    : public sf::Drawable
{
protected:
    static sf::Vector2f _tileSize;
    
public:

    World();
    virtual ~World();

    static void updateTileSize();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

