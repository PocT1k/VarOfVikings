﻿/*************************************************************
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
* Last Revision  : 23/03/24                                  *
* Comments(s)    : ВОЙНАААААААААААААААААААА                  *
*************************************************************/

#include <windows.h>
#include <iostream>

#include "Funcs.h"


int startMoney = 2500;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");
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
            editMoney();
            break;
        //case k3:
        //    outInfo();
        //    break;
        default:
            break;
        }

        menuStop();
        menuClear();
        printCommands();
    }

	return 0;
}
