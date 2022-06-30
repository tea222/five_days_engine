#include "Core.h"

void Core::createWindow()
{
    _window.create(settings::videomode, settings::windowTitle, settings::windowStyle);
}

void Core::initButtons()
{
    // clear menu buttons map
    for (std::pair<const SubMenu, std::vector<Button>>& elem : _menuButtons){
        elem.second.clear();
    }

    // init main menu buttons 
    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 8), settings::lines[Line::PLAY], [&]() {                  // PLAY
        _currentState = GameState::GAME;
        _hasGameStarted = true;
        }));

    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {         // SETTINGS
        _currentSubMenu = SubMenu::SETTINGS;
        }));

    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {                 // EXIT
        _window.close();
        }));

    // init settings buttons
    sf::Vector2u resolutionBtnPos(2, 8);

    _resolutionText.setPosition(resolutionBtnPos.x * settings::baseUiSizeUnit
        + settings::buttonSize.x + settings::buttonOutlineThickness * 2.0f, resolutionBtnPos.y * settings::baseUiSizeUnit);
    _resolutionText.setString(getCurrentResolutionStr());
    _resolutionText.setFont(settings::font);
    _resolutionText.setCharacterSize(settings::characterSize);

    Button resolutionBtn = Button(ButtonType::RESOLUTION, resolutionBtnPos, settings::lines[Line::RESOLUTION], [&]() {                      // CHANGE RESOLUTION
        static std::vector<sf::VideoMode> allVideomodes = sf::VideoMode::getFullscreenModes();

        auto currentVideoModeIt = std::find_if(allVideomodes.begin(), allVideomodes.end(), [&](sf::VideoMode& mode) {
            return mode == settings::videomode;
            });
        currentVideoModeIt += 1;

        if (currentVideoModeIt == allVideomodes.end())
        {
            currentVideoModeIt = allVideomodes.begin();
        }
        settings::videomode = *currentVideoModeIt;
        _resolutionText.setString(getCurrentResolutionStr());
        createWindow();

        settings::updateWindowSettings();
        initButtons(); // normalize buttons position
        });
    _menuButtons[SubMenu::SETTINGS].push_back(resolutionBtn);


    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::VERTICAL_SYNC, sf::Vector2u(2, 10),
        settings::lines[settings::enableVerticalSync ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF], [&]() {                           // VERTICAL SYNC

            settings::enableVerticalSync = !settings::enableVerticalSync;
            _window.setVerticalSyncEnabled(settings::enableVerticalSync);
            auto verticalSyncBtnIt = std::find_if(_menuButtons[SubMenu::SETTINGS].begin(), _menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
                return btn.getType() == ButtonType::VERTICAL_SYNC;
                });
            verticalSyncBtnIt->setTitle(settings::lines[settings::enableVerticalSync ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF]);
        }));

    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::WINDOW_MODE, sf::Vector2u(2, 12),
        settings::lines[settings::windowStyle == sf::Style::Default ? Line::WINDOW_MODE_ON : Line::WINDOW_MODE_OFF], [&]() {                // WINDOW MODE

            settings::windowStyle = settings::windowStyle == sf::Style::Default ? sf::Style::Fullscreen : sf::Style::Default;
            _window.setVerticalSyncEnabled(settings::enableVerticalSync);
            auto windowModeBtnIt = std::find_if(_menuButtons[SubMenu::SETTINGS].begin(), _menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
                return btn.getType() == ButtonType::WINDOW_MODE;
                });
            windowModeBtnIt->setTitle(settings::windowStyle == sf::Style::Default ? settings::lines[Line::WINDOW_MODE_ON] : settings::lines[Line::WINDOW_MODE_OFF]);
            createWindow();
        }));

    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::BACK, sf::Vector2u(2, 14), settings::lines[Line::BACK], [&]() {             // BACK
        _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
        }));

    // init pause buttons
    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::CONTINUE, sf::Vector2u(2, 8), settings::lines[Line::CONTINUE], [&]() {         // CONTINUE
        _currentState = GameState::GAME;
        }));

    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {        // SETTINGS
        _currentSubMenu = SubMenu::SETTINGS;
        }));

    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::EXIT, sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {                // EXIT
        _window.close();
        }));
}

void Core::launchApp()
{
#ifndef RELEASE
    restart :
#endif

    settings::load();

    createWindow();

    _window.setVerticalSyncEnabled(settings::enableVerticalSync);
    
    initButtons();
    

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
                default:
                    break;
                case sf::Event::KeyPressed:
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
                }
            }

            // render 
            _window.clear(sf::Color::Black);

            auto& currentButtons = _menuButtons[_currentSubMenu];
            for (Button& btn : currentButtons) {
                btn.updateAndDraw(_window);
            }
            if (_currentSubMenu == SubMenu::SETTINGS)
            {
                _window.draw(_resolutionText);
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
            text.setFont(settings::font);
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
{
}

Core::~Core()
{
}

std::wstring Core::convertToWString(std::string str)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);

    return wideStr;
}

std::wstring Core::getCurrentResolutionStr()
{
    std::string nStr = ("(" + std::to_string(settings::videomode.width) + ", " 
        + std::to_string(settings::videomode.height) + ")");

    return convertToWString(nStr);
}
