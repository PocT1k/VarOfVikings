#pragma once
#ifndef VAROFVIKINGS_FUNCS
#define VAROFVIKINGS_FUNCS

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <random>

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

void printCommands();
void menuStop();
void menuClear();
int editMoney();
void printTeam(const vector<shared_ptr<BaseUnit>> units, int team);
shared_ptr<BaseUnit> randomUnit(int& startMoney);
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

int editMoney() {
    menuClear();
    cout << "2 Изменение стартового бюджета" << endl;
    cout << endl;
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
    return res;
}


shared_ptr<BaseUnit> randomUnit(int& startMoney) {
    int i = rand() % 6;

    switch (i) {
    case 0:
        if (startMoney < 100) { return nullptr; }
        else { startMoney -= 100; return make_shared<LowUnit>(); }
        break;
    case 1:
        if (startMoney < 250) { return nullptr; }
        else { startMoney -= 250; return make_shared<MediumUnit>(); }
        break;
    case 2:
        if (startMoney < 350) { return nullptr; }
        else { startMoney -= 350; return make_shared<HigtUnit>(); }
        break;
    case 3:
        if (startMoney < 200) { return nullptr; }
        else { startMoney -= 200; return make_shared<ArcherUnit>(); }
        break;
    case 4:
        if (startMoney < 150) { return nullptr; }
        else { startMoney -= 150; return make_shared<HillerUnit>(); }
        break;
    case 5:
        if (startMoney < 400) { return nullptr; }
        else { startMoney -= 400; return make_shared<MagicUnit>(); }
        break;
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

void printTeam(const vector<shared_ptr<BaseUnit>> units, int team) {
    cout << "  к" << team << ": ";
    for (const auto& unit : units) {
        switch (unit->type) {
        case 'l':
            cout << "Лёгкий" << " "; break;
        case 'm':
            cout << "Средний" << " "; break;
        case 'h':
            cout << "Тяжёлый" << " "; break;
        case 'a':
            cout << "Лучник" << " "; break;
        case 'p':
            cout << "Хиллер" << " "; break;
        case 'c':
            cout << "Копимаг" << " "; break;
        default:
            break;
        }
    }
    cout << "(" << units.size() << ")" << endl;
}

void startSimulation() {
    //Инициализация
    int moneyTeam_1 = startMoney;
    int moneyTeam_2 = startMoney;
    int lenTeam_1 = 0;
    int lenTeam_2 = 0;
    vector<shared_ptr<BaseUnit>> unitsTeam_1;
    vector<shared_ptr<BaseUnit>> unitsTeam_2;
    
    //Заполнение войск
    while (moneyTeam_1 >= 100) {
        shared_ptr<BaseUnit> tempUnit = randomUnit(moneyTeam_1);
        if (tempUnit != nullptr) {
            lenTeam_1++;
            unitsTeam_1.push_back(tempUnit);
        }
    }
    while (moneyTeam_2 >= 100) {
        shared_ptr<BaseUnit> tempUnit = randomUnit(moneyTeam_2);
        if (tempUnit != nullptr) {
            lenTeam_2++;
            unitsTeam_2.push_back(tempUnit);
        }
    }

    menuClear();
    cout << "Комманы перед началом боя: " << endl;
    printTeam(unitsTeam_1, 1);
    printTeam(unitsTeam_2, 2);
    menuStop();

    int fullDamage = 0;
    int fullHealth = 0;
    int index = 0;
    int motion = 0;

    //Цикл боя
    while (lenTeam_1 != 0 && lenTeam_2 != 0) {
        //Ход 1 команды
        if (!unitsTeam_1.empty() && !unitsTeam_2.empty()) {
            for (auto unit : unitsTeam_1) {
                switch (unit->type) {
                case 'l':
                case 'm':
                case 'h':
                case 'a':
                case 'p':
                    if (unit->lenUse >= index) {
                        if (unit->type == 'p') {
                            unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->damage : fullHealth; //Шанс хила
                        }
                        else {
                            fullDamage += unit->damage;
                        }
                    }
                    break;
                case 'c':
                    break;
                default:
                    break;
                }

                index++;
            }
            unitsTeam_2[0]->takeDamage(fullDamage); //Применение дамага
            unitsTeam_1[0]->takeHealth(fullHealth); //Применение хила

            index = 0;
            fullDamage = 0;
            fullHealth = 0;

            //Удаление бойца
            if (!unitsTeam_2[0]->getHealth()) {
                unitsTeam_2.erase(unitsTeam_2.begin());
                lenTeam_2--;
            }
        }

        //Ход 2 команды
        if (!unitsTeam_1.empty() && !unitsTeam_2.empty()) {
            for (auto unit : unitsTeam_2) {
                switch (unit->type) {
                case 'l':
                case 'm':
                case 'h':
                case 'a':
                case 'p':
                    if (unit->lenUse >= index) {
                        if (unit->type == 'p') {
                            unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->damage : fullHealth += 0; //Шанс хила
                        }
                        else {
                            fullDamage += unit->damage;
                        }
                    }
                    break;
                case 'c':
                    break;
                default:
                    break;
                }

                index++;
            }
            unitsTeam_1[0]->takeDamage(fullDamage); //Применение дамага
            unitsTeam_2[0]->takeHealth(fullHealth); //Применение хила

            index = 0;
            fullDamage = 0;
            fullHealth = 0;

            //Удаление бойца
            if (!unitsTeam_1[0]->getHealth()) {
                unitsTeam_1.erase(unitsTeam_1.begin());
                lenTeam_1--;
            }
        }

        //Результаты
        cout << ++motion << " ход: " << endl;
        printTeam(unitsTeam_1, 1);
        printTeam(unitsTeam_2, 2);
    }

    cout << endl << "Бой завершён, победила команда " << (unitsTeam_1.empty() ? 2 : 1) << endl;
}


#endif
