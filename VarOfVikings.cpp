/*************************************************************
*                РЭУ   3 КУРС                                *
*------------------------------------------------------------*
* Project Type   : Win32 Console Application                 *
* Project Name   : VarOfVikings                              *
* File Name      : VarOfVikings.cpp                          *
* Language       : C++                                       *
* Programmers(s) : Чернышёв Е., Дума А.                      *
* Modifyed by    : Новиков К.                                *
* Lit sourse     : https://github.com/PocT1k/VarOfVikings    *
* Created        : 19/03/24                                  *
* Last Revision  : 11/06/24                                  *
* Comments(s)    : ВОЙНАААААААААААААААААААА                  *
*************************************************************/

#include <windows.h>
#include <iostream>

#include "Funcs.h"


int startMoney = 2500; //Стартовые деньги, 2500 в среднем хватает на 10 воинов
float medLenShild = 0.33; //Средняя длинна цита, 0.33 = 33%
float medHealthShield = 0.1; //Среднее значение здоровья щита от здоровья всей команды, 0.1 = 10%


int main() {
    SetConsoleTitle(L"VarOfVikings");
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");
    srand(time(nullptr));
    SetConsoleTextAttribute(hConsole, 7);

    menuClear();
    printCommands();

    char key;
    bool run = 1;
    while (run) {
start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            menuClear();
            cout << "Выход из программы" << endl;
            goto end;
            break;
        case k1:
            runSimulation();
            break;
        case k2:
            editMoney();
            break;
        case k3:
            editStrateg();
            break;
        case k4:
            editStream();
            break;
        case k0:
            outInfo();
            break;
        default:
            goto start;
            break;
        } //switch

        menuStop();
        menuClear();
        printCommands();
    } //while

end:
	return 0;
}
