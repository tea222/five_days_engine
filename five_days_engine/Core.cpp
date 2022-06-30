#include "Core.h"

std::wstring Core::convertToWString(std::string str)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);

    return wideStr;
}

std::wstring Core::getResolutionStrFromVideoMode(sf::VideoMode& videoMode)
{
    std::string nStr = ("(" + std::to_string(videoMode.width) + ", " + std::to_string(videoMode.height) + ")");

    return convertToWString(nStr);
}
