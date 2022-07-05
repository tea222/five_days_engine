#include "World.h"

sf::Vector2f World::_tileSize(0.0f, 0.0f);

World::World()
{
}

World::~World()
{
}

void World::updateTileSize()
{
    _tileSize = Settings::getTileSize();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
