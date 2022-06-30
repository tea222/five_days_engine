#pragma once

#include <codecvt>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "settings.h"
#include "Button.h"

enum class GameState {
    MENU,
    GAME
};

enum class SubMenu {
    MAIN,
    PAUSE,
    SETTINGS
};

class Core
{
private:
    sf::RenderWindow _window;
    GameState _currentState;
    SubMenu _currentSubMenu;
    bool _hasGameStarted;

    std::map<SubMenu, std::vector<Button>> _menuButtons;

    sf::Text _resolutionText;

    void createWindow();
    void initButtons();

public:
    Core();
    virtual ~Core();

    void launchApp();

    std::wstring convertToWString(std::string str);
    std::wstring getCurrentResolutionStr();
};

