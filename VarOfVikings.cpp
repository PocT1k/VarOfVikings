/*************************************************************
*                              /|-   />                      *
*                Плешка    <========//                       *
*                              \|-                           *
*------------------------------------------------------------*
* Project Type   : Win32 Console Application                 *
* Project Name   : VarOfVikings                              *
* File Name      : VarOfVikings.cpp                          *
* Language       : C++                                       *
* Programmers(s) : Чернышёв Е.А.                             *
* Modifyed by    :                                           *
* Lit sourse     :                                           *
* Created        : 19/03/24                                  *
* Last Revision  : 20/03/24                                  *
* Comments(s)    : ВОЙНАААААААААААААААААААА                  *
*************************************************************/

#include <Windows.h>
#include <iostream>

#include "Units.h"
#include "Funcs.h"

using namespace std;


int startMoney = 2500;

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 1251>nul");
    srand(time(nullptr));
    SetConsoleTitle(L"VarOfVikings");

    menuClear();
    printCommands();

    char key;
    bool run = 1;
    while (run) {
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            break;
        case k1:
            startSimulation();
            break;
        case k2:
            startMoney = editMoney();
            break;
        default:
            break;
        }
    }

	return 0;
}
