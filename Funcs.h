#pragma once
#ifndef VAROFVIKINGS_FUNCS
#define VAROFVIKINGS_FUNCS

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <random>

#include "Team.h"

using namespace std;


#define kESC 27
#define kSPACE 32
#define kENTER 13
#define kBACKSPACE 8
#define k0 48
#define k1 49
#define k2 50
#define k3 51
#define k4 52
#define k5 53
#define k6 54
#define k7 55
#define k8 56
#define k9 57


//money
extern int startMoney;
int standartMoney = startMoney;
//strateg
extern unsigned int typeStrateg;
extern const unsigned int quantStrateg;
extern string arrStrategNames[];


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
    cout << "3 Изменить тип стратегии игры" << endl;
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
    cout << "Текущее значение: " << startMoney << " (стандартное значение: " << standartMoney << ")" << endl;
    cout << "Введите новый бюджет: " << endl;

    string str;
    getline(cin, str);
    string bufferNewMoney = "";

    for (char c : str) {
        if (isdigit(c)) {
            bufferNewMoney += c;
        }
    }

    if (bufferNewMoney == "") {
        cout << "Стартовый бюджет не изменён - нет цифр в строке, старое значение " << startMoney << endl;
    }
    else if (stoi(bufferNewMoney) < minPrice) {
        cout << "Стартовый бюджет не изменён - значение " << stoi(bufferNewMoney) <<" меньше цены наидешёвейшего бойца (" << minPrice << "), старое значение " << startMoney << endl;
    }
    else {
        startMoney = stoi(bufferNewMoney);
        cout << "Стартовый бюджет изменён и состовляет " << startMoney << endl;
    }
}

void editStrateg() {
    menuClear();
    cout << "3 Изменение типа стратегии игры" << endl;
    cout << endl;
    cout << "Текущее стратегия №" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
    cout << endl;
    cout << "Выберите новую стратегию (нажмите соотвествующую клавишу):" << endl;
    for (int i = 0; i < quantStrateg; i++) { cout << i + 1 << " " << arrStrategNames[i] << endl; } //печать стратегий

    char key;
    bool run = 1;
    while (run) {
start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            cout << endl;
            cout << "Изменение типа стратегии игры отменено" << endl;
            goto end;
            break;
        case k1:
            run = 0;
            typeStrateg = 0;
            break;
        case k2:
            run = 0;
            typeStrateg = 1;
            break;
        case k3:
            run = 0;
            typeStrateg = 2;
            break;
        default:
            goto start;
            break;
        } //switch

    } //while
    cout << endl;
    cout << "Выбрат тип стратегии №" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
end:
    return;
}

void outInfo() { //TONOTDO
    cout << "\t " << endl;
    void;
    return;
}

void startSimulation() {
    cout << "Создание команд..." << endl;
    Team team1(1);
    Team team2(2);

    menuClear();
    cout << "Комманы перед началом боя:" << endl;
    team1.print();
    team2.print();
    menuStop();

    unsigned int motion = 0; //Номер хода
    while (team1.len != 0 && team2.len != 0) { //Цикл боя
        //Ход
        team1.move0(team2);
        team2.move0(team1);

        //Результаты
        cout << ++motion << " ход: " << endl;
        team1.print();
        team2.print();

        //Удаление мёртвых
        team1.deleteDead();
        team2.deleteDead();
    }

    Team* team = (team2.len == 0 ? &team1 : &team2);
    cout << endl << endl << "Оставшиеся в победившей команде:" << endl;
    team->print();
    cout << endl << "Бой завершён, победила команда " << team->number << endl;
}


#endif
