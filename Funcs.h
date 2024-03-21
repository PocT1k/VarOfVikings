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
    cout << "������� �������������� �������:" << endl;
    cout << "1 ��������� ���������" << endl;
    cout << "2 �������� ��������� ������" << endl;
    //cout << "3 ������ ����������" << endl;
    cout << "ESC ���������� ���������" << endl;
}

void menuStop() {
    cout << endl << "��� ����������� ������ ������� ENTER" << endl;
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
    cout << "2 ��������� ���������� �������" << endl;
    cout << endl;
    cout << "������� ����� ������: " << endl;

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
        cout << "��������� ������ �� ������ - ��� ���� � ������, ������ �������� " << startMoney << endl;
    }
    else {
        res = stoi(newMoney);
        cout << "��������� ������ ������ � ���������� " << res << endl;
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
    cout << "  �" << team << ": ";
    for (const auto& unit : units) {
        switch (unit->type) {
        case 'l':
            cout << "˸����" << " "; break;
        case 'm':
            cout << "�������" << " "; break;
        case 'h':
            cout << "������" << " "; break;
        case 'a':
            cout << "������" << " "; break;
        case 'p':
            cout << "������" << " "; break;
        case 'c':
            cout << "�������" << " "; break;
        default:
            break;
        }
    }
    cout << "(" << units.size() << ")" << endl;
}

void startSimulation() {
    //�������������
    int moneyTeam_1 = startMoney;
    int moneyTeam_2 = startMoney;
    int lenTeam_1 = 0;
    int lenTeam_2 = 0;
    vector<shared_ptr<BaseUnit>> unitsTeam_1;
    vector<shared_ptr<BaseUnit>> unitsTeam_2;
    
    //���������� �����
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
    cout << "������� ����� ������� ���: " << endl;
    printTeam(unitsTeam_1, 1);
    printTeam(unitsTeam_2, 2);
    menuStop();

    int fullDamage = 0;
    int fullHealth = 0;
    int index = 0;
    int motion = 0;

    //���� ���
    while (lenTeam_1 != 0 && lenTeam_2 != 0) {
        //��� 1 �������
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
                            unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->damage : fullHealth; //���� ����
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
            unitsTeam_2[0]->takeDamage(fullDamage); //���������� ������
            unitsTeam_1[0]->takeHealth(fullHealth); //���������� ����

            index = 0;
            fullDamage = 0;
            fullHealth = 0;

            //�������� �����
            if (!unitsTeam_2[0]->getHealth()) {
                unitsTeam_2.erase(unitsTeam_2.begin());
                lenTeam_2--;
            }
        }

        //��� 2 �������
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
                            unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->damage : fullHealth += 0; //���� ����
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
            unitsTeam_1[0]->takeDamage(fullDamage); //���������� ������
            unitsTeam_2[0]->takeHealth(fullHealth); //���������� ����

            index = 0;
            fullDamage = 0;
            fullHealth = 0;

            //�������� �����
            if (!unitsTeam_1[0]->getHealth()) {
                unitsTeam_1.erase(unitsTeam_1.begin());
                lenTeam_1--;
            }
        }

        //����������
        cout << ++motion << " ���: " << endl;
        printTeam(unitsTeam_1, 1);
        printTeam(unitsTeam_2, 2);
    }

    cout << endl << "��� ��������, �������� ������� " << (unitsTeam_1.empty() ? 2 : 1) << endl;
}


#endif
