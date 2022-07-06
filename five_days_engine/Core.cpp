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

    _camera = _window.getView();

    sf::Clock timer;
    float delta = 0.0f;
    _player.init();

    // init background
    sf::Texture* backgroundTexture = TextureManager::getTexture((unsigned)(Textures::BACKGROUND));
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(backgroundTexture->getSize());
    _menuBackground.setTexture(backgroundTexture);
    _menuBackground.setSize(backgroundSize);
    _menuBackground.setOrigin(backgroundSize / 2.0f);

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
                            if (_currentState == GameState::MENU) {
                                if (_currentSubMenu == SubMenu::PAUSE) {
                                    _currentState = GameState::GAME;
                                }
                                else if (_currentSubMenu == SubMenu::SETTINGS) {
                                    _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
                                }
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    case sf::Event::Resized: // resized
                    {
                        sf::Vector2f viewSize(e.size.width, e.size.height);
                        sf::VideoMode newVideoMode(viewSize.x, viewSize.y);
                        Settings::setVideomode(newVideoMode);
                        sf::View newView(viewSize / 2.0f, viewSize);
                        _window.setView(newView);

                        auto beginIt = _menuButtons[SubMenu::SETTINGS].begin();
                        auto endIt = _menuButtons[SubMenu::SETTINGS].end();
                        auto resolutionBtn = std::find_if(beginIt, endIt, [&](Button& btn) {
                            return btn.getType() == Button::ButtonType::CHANGE_RESOLUTION;
                            });
                        if (resolutionBtn != endIt) {
                            resolutionBtn->setAdditionalLabelStr(getCurrentResolutionStr());
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                // render 
                _window.clear(sf::Color::Black);

                // normalize camera center
                sf::View menuCamera = _window.getView();
                menuCamera.setCenter(menuCamera.getSize() / 2.0f);
                _window.setView(menuCamera);

                // background
                sf::Vector2f viewSize = sf::Vector2f(Settings::getVideomode().width, Settings::getVideomode().height);
                _menuBackground.setScale(viewSize.x / backgroundSize.x, viewSize.y / backgroundSize.y);
                _menuBackground.setPosition(viewSize / 2.0f);
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
                    case sf::Event::KeyPressed: // key pressed
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

                _player.update(delta);

                // normalize camera center
                _camera.setCenter(_player.getPosition());
                _window.setView(_camera);

                sf::Text text;
                text.setString("this is where the game is supposed to be..");
                text.setFont(Settings::getFont());
                text.setPosition(500, 200);
                _window.draw(text);

                
                _window.draw(_currentWorld);
                _window.draw(_player);


                _window.display();

                delta = timer.getElapsedTime().asSeconds();
                break;
            }
        }

        timer.restart();
    }
}

Core::Core()
    : _currentState(GameState::MENU)
    , _currentSubMenu(SubMenu::MAIN)
    , _hasGameStarted(false)
    , _gameCamera(sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f)))
    , _camera()
{
    EventsController::addListener(this);

    Settings::load();
    World::updateTileSize();
    TextManager::loadAll();
    TextureManager::loadAll();
}

Core::~Core()
{
    EventsController::removeListener(this);
}

std::wstring Core::getCurrentResolutionStr()
{
    std::string nStr = ("(" + std::to_string(Settings::getVideomode().width) + ", " 
        + std::to_string(Settings::getVideomode().height) + ")");

    return TextManager::convertToWString(nStr);
}

void Core::onEvent(EventType eType, std::vector<void*> params)
{
    switch (eType)
    {
        case EventType::STOCK_BUTTON_PRESSED:   // STOCK BUTTON PRESSED
        {
            Button* buttonPtr = static_cast<Button*>(params.at(0));
            Button::ButtonType btnType = buttonPtr->getType();

            switch (btnType)
            {
            case Button::ButtonType::PLAY:
            case Button::ButtonType::CONTINUE:              // PLAY AND CONTINUE
                _currentState = GameState::GAME;        
                _hasGameStarted = true;
                break;
            case Button::ButtonType::SETTINGS_MAIN_MENU:    // SETTINGS
            case Button::ButtonType::SETTINGS_PAUSE:
                _currentSubMenu = SubMenu::SETTINGS;
                break;
            case Button::ButtonType::EXIT_MAIN_MENU:        // EXIT
            case Button::ButtonType::EXIT_PAUSE:
                _window.close();
                break;
            case Button::ButtonType::CHANGE_RESOLUTION:     // RESOLUTION
            {
                static std::vector<sf::VideoMode> allVideomodes = sf::VideoMode::getFullscreenModes();
                static auto currentVideoModeIt = std::find_if(allVideomodes.begin(), allVideomodes.end(), [&](sf::VideoMode& mode) {
                    return mode == Settings::getDefaultVideomode();
                    });

                currentVideoModeIt += 1;
                currentVideoModeIt = currentVideoModeIt == allVideomodes.end() ? allVideomodes.begin() : currentVideoModeIt;

                Settings::setVideomode(*currentVideoModeIt);
                buttonPtr->setAdditionalLabelStr(getCurrentResolutionStr());
                createWindow();
                break;
            }
            case Button::ButtonType::WINDOW_MODE:           // WINDOW MODE
            {
                bool setWindowMode = Settings::getWindowStyle() == sf::Style::Fullscreen;
                Settings::setWindowStyle(setWindowMode ? sf::Style::Default : sf::Style::Fullscreen);

                buttonPtr->setAdditionalLabelStr(TextManager::getStockLineById((unsigned)(setWindowMode ? StockLines::ON : StockLines::OFF)));
                createWindow();

                break;
            }
            case Button::ButtonType::VERTICAL_SYNC:         // VERTICAL SYNC
            {
                bool setEnabled = !Settings::getVerticalSyncEnabled();
                Settings::setVerticalSyncEnabled(setEnabled);
                _window.setVerticalSyncEnabled(setEnabled);

                buttonPtr->setAdditionalLabelStr(TextManager::getStockLineById((unsigned)(setEnabled ? StockLines::ON : StockLines::OFF)));

                break;
            }
            case Button::ButtonType::BACK:                  // BACK
                _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;

                break;
            default:
                break;
            }

            break;
        }
        default:
            break;
    }
}

void Core::addStockButton(Button::ButtonType buttonType, const std::wstring& title)
{
    SubMenu subMenu(SubMenu::MAIN);
    sf::Vector2u position(0, 0);
    bool useAdditionalLabel = false;
    std::wstring additLabelStr;

    switch (buttonType)
    {
    case Button::ButtonType::PLAY:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(2, 8);
        break;
    case Button::ButtonType::CONTINUE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(2, 8);
        break;
    case Button::ButtonType::SETTINGS_MAIN_MENU:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(3, 10);
        break;
    case Button::ButtonType::SETTINGS_PAUSE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(3, 10);
        break;
    case Button::ButtonType::EXIT_MAIN_MENU:
        subMenu = SubMenu::MAIN;
        position = sf::Vector2u(4, 12);
        break;
    case Button::ButtonType::EXIT_PAUSE:
        subMenu = SubMenu::PAUSE;
        position = sf::Vector2u(4, 12);
        break;
    case Button::ButtonType::CHANGE_RESOLUTION:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 8);
        useAdditionalLabel = true;
        additLabelStr = getCurrentResolutionStr();
        break;
    case Button::ButtonType::WINDOW_MODE:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 10);
        useAdditionalLabel = true;
        additLabelStr = TextManager::getStockLineById((unsigned)(Settings::getWindowStyle() == sf::Style::Default ? StockLines::ON : StockLines::OFF));
        break;
    case Button::ButtonType::VERTICAL_SYNC:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 12);
        useAdditionalLabel = true;
        additLabelStr = TextManager::getStockLineById((unsigned)(Settings::getVerticalSyncEnabled() ? StockLines::ON : StockLines::OFF));
        break;
    case Button::ButtonType::BACK:
        subMenu = SubMenu::SETTINGS;
        position = sf::Vector2u(2, 14);
        break;
    default:
        break;
    }

    addButton(subMenu, position, title, buttonType, useAdditionalLabel, additLabelStr);
}

void Core::addAllStockButtons()
{
    int i = 0;
    Button::ButtonType btn = static_cast<Button::ButtonType>(i);
    while (i < static_cast<int>(Button::ButtonType::CUSTOM))
    {
        unsigned lineId = static_cast<unsigned>(btn);
        addStockButton(btn, TextManager::getStockLineById(lineId));
        btn = static_cast<Button::ButtonType>(++i);
    }
}

void Core::addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title,
    Button::ButtonCallback callback, bool useAdditionalLabel, const std::wstring& additionalLabelStr)
{
    _menuButtons[subMenu].push_back(Button(position, title, callback, useAdditionalLabel, additionalLabelStr));
}

void Core::addButton(SubMenu subMenu, const sf::Vector2u& position, const std::wstring& title, 
    Button::ButtonType btnType, bool useAdditionalLabel, const std::wstring& additionalLabelStr)
{
    _menuButtons[subMenu].push_back(Button(position, title, btnType, useAdditionalLabel, additionalLabelStr));
}
