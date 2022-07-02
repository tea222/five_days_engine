#pragma once

#include <codecvt>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Settings.h"
#include "Button.h"

class Core
{
public:

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
    }; // BACK must be the last element
    

    enum class SwitchButtonState {
        OFF = 0,
        ON
    };

    using SwitchButtonStateStringsMap = std::map<SwitchButtonState, std::wstring>;

    Core();
    virtual ~Core();

    void setSwitchButtonStateStrings(const SwitchButtonStateStringsMap& stringsMap);
    void launchGame();
    void addStockButton(StockButton buttonType, const std::wstring& title);
    void addAllStockButtons(std::map<StockButton, std::wstring> titles);
    void addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title, 
        Button::ButtonCallback callback, bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());

    // @param id : position of the required line in Resources/Lines.txt, starting at 0
    std::wstring& getLineById(unsigned int id);

private:

    sf::RenderWindow _window;
    GameState _currentState;
    SubMenu _currentSubMenu;
    bool _hasGameStarted;
    SwitchButtonStateStringsMap _switchBtnStateStringsMap;

    std::map<SubMenu, std::vector<Button>> _menuButtons;
    sf::RectangleShape _menuBackground;

    std::vector<std::wstring> _lines;

    sf::View _gameCamera;

    void createWindow();
    void loadLines();

    std::wstring convertToWString(std::string str);
    std::wstring getCurrentResolutionStr();

    // stock buttons callbacks
    Button::ButtonCallback onPlayBtnPressed;
    Button::ButtonCallback onContinueBtnPressed;
    Button::ButtonCallback onSettingsBtnPressed;
    Button::ButtonCallback onExitBtnPressed;
    Button::ButtonCallback onResolutionBtnPressed;
    Button::ButtonCallback onWindowModeBtnPressed;
    Button::ButtonCallback onVerticalSyncBtnPressed;
    Button::ButtonCallback onBackBtnPressed;
};

