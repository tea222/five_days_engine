#include "SFML/Graphics.hpp"
#include "GlobalSettings.h"
#include "Button.h"

int main() {
    setlocale(LC_ALL, "Russian");

    sf::RenderWindow window;
    window.create(s.videomode, s.windowTitle, s.windowStyle);

    window.setVerticalSyncEnabled(true);

    Button button(sf::Vector2u(2, 10), "PLAY", []() {});

menu: // main and pause menu loop
    while (window.isOpen())
    {

        // events
        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type) {
            case sf::Event::Closed: // window closed
                window.close();
                break;
            case sf::Event::MouseButtonReleased: // mouse button pressed
                
                if (e.mouseButton.button == sf::Mouse::Button::Left){
                    return 0;
                }
                else{
                    goto game;
                }
                

                break;
                default:
                    break;
                
            }
        }

        // render 
        window.clear(sf::Color::Black);
        button.updateAndDraw(window);
        window.display();
    }

game: // game loop
    while (window.isOpen())
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
                    goto menu;
                    break; 
                }

                default:
                    break;
                }
            }
        }

        // render 
        window.clear(sf::Color::Black);
        window.display();
    }


    return 0;
}