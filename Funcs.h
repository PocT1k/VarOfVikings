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

void printCommands();
void menuStop();
void menuClear();
void editMoney();
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
    //system("CLS");
}

void editMoney() {
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
    startMoney = res;
}


void startSimulation() {
    Team team1(1);
    Team team2(2);

    menuClear();
    cout << "������� ����� ������� ���: " << endl;
    team1.print();
    team2.print();
    menuStop();

    int motion = 0;
    while (team1.len != 0 && team2.len != 0) { //���� ���
        team1.move(team2);
        team2.move(team1);

        //����������
        cout << ++motion << " ���: " << endl;
        team1.print();
        team2.print();
    }

    cout << endl << "��� ��������, �������� ������� " << (team2.len == 0 ? 1 : 2) << endl;
}


#endif
