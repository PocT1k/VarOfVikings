#pragma once
#ifndef VAROFVIKINGS_TEAM
#define VAROFVIKINGS_TEAM

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

#include "Units.h"

using namespace std;


extern int startMoney;
extern IBaseUnit* unitsArr[6];
extern int prices[6];
extern int minPrice;


class Team;


class Team { //Команда
public:
	int number = 0; //Номер команды - 1 или 2
	int money = 0; //Money, money, money	Must be funny	In the rich man's world
	int len = 0; //Количество оставшихся воинов, 0 - команда закончилась и проиграла
	vector<shared_ptr<IBaseUnit>> units; //Вектор с воинами

	int ptrShield = 3; //Начало щита
	int lenShield = 2; //Длинна щита
	int healthShield; //Здоровье щита

	Team(int number); //Создание команды, всё в конструкторе
	shared_ptr<IBaseUnit> randomUnit(); //Сгенерировать воина
	int getUnitNumber(shared_ptr<IBaseUnit> unit);
	bool isUnderShield(shared_ptr<IBaseUnit> unit); //Узнать под щитом воин или инет
	void print(); //Печать команды
	void deleteDead(); //Удаление мёртвых бойцов
	void move0(Team& enemies); //Ход первой стратегией
};


#endif
