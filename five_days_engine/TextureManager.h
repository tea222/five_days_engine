#pragma once

#include <fstream>
#include <cassert>
#include "SFML/Graphics.hpp"

class TextureManager
{
private:
    static std::vector<sf::Texture*> _textures;

public:
    static void loadAll();

    // @param id : position of the required texture's path in settings/texture_paths.txt, starting at 0
    static sf::Texture* getTexture(unsigned id);
};

