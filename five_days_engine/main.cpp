#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Core.h"
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

int main() {
    setlocale(LC_ALL, "Russian");

#ifndef RELEASE
restart :
#endif

    Core core;
    settings::load();

    sf::RenderWindow window;
    window.create(settings::videomode, settings::windowTitle, settings::windowStyle);

    window.setVerticalSyncEnabled(settings::enableVerticalSync);
    GameState currentState = GameState::MENU;
    SubMenu currentSubMenu = SubMenu::MAIN;
    bool hasGameStarted = false;

    std::map<SubMenu, std::vector<Button>> menuButtons;

    // init main menu buttons 
    menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 8), settings::lines[Line::PLAY], [&]() {                  // PLAY
            currentState = GameState::GAME;
            hasGameStarted = true;
        }));
    menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {         // SETTINGS
        currentSubMenu = SubMenu::SETTINGS;
        }));
    menuButtons[SubMenu::MAIN].push_back(Button(ButtonType::PLAY, sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {                 // EXIT
            window.close(); 
        }));

    // init settings buttons
    std::wstring resolutionWStr = core.getResolutionStrFromVideoMode(settings::videomode);
    sf::Vector2u resolutionBtnPos(2, 8);
    sf::Text resolutionText;
    resolutionText.setPosition(resolutionBtnPos.x * settings::baseUiSizeUnit 
        + settings::buttonSize.x + settings::buttonOutlineThickness * 2.0f, resolutionBtnPos.y * settings::baseUiSizeUnit);
    resolutionText.setString(resolutionWStr);
    resolutionText.setFont(settings::font);
    Button resolutionBtn = Button(ButtonType::RESOLUTION, resolutionBtnPos, settings::lines[Line::RESOLUTION], [&]() {                    // CHANGE RESOLUTION
        static std::vector<sf::VideoMode> allVideomodes = sf::VideoMode::getFullscreenModes();
        auto resolutionBtnIt = std::find_if(menuButtons[SubMenu::SETTINGS].begin(), menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
            return btn.getType() == ButtonType::RESOLUTION;
            });
        auto currentVideoModeIt = std::find_if(allVideomodes.begin(), allVideomodes.end(), [&](sf::VideoMode& mode) {
            return mode == settings::videomode;
            });
        currentVideoModeIt += 1;

        if (currentVideoModeIt == allVideomodes.end())
        {
            currentVideoModeIt = allVideomodes.begin();
        }
        settings::videomode = *currentVideoModeIt;
        resolutionWStr = core.getResolutionStrFromVideoMode(settings::videomode);
        resolutionText.setString(resolutionWStr);
        window.create(settings::videomode, settings::windowTitle, settings::windowStyle);
        });
    menuButtons[SubMenu::SETTINGS].push_back(resolutionBtn);

    menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::VERTICAL_SYNC, sf::Vector2u(2, 10),
    settings::lines[settings::enableVerticalSync ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF], [&](){                                // VERTICAL SYNC
            
            settings::enableVerticalSync = !settings::enableVerticalSync;
            window.setVerticalSyncEnabled(settings::enableVerticalSync);
            auto verticalSyncBtnIt = std::find_if(menuButtons[SubMenu::SETTINGS].begin(), menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
                    return btn.getType() == ButtonType::VERTICAL_SYNC;
                });
            verticalSyncBtnIt->setTitle(settings::lines[settings::enableVerticalSync ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF]);
        }));

    menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::WINDOW_MODE, sf::Vector2u(2, 12),
        settings::lines[settings::windowStyle == sf::Style::Default ? Line::WINDOW_MODE_ON : Line::WINDOW_MODE_OFF], [&]() {                // WINDOW MODE

            settings::windowStyle = settings::windowStyle == sf::Style::Default ? sf::Style::Fullscreen : sf::Style::Default;
            window.setVerticalSyncEnabled(settings::enableVerticalSync);
            auto windowModeBtnIt = std::find_if(menuButtons[SubMenu::SETTINGS].begin(), menuButtons[SubMenu::SETTINGS].end(), [&](Button& btn) {
                return btn.getType() == ButtonType::WINDOW_MODE;
                });
            windowModeBtnIt->setTitle(settings::windowStyle == sf::Style::Default ? settings::lines[Line::WINDOW_MODE_ON] : settings::lines[Line::WINDOW_MODE_OFF]);
            window.create(settings::videomode, settings::windowTitle, settings::windowStyle);
        }));

    menuButtons[SubMenu::SETTINGS].push_back(Button(ButtonType::BACK, sf::Vector2u(2, 14), settings::lines[Line::BACK], [&]() {             // BACK

        currentSubMenu = hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
        }));

    // init pause buttons
    menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::CONTINUE, sf::Vector2u(2, 8), settings::lines[Line::CONTINUE], [&]() {         // CONTINUE
        currentState = GameState::GAME;
        }));
    menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::SETTINGS, sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {        // SETTINGS
        currentSubMenu = SubMenu::SETTINGS;
        }));
    menuButtons[SubMenu::PAUSE].push_back(Button(ButtonType::EXIT, sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {                // EXIT
        window.close();
        }));

// main and pause menu 
    while (window.isOpen())
    {
        switch (currentState)
        {
        case GameState::MENU:
        {
            // events
            sf::Event e;
            while (window.pollEvent(e))
            {
                switch (e.type) {
                case sf::Event::Closed: // window closed
                    window.close();
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
                        if (currentSubMenu == SubMenu::SETTINGS)
                        {
                            currentSubMenu = hasGameStarted ? SubMenu::PAUSE : SubMenu::MAIN;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            // render 
            window.clear(sf::Color::Black);

            auto& currentButtons = menuButtons[currentSubMenu];
            for (Button& btn : currentButtons){
                btn.updateAndDraw(window);
            }
            if (currentSubMenu == SubMenu::SETTINGS)
            {
                window.draw(resolutionText);
            }

            window.display();
            break;
        }
        case GameState::GAME:
        {
            // events
            sf::Event e;
            while (window.pollEvent(e))
            {
                switch (e.type) {
                case sf::Event::Closed: // window closed
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (e.key.code)
                    {
                    case sf::Keyboard::Escape:
                    {
                        currentState = GameState::MENU;
                        currentSubMenu = SubMenu::PAUSE;
                        break;
                    }
                    default:
                        break;
                    }
                }
            }

            // render 
            window.clear(sf::Color::Black);



            sf::Text text;
            text.setString("this is where the game is supposed to be..");
            text.setFont(settings::font);
            text.setPosition(500, 200);
            window.draw(text);



            window.display();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}