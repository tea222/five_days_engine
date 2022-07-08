#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "TextureManager.h"
#include "TextManager.h"
#include "IEventsListener.h"
#include "EventsController.h"
#include "Settings.h"
#include "Button.h"
#include "Player.h"
#include "World.h"

class Core
    : public IEventsListener
{
public:

    enum class SubMenu {
        MAIN = 0,
        PAUSE,
        SETTINGS
    };

    enum class SwitchButtonState {
        OFF = 0,
        ON
    };

    Core();
    virtual ~Core();

    void launchGame();
    void addStockButton(Button::ButtonType buttonType, const std::wstring& title);
    void addAllStockButtons();
    void addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title, 
        Button::ButtonCallback callback, bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());
    void addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title,
        Button::ButtonType btnType, bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());


private:

    enum class GameState {
        MENU = 0,
        GAME
    };

    enum class StockLines {
        PLAY = 0,
        CONTINUE,
        SETTINGS_MAIN_MENU,
        SETTINGS_PAUSE,
        EXIT_MAIN_MENU,
        EXIT_PAUSE,
        RESOLUTION,
        WINDOW_MODE,
        VERTICAL_SYNC,
        BACK,
        ON,
        OFF,
        LOADING
    };

    Player _player;
    World _currentWorld;

    sf::RenderWindow _window;
    sf::View _camera;
    GameState _currentState;
    SubMenu _currentSubMenu;
    bool _hasGameStarted;

    std::map<SubMenu, std::vector<Button>> _menuButtons;

    sf::View _gameCamera;

    void onEvent(EventType eType, std::vector<void*> params) override;

    void createWindow();

    void showLoadingScreen();
    void updateResolutionBtnStr();
    std::wstring getCurrentResolutionStr();
};

