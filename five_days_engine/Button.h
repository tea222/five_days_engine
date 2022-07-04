#pragma once
#include <functional>
#include "SFML/Graphics.hpp"

#include "Settings.h"
#include "EventsController.h"

class Button
{
public:

    enum class ButtonType {
        PLAY = 0,           // start new game (main menu)
        CONTINUE,           // continue game (pause menu)
        SETTINGS_MAIN_MENU, // go to settings (main menu)
        SETTINGS_PAUSE,     // go to settings (pause menu)
        EXIT_MAIN_MENU,     // exit game (main menu)
        EXIT_PAUSE,         // exit game (pause menu)
        CHANGE_RESOLUTION,  // change resolution (settings menu)
        WINDOW_MODE,        // enable / disable window mode (settings menu)
        VERTICAL_SYNC,      // enamge / disable vertical sync (settings menu)
        BACK,               // go back (settings menu)
        CUSTOM              // a custom button
    };

    using ButtonCallback = std::function<void(Button*)>;

    Button(const sf::Vector2u& position, const std::wstring& title, ButtonCallback callback,
        bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());
    Button(const sf::Vector2u& position, const std::wstring& title, ButtonType btnType,
        bool useAdditionalLabel = false, const std::wstring& additionalLabelStr = std::wstring());
    virtual ~Button();

    ButtonType getType();
    void setAdditionalLabelStr(const std::wstring& str);
    void updateAndDraw(sf::RenderWindow& window);
    
private:

    ButtonType _type;
    sf::Vector2u _position;
    ButtonCallback _callback;
    const bool _useAdditionalLabel;
    bool _isPressed;
    bool _isHover;

    // things to render
    sf::ConvexShape _convex;
    sf::Text _title;
    sf::Text _additionalLabel;

    void init(const std::wstring& title, const std::wstring& additionalLabelStr);
    void updateConvexPoints();
};

