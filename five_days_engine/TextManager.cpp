#include "TextManager.h"

std::vector<std::wstring> TextManager::_lines;
std::vector<std::wstring> TextManager::_stockLines;

std::wstring TextManager::convertToWString(std::string str)
{
    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);

    return wideStr;
}

void TextManager::loadAll()
{
    std::ifstream file;

    // stock lines
    file.open("resources/text/stock_lines.txt");
    assert(file.good());

    std::string currentStr;
    while (std::getline(file, currentStr)) {
        _stockLines.push_back(convertToWString(currentStr));
    }

    // custom lines
    file.close();
    file.open("resources/text/lines.txt");
    assert(file.good());

    while (std::getline(file, currentStr)) {
        _lines.push_back(convertToWString(currentStr));
    }

    file.close();
}

std::wstring& TextManager::getLineById(unsigned int id)
{
    return _lines.at(id);
}

std::wstring& TextManager::getStockLineById(unsigned int id)
{
    return _stockLines.at(id);
}
