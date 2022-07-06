#include "TextureManager.h"

std::vector<sf::Texture*> TextureManager::_textures;

void TextureManager::loadAll()
{
    _textures.clear();

    std::ifstream file;
    file.open("settings/texture_paths.txt");

    assert(file.good());

    std::string currentStr;
    while (std::getline(file, currentStr)) {
        sf::Texture* texture = new sf::Texture;
        assert(texture->loadFromFile(currentStr));
        _textures.push_back(texture);
    }
    file.close();
}

sf::Texture* TextureManager::getTexture(TextureType type)
{
    return _textures.at(static_cast<unsigned>(type));
}
