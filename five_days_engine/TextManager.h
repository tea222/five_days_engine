#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <codecvt>

class TextManager
{
private:

    static std::vector<std::wstring> _lines;
    static std::vector<std::wstring> _stockLines;
public:

    static std::wstring convertToWString(std::string str);

    static void loadAll();

    // @param id : position of the required line in Resources/Lines.txt, starting at 0
    static std::wstring& getLineById(unsigned int id);

    // @param id : position of the required line in resources/text/stock_lines.txt, starting at 0
    static std::wstring& getStockLineById(unsigned int id);
};

