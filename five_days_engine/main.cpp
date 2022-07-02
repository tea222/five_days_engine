#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Core.h"

enum class Lines {
    PLAY = 0,
    CONTINUE,
    SETTINGS,
    EXIT,
    RESOLUTION,
    WINDOW_MODE,
    VERTICAL_SYNC,
    ON,
    OFF,
    BACK
};

int main() {
    setlocale(LC_ALL, "Russian");

    Core core;

    Core::SwitchButtonStateStringsMap map;
    map[Core::SwitchButtonState::ON] = core.getLineById(static_cast<unsigned int>(Lines::ON));
    map[Core::SwitchButtonState::OFF] = core.getLineById(static_cast<unsigned int>(Lines::OFF));
    core.setSwitchButtonStateStrings(map);

    std::map<Core::StockButton, std::wstring> stockBtnsTitles;
    stockBtnsTitles[Core::StockButton::PLAY]                = core.getLineById(static_cast<int>(Lines::PLAY));
    stockBtnsTitles[Core::StockButton::CONTINUE]            = core.getLineById(static_cast<int>(Lines::CONTINUE));
    stockBtnsTitles[Core::StockButton::SETTINGS_MAIN_MENU]  = core.getLineById(static_cast<int>(Lines::SETTINGS));
    stockBtnsTitles[Core::StockButton::SETTINGS_PAUSE]      = core.getLineById(static_cast<int>(Lines::SETTINGS));
    stockBtnsTitles[Core::StockButton::EXIT_MAIN_MENU]      = core.getLineById(static_cast<int>(Lines::EXIT));
    stockBtnsTitles[Core::StockButton::EXIT_PAUSE]          = core.getLineById(static_cast<int>(Lines::EXIT));
    stockBtnsTitles[Core::StockButton::CHANGE_RESOLUTION]   = core.getLineById(static_cast<int>(Lines::RESOLUTION));
    stockBtnsTitles[Core::StockButton::VERTICAL_SYNC]       = core.getLineById(static_cast<int>(Lines::VERTICAL_SYNC));
    stockBtnsTitles[Core::StockButton::WINDOW_MODE]         = core.getLineById(static_cast<int>(Lines::WINDOW_MODE));
    stockBtnsTitles[Core::StockButton::BACK]                = core.getLineById(static_cast<int>(Lines::BACK));
    core.addAllStockButtons(stockBtnsTitles);

    core.launchGame();

    return 0;
}