#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Core.h"
#include "settings.h"
#include "Button.h"


int main() {
    setlocale(LC_ALL, "Russian");

    Core core;
    core.launchApp();

    return 0;
}