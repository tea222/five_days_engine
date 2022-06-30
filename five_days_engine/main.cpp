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

int main() {
    setlocale(LC_ALL, "Russian");

#ifndef RELEASE
restart :
#endif

    settings::load();

    sf::RenderWindow window;
    window.create(settings::videomode, settings::windowTitle, settings::windowStyle);

    window.setVerticalSyncEnabled(settings::enableVerticalSync);
    GameState currentState = GameState::MENU;
    SubMenu currentSubMenu = SubMenu::MAIN;
    bool hasGameStarted = false;

    std::map<SubMenu, std::vector<Button>> menuButtons;

    // init main menu buttons
    menuButtons[SubMenu::MAIN].push_back(Button(sf::Vector2u(2, 8), settings::lines[Line::PLAY], [&]() {             // PLAY
            currentState = GameState::GAME;
            hasGameStarted = true;
        }));
    menuButtons[SubMenu::MAIN].push_back(Button(sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {       // SETTINGS
        currentSubMenu = SubMenu::SETTINGS;
        }));
    menuButtons[SubMenu::MAIN].push_back(Button(sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {           // EXIT
            window.close(); 
        }));

    // init settings buttons
    menuButtons[SubMenu::SETTINGS].push_back(Button(sf::Vector2u(2, 8), settings::lines[Line::RESOLUTION], [&](){   // CHANGE RESOLUTION

        }));
    menuButtons[SubMenu::SETTINGS].push_back(Button(sf::Vector2u(2, 10), 
        settings::lines[settings::enableVerticalSync ? Line::VERTICAL_SYNC_ON : Line::VERTICAL_SYNC_OFF], [&](){    // VERTICAL SYNC
            //if(window.ve)
        }));

    // init pause buttons
    menuButtons[SubMenu::PAUSE].push_back(Button(sf::Vector2u(2, 8), settings::lines[Line::CONTINUE], [&]() {       // CONTINUE
        currentState = GameState::GAME;
        }));
    menuButtons[SubMenu::PAUSE].push_back(Button(sf::Vector2u(2, 10), settings::lines[Line::SETTINGS], [&]() {      // SETTINGS
        currentSubMenu = SubMenu::SETTINGS;
        }));
    menuButtons[SubMenu::PAUSE].push_back(Button(sf::Vector2u(2, 12), settings::lines[Line::EXIT], [&]() {          // EXIT
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
#endif
                        break;
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