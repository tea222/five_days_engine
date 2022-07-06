#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Core.h"


int main() {
    setlocale(LC_ALL, "Russian");

    Core core;

    core.addAllStockButtons();

    core.launchGame();

    return 0;
}