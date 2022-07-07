#pragma once

#include <fstream>
#include "SFML/Graphics.hpp"

enum class TextureType {
    BACKGROUND = 0,
    PLAYER_STAFF,
    PLAYER_RED_THING,
    PLAYER_PURPLE_THING
};

class TextureManager
{
private:
    static std::vector<sf::Texture*> _textures;

public:
    static void loadAll();

    // @param id : position of the required texture's path in settings/texture_paths.txt, starting at 0
    static sf::Texture* getTexture(TextureType type);
};

