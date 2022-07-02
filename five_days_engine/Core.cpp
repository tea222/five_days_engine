#include "Core.h"

void Core::createWindow()
{
    _window.create(Settings::getVideomode(), Settings::getWindowTitle(), Settings::getWindowStyle());
    _window.setVerticalSyncEnabled(Settings::getVerticalSyncEnabled());
}

    /*
    // clear menu buttons map
    for (std::pair<const SubMenu, std::vector<Button>>& elem : _menuButtons){
        elem.second.clear();
    }

    // init main menu buttons 
    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 8), Settings::lines[Line::PLAY], [&]() {                  // PLAY
        
        }));

    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), Settings::lines[Line::SETTINGS], [&]() {         // SETTINGS
        
        }));

    _menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 12), Settings::lines[Line::EXIT], [&]() {                 // EXIT
        
        }));

    // init settings buttons
    sf::Vector2u resolutionBtnPos(2, 8);

    _resolutionText.setPosition(resolutionBtnPos.x * Settings::getBeseUiSizeUnit()
        + Settings::buttonSize.x + Settings::buttonOutlineThickness * 2.0f, resolutionBtnPos.y * Settings::getBeseUiSizeUnit());
    _resolutionText.setString(getCurrentResolutionStr());
    _resolutionText.setFont(Settings::getFont());
    _resolutionText.setCharacterSize(Settings::characterSize);

    Button resolutionBtn = Button(ButtonType::RESOLUTION, resolutionBtnPos, Settings::lines[Line::RESOLUTION], [&]() {                      // CHANGE RESOLUTION
        
        });
    _menuButtons[SubMenu::SETTINGS].push_back(resolutionBtn);


    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::VERTICAL_SYNC, sf::Vector2u(2, 10),
        Settings::lines[Settings::getVerticalSyncEnabled() ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF], [&]() {                           // VERTICAL SYNC

            Settings::getVerticalSyncEnabled() = !Settings::getVerticalSyncEnabled();
            _window.setVerticalSyncEnabled(Settings::getVerticalSyncEnabled());
            auto verticalSyncBtnIt = std::find_if(_menuButtons[SubMenu::SETTINGS].begin(), _menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
                return btn.getType() == ButtonType::VERTICAL_SYNC;
                });
            verticalSyncBtnIt->setTitle(Settings::lines[Settings::getVerticalSyncEnabled() ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF]);
        }));

    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::WINDOW_MODE, sf::Vector2u(2, 12),
        Settings::lines[Settings::getWindowStyle() == sf::Style::Default ? Line::WINDOW_MODE_ON : Line::WINDOW_MODE_OFF], [&]() {                // WINDOW MODE

            
        }));

    _menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::BACK, sf::Vector2u(2, 14), Settings::lines[Line::BACK], [&]() {             // BACK
        _currentSubMenu = _hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
        }));

    // init pause buttons
    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::CONTINUE, sf::Vector2u(2, 8), Settings::lines[Line::CONTINUE], [&]() {         // CONTINUE
        
        }));

    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), Settings::lines[Line::SETTINGS], [&]() {        // SETTINGS
        _currentSubMenu = SubMenu::SETTINGS;
        }));

    _menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::EXIT, sf::Vector2u(2, 12), Settings::lines[Line::EXIT], [&]() {                // EXIT
        _window.close();
        }));

    */


void Core::launchGame()
{
#ifndef RELEASE
    restart :
#endif

    createWindow();

    std::wstring w;
    w = convertToWString("EXIT");
    _menuButtons[SubMenu::MAIN].push_back(Button(sf::Vector2u(2, 2), w, [&]() {_window.close(); }));

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
                case sf::Event::Resized:
                {
                    sf::Vector2f viewSize(e.size.width, e.size.height);
                    sf::VideoMode newVideoMode(viewSize.x, viewSize.y);
                    Settings::setVideomode(newVideoMode);
                    sf::View newView(viewSize / 2.0f, viewSize);
                    _window.setView(newView);
                    int asd = 4;
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
{
    Settings::load();
}

Core::~Core()
{
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

void Core::addStockButton(StockButton buttonType)
{
}

void Core::addButton(SubMenu subMenu, sf::Vector2u& position, std::wstring& title, std::function<void()> callback)
{
}

void Core::onPlayBtnPressed()
{
    _currentState = GameState::GAME;
    _hasGameStarted = true;
}

void Core::onContinueBtnPressed()
{
    _currentState = GameState::GAME;
}

void Core::onSettingsBtnPressed()
{
    _currentSubMenu = SubMenu::SETTINGS;
}

void Core::onExitBtnPressed()
{
    _window.close();
}

void Core::onResolutionBtnPressed()
{
    static std::vector<sf::VideoMode> allVideomodes = sf::VideoMode::getFullscreenModes();

    auto currentVideoModeIt = std::find_if(allVideomodes.begin(), allVideomodes.end(), [&](sf::VideoMode& mode) {
        return mode == Settings::getVideomode();
        });
    currentVideoModeIt += 1;

    currentVideoModeIt = currentVideoModeIt == allVideomodes.end() ? allVideomodes.begin() : currentVideoModeIt;
    Settings::setVideomode(*currentVideoModeIt);
    createWindow();
}

void Core::onWindowModeBtnPressed()
{
    /*Settings::setWindowStyle(Settings::getWindowStyle() == sf::Style::Default ? sf::Style::Fullscreen : sf::Style::Default);
    _window.setVerticalSyncEnabled(Settings::getVerticalSyncEnabled());
    auto windowModeBtnIt = std::find_if(_menuButtons[SubMenu::SETTINGS].begin(), _menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
        return btn.getType() == ButtonType::WINDOW_MODE;
        });
    windowModeBtnIt->setTitle(Settings::getWindowStyle() == sf::Style::Default ? Settings::lines[Line::WINDOW_MODE_ON] : Settings::lines[Line::WINDOW_MODE_OFF]);
    createWindow();*/
}

void Core::onVerticalSyncBtnPressed()
{
}

void Core::onBackBtnPressed()
{
}