#include <iostream>
#include "spread_sheet.h"

int main() 
{
    SpreadSheet sheet(3, 3);
    std::cout << "Enter values for the spreadsheet:" << std::endl;
    for (int i = 0; i < sheet.row(); ++i) {
        for (int j = 0; j < sheet.col(); ++j) {
            std::cin >> sheet[i][j];
        }
    }

    std::cout << "Spreadsheet after input:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.resize(5, 5);

    for (int i = 0; i < sheet.row(); ++i) {
        for (int j = 0; j < sheet.col(); ++j) {
            if (i % 2 == 0 && j % 3 == 0) {
                sheet[i][j] = "Modified";
            }
        }
    }

    std::cout << "Spreadsheet after modification:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.mirrorH();
    sheet.mirrorV();

    std::cout << "Spreadsheet after horizontal and vertical mirroring:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.rotate(1);
    std::cout << "Spreadsheet after rotation:" << std::endl;
    std::cout << sheet << std::endl;

    return 0;
}

