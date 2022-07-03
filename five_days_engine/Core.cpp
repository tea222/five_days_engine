#include "Core.h"

void Core::createWindow()
{
    _window.create(Settings::getVideomode(), Settings::getWindowTitle(), Settings::getWindowStyle());
    _window.setVerticalSyncEnabled(Settings::getVerticalSyncEnabled());
}

void Core::launchGame()
{
#ifndef RELEASE
    restart :
#endif

    createWindow();

    // init background
    sf::Texture* backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile("Resources/background.jpg");
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(backgroundTexture->getSize());
    _menuBackground.setSize(backgroundSize);
    _menuBackground.setTexture(backgroundTexture);

    // main loop 
    while (_window.isOpen())
    {
        switch (_currentState)
        {
        case GameState::MENU:
        {
            // events
            sf::Event e;
            while (_window.pollEvent(e))
            {
                switch (e.type) {
                case sf::Event::Closed: // window closed
                    _window.close();
                    break;
                case sf::Event::KeyPressed: // key pressed
                    switch (e.key.code)
                    {
#ifndef RELEASE
                    case sf::Keyboard::F5:
                        goto restart;
                        break;
#endif                  
                    case sf::Keyboard::Escape:
                        if (_currentSubMenu == SubMenu::SETTINGS)
                        {
                            _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case sf::Event::Resized:
                {
                    sf::Vector2f viewSize(e.size.width, e.size.height);
                    sf::VideoMode newVideoMode(viewSize.x, viewSize.y);
                    Settings::setVideomode(newVideoMode);
                    sf::View newView(viewSize / 2.0f, viewSize);
                    _window.setView(newView);
                    break;
                }
                default:
                    break;
                }
            }
            // render 
            _window.clear(sf::Color::Black);

            // background
            sf::Vector2f textureSize = static_cast<sf::Vector2f>(backgroundTexture->getSize());
            sf::Vector2f windowSize = static_cast<sf::Vector2f>(_window.getSize());
            float scale = windowSize.x / textureSize.x;
            _menuBackground.setSize(textureSize * scale);
            _menuBackground.setOrigin(textureSize * scale / 2.0f);
            _menuBackground.setPosition(windowSize / 2.0f);
            _window.draw(_menuBackground);

            // buttons
            auto& currentButtons = _menuButtons[_currentSubMenu];
            for (Button& btn : currentButtons) {
                btn.updateAndDraw(_window);
            }

            _window.display();
            break;
        }
        case GameState::GAME:
        {
            // events
            sf::Event e;
            while (_window.pollEvent(e))
            {
                switch (e.type) {
                case sf::Event::Closed: // window closed
                    _window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::Escape:
                    {
                        _currentState = GameState::MENU;
                        _currentSubMenu = SubMenu::PAUSE;
                        break;
                    }
                    default:
                        break;
                    }
                }
            }

            // render 
            _window.clear(sf::Color::Black);



            sf::Text text;
            text.setString("this is where the game is supposed to be..");
            text.setFont(Settings::getFont());
            text.setPosition(500, 200);
            _window.draw(text);



            _window.display();
            break;
        }
        default:
            break;
        }
    }
}

Core::Core()
    : _currentState(GameState::MENU)
    , _currentSubMenu(SubMenu::MAIN)
    , _hasGameStarted(false)
    , _gameCamera(sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f)))
{
    Settings::load();
    loadLines();

    // init stock button callbacks
    onPlayBtnPressed = [&](Button* buttonPtr) {         // PLAY
        _currentState = GameState::GAME;
        _hasGameStarted = true;
    };

    onContinueBtnPressed = [&](Button* buttonPtr) {     // CONTINUE
        _currentState = GameState::GAME;
    };

    onSettingsBtnPressed = [&](Button* buttonPtr) {     // SETTINGS
        _currentSubMenu = SubMenu::SETTINGS;
    };

    onExitBtnPressed = [&](Button* buttonPtr) {         // EXIT
        _window.close();
    };

    onResolutionBtnPressed = [&](Button* buttonPtr) {   // CHANGE RESOLUTION
        static std::vector<sf::VideoMode> allVideomodes = sf::VideoMode::getFullscreenModes();

        auto currentVideoModeIt = std::find_if(allVideomodes.begin(), allVideomodes.end(), [&](sf::VideoMode& mode) {
            return mode == Settings::getVideomode();
            });
        currentVideoModeIt += 1;
        currentVideoModeIt = currentVideoModeIt == allVideomodes.end() ? allVideomodes.begin() : currentVideoModeIt;

        Settings::setVideomode(*currentVideoModeIt);
        buttonPtr->setAdditionalLabelStr(getCurrentResolutionStr());
        createWindow();
    };

    onWindowModeBtnPressed = [&](Button* buttonPtr) {   // WINDOW MODE
        bool setWindowMode = Settings::getWindowStyle() == sf::Style::Fullscreen;
        Settings::setWindowStyle(setWindowMode ? sf::Style::Default : sf::Style::Fullscreen);

        buttonPtr->setAdditionalLabelStr(_switchBtnStateStringsMap[setWindowMode ? SwitchButtonState::ON : SwitchButtonState::OFF]);
        createWindow();
    };

    onVerticalSyncBtnPressed = [&](Button* buttonPtr) { // VERTICAL SYNC
        bool setEnabled = !Settings::getVerticalSyncEnabled();
        Settings::setVerticalSyncEnabled(setEnabled);
        _window.setVerticalSyncEnabled(setEnabled);

        buttonPtr->setAdditionalLabelStr(_switchBtnStateStringsMap[setEnabled ? SwitchButtonState::ON : SwitchButtonState::OFF]);
    };

    onBackBtnPressed = [&](Button* buttonPtr) {         // BACK
        _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
    };
}

Core::~Core()
{
}

void Core::setSwitchButtonStateStrings(const SwitchButtonStateStringsMap& stringsMap)
{
    _switchBtnStateStringsMap = stringsMap;
}

std::wstring& Core::getLineById(unsigned int id)
{
    return _lines.at(id);
}

std::wstring Core::convertToWString(std::string str)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);

    return wideStr;
}

std::wstring Core::getCurrentResolutionStr()
{
    std::string nStr = ("(" + std::to_string(Settings::getVideomode().width) + ", " 
        + std::to_string(Settings::getVideomode().height) + ")");

    return convertToWString(nStr);
}

void Core::loadLines()
{
    std::ifstream file;
    file.open("Resources/Lines.txt");

    assert(file.good());

    std::string currentStr;
    while (std::getline(file, currentStr)) {
        _lines.push_back(convertToWString(currentStr));
    }
    file.close();
}

void Core::addStockButton(StockButton buttonType, const std::wstring& title)
{
    SubMenu subMenu(SubMenu::MAIN);
    sf::Vector2u position(0, 0);
    Button::ButtonCallback callback = onExitBtnPressed;
    bool useAdditionalLabel = false;
    std::wstring additLabelStr;

    switch (buttonType)
    {
    case Core::StockButton::PLAY:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(2, 8);
        callback = onPlayBtnPressed;
        break;
    case Core::StockButton::CONTINUE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(2, 8);
        callback = onContinueBtnPressed;
        break;
    case Core::StockButton::SETTINGS_MAIN_MENU:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(2, 10);
        callback = onSettingsBtnPressed;
        break;
    case Core::StockButton::SETTINGS_PAUSE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(2, 10);
        callback = onSettingsBtnPressed;
        break;
    case Core::StockButton::EXIT_MAIN_MENU:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(2, 12);
        callback = onExitBtnPressed;
        break;
    case Core::StockButton::EXIT_PAUSE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(2, 12);
        callback = onExitBtnPressed;
        break;
    case Core::StockButton::CHANGE_RESOLUTION:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 8);
        callback = onResolutionBtnPressed;
        useAdditionalLabel = true;
        additLabelStr = getCurrentResolutionStr();
        break;
    case Core::StockButton::WINDOW_MODE:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 10);
        callback = onWindowModeBtnPressed;
        useAdditionalLabel = true;
        additLabelStr = _switchBtnStateStringsMap[Settings::getWindowStyle() == sf::Style::Default ? SwitchButtonState::ON : SwitchButtonState::OFF];
        break;
    case Core::StockButton::VERTICAL_SYNC:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 12);
        callback = onVerticalSyncBtnPressed;
        useAdditionalLabel = true;
        additLabelStr = _switchBtnStateStringsMap[Settings::getVerticalSyncEnabled() ? SwitchButtonState::ON : SwitchButtonState::OFF];
        break;
    case Core::StockButton::BACK:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 14);
        callback = onBackBtnPressed;
        break;
    default:
        break;
    }

    addButton(subMenu, position, title, callback, useAdditionalLabel, additLabelStr);
}

void Core::addAllStockButtons(std::map<StockButton, std::wstring> titles)
{
    int i = 0;
    StockButton btn = static_cast<StockButton>(i);
    while (i <= static_cast<int>(StockButton::BACK))
    {
        addStockButton(btn, titles[btn]);
        btn = static_cast<StockButton>(++i);
    }
}

void Core::addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title,
    Button::ButtonCallback callback, bool useAdditionalLabel, const std::wstring& additionalLabelStr)
{
    _menuButtons[subMenu].push_back(Button(position, title, callback, useAdditionalLabel, additionalLabelStr));
}