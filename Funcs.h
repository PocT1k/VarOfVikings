#pragma once
#ifndef VAROFVIKINGS_FUNCS
#define VAROFVIKINGS_FUNCS

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <random>

#include "Team.h"

using namespace std;


#define kESC 27
#define kSPACE 32
#define kENTER 13
#define kBACKSPACE 8
#define k1 49
#define k2 50
#define k3 51
#define k4 52
#define k5 53
#define k6 54
#define k7 55
#define k8 56
#define k9 57
#define k0 58

extern int startMoney;
int money = startMoney;


void printCommands();
void menuStop();
void menuClear();
void editMoney();
void outInfo();
void startSimulation();


void printCommands() {
    cout << "Нажмите соотвествующую клавишу:" << endl;
    cout << "1 Запустить симуляцию" << endl;
    cout << "2 Изменить стартовый бюджет" << endl;
    //cout << "3 Печать параметров" << endl;
    cout << "ESC остановить программу" << endl;
}

void menuStop() {
    cout << endl << "Для продолжения работы нажмите ENTER" << endl;
    char key;
    while (true) {
        key = _getch();
        switch (key) {
        case kENTER:
            return;
        default:
            break;
        }
    }
}

void menuClear() {
    system("CLS");
}

void editMoney() {
    menuClear();
    cout << "2 Изменение стартового бюджета" << endl;
    cout << endl;
    cout << "Текущее значение: " << startMoney << " (стандартное значение: " << money << ")" << endl;
    cout << "Введите новый бюджет: " << endl;

    string str;
    getline(cin, str);
    string newMoney = "";

    for (char c : str) {
        if (isdigit(c)) {
            newMoney += c;
        }
    }

    int res;
    if (newMoney == "") {
        res = startMoney;
        cout << "Стартовый бюджет не изменён - нет цифр в строке, старое значение " << startMoney << endl;
    }
    else {
        res = stoi(newMoney);
        cout << "Стартовый бюджет изменён и состовляет " << res << endl;
    }
    menuStop();
    menuClear();
    printCommands();
    startMoney = res;
}

void outInfo() {

}

void startSimulation() {
    Team team1(1);
    Team team2(2);

    menuClear();
    cout << "Комманы перед началом боя: " << endl;
    team1.print();
    team2.print();
    menuStop();

    int motion = 0;
    while (team1.len != 0 && team2.len != 0) { //Цикл боя
        team1.move(team2);
        team2.move(team1);

        //Результаты
        cout << ++motion << " ход: " << endl;
        team1.print();
        team2.print();
    }

    cout << endl << "Бой завершён, победила команда " << (team2.len == 0 ? team1 : team2).number << endl;
}


#endif
