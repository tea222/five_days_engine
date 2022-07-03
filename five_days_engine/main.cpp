#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Core.h"

enum class Line {

    // stock buttons lines
    PLAY = 0,
    CONTINUE,
    SETTINGS_MAIN_MENU,
    SETTINGS_PAUSE,
    EXIT_MAIN_MENU,
    EXIT_PAUSE,
    RESOLUTION,
    WINDOW_MODE,
    VERTICAL_SYNC,
    BACK,
    ON,
    OFF
};

int main() {
    setlocale(LC_ALL, "Russian");

    Core core;

    // set ON/OFF strings
    Core::SwitchButtonStateStringsMap map;
    map[Core::SwitchButtonState::ON] = core.getLineById(static_cast<unsigned int>(Line::ON));
    map[Core::SwitchButtonState::OFF] = core.getLineById(static_cast<unsigned int>(Line::OFF));
    core.setSwitchButtonStateStrings(map);

    // set stock button strings
    std::map<Button::ButtonType, std::wstring> stockBtnsTitles;
    int i = 0;
    while (i < static_cast<int>(Button::ButtonType::CUSTOM))
    {
        Button::ButtonType btn = static_cast<Button::ButtonType>(i);
        Line btnTitle = static_cast<Line>(i);
        stockBtnsTitles[btn] = core.getLineById(static_cast<unsigned>(btnTitle));
        i++;
    }
    core.addAllStockButtons(stockBtnsTitles); // add all stock buttons

    core.launchGame();

    return 0;
}