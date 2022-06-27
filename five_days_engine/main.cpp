#include <iostream>
#include "SFML/Graphics.hpp"



int main() {
    setlocale(LC_ALL, "Russian");

    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "5DaysEngine");
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("Resources/OnestRegular1602-hint.ttf");

    // create a text to render
    sf::Text text;
    text.setFont(font);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    text.setString(L"fsdfhsdjkfhytureio, פûמאנגהûכמא48\n35נמכןûגאנמןא, 5648/*/+¹%;?({})(*@#% ");
    
    // main loop
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
                case sf::Keyboard::Space: // space
                {
                    // rotate text by 2 degree
                    static float rotation = 0.0f;
                    rotation = rotation >= 360.0f ? 0.0f : rotation + 2.0f;
                    text.setRotation(rotation);
                    break; 
                }

                default:
                    break;
                }
            }
        }

        // render 
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}