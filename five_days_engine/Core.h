#pragma once

#include <codecvt>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "IEventsListener.h"
#include "EventsController.h"
#include "Settings.h"
#include "Button.h"

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

    using SwitchButtonStateStringsMap = std::map<SwitchButtonState, std::wstring>;

    Core();
    virtual ~Core();

    void setSwitchButtonStateStrings(const SwitchButtonStateStringsMap& stringsMap);
    void launchGame();
    void addStockButton(Button::ButtonType buttonType, const std::wstring& title);
    void addAllStockButtons(std::map<Button::ButtonType, std::wstring> titles);
    void addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title, 
        Button::ButtonCallback callback, bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());
    void addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title,
        Button::ButtonType btnType, bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());

    // @param id : position of the required line in Resources/Lines.txt, starting at 0
    std::wstring& getLineById(unsigned int id);

private:

    enum class GameState {
        MENU = 0,
        GAME
    };

    sf::RenderWindow _window;
    GameState _currentState;
    SubMenu _currentSubMenu;
    bool _hasGameStarted;
    SwitchButtonStateStringsMap _switchBtnStateStringsMap;

    std::map<SubMenu, std::vector<Button>> _menuButtons;
    sf::RectangleShape _menuBackground;

    std::vector<std::wstring> _lines;

    sf::View _gameCamera;

    void onEvent(EventType eType, std::vector<void*> params) override;

    void createWindow();
    void loadLines();

    std::wstring convertToWString(std::string str);
    std::wstring getCurrentResolutionStr();
};

