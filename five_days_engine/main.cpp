#include "SFML/Graphics.hpp"
#include "settings.h"
#include "Button.h"

enum class GameState {
    MENU,
    GAME
};

int main() {
    setlocale(LC_ALL, "Russian");

    settings::load();

    sf::RenderWindow window;
    window.create(settings::videomode, settings::windowTitle, settings::windowStyle);

    window.setVerticalSyncEnabled(true);
    GameState currentState = GameState::MENU;

    Button playButton(sf::Vector2u(2, 10), "PLAY", [&]() {
            currentState = GameState::GAME;
        });

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
                }
            }

            // render 
            window.clear(sf::Color::Black);
            playButton.updateAndDraw(window);
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
                case sf::Event::KeyPressed: // key pressed
                    switch (e.key.code)
                    {
                    case sf::Keyboard::Escape: // escape
                    {
                        currentState = GameState::MENU;
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