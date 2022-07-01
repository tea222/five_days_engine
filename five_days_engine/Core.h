#pragma once

#include <codecvt>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Settings.h"
#include "Button.h"

enum class GameState {
    MENU = 0,
    GAME
};

enum class SubMenu {
    MAIN = 0,
    PAUSE,
    SETTINGS
};

enum class StockButton {
    PLAY = 0,           // start new game (main menu)
    CONTINUE,           // continue game (pause menu)
    SETTINGS_MAIN_MENU, // go to settings (main menu)
    SETTINGS_PAUSE,     // go to settings (pause menu)
    EXIT_MAIN_MENU,     // exit game (main menu)
    EXIT_PAUSE,         // exit game (pause menu)
    CHANGE_RESOLUTION,  // change resolution (settings menu)
    WINDOW_MODE,        // enable / disable window mode (settings menu)
    VERTICAL_SYNC,      // enamge / disable vertical sync (settings menu)
    BACK                // go back (settings menu)
};

class Core
{
private:

    sf::RenderWindow _window;
    GameState _currentState;
    SubMenu _currentSubMenu;
    bool _hasGameStarted;

    std::map<SubMenu, std::vector<Button>> _menuButtons;

    std::vector<std::wstring> _lines;

    void createWindow();
    void loadLines();

    std::wstring convertToWString(std::string str);
    std::wstring getCurrentResolutionStr();

    // stock buttons callbacks
    void onPlayBtnPressed();
    void onContinueBtnPressed();
    void onSettingsBtnPressed();
    void onExitBtnPressed();
    void onResolutionBtnPressed();
    void onWindowModeBtnPressed();
    void onVerticalSyncBtnPressed();
    void onBackBtnPressed();
public:
    Core();
    virtual ~Core();

    void launchGame();
    void addStockButton(StockButton buttonType);
    void addButton(SubMenu subMenu, sf::Vector2u& position, std::wstring& title, std::function<void()> callback);

    // @param id : position of the required line in Resources/Lines.txt, starting at 0
    std::wstring& getLineById(unsigned int id);
};

