#pragma once
#ifndef VAROFVIKINGS_TEAM
#define VAROFVIKINGS_TEAM

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

#include "Units.h"

using namespace std;


#define COUNT_OF_UNITS 6

extern int startMoney;
extern int minPriceUnit;
extern float medLenShild;
extern float medHealthShield;
extern ostream* logStream;
extern HANDLE hConsole;


class Team;

class Team { //Команда
public:
	int numberTeam = 0; //Номер команды - 1 или 2
	int moneyTeam = 0; //Money, money, money	Must be funny	In the rich man's world
	int lenTeam = 0; //Количество оставшихся воинов, 0 - команда закончилась и проиграла
	vector<shared_ptr<IBaseUnit>> units; //Вектор с воинами

	int ptrShield = 0; //Начало щита
	int lenShield = 0; //Длинна щита
	int healthShield = 0; //Здоровье щита

	Team(int number); //Создание команды (вся генерация воинов и щита в конструкторе)
	shared_ptr<IBaseUnit> generateUnit(int number); //Сгенерировать воина
	void generateShield(); //Сгенерировать щит

	void takeDamage(int damage); //Функция применения урона для щита команды
	int getUnitNumber(shared_ptr<IBaseUnit> unit); //Узнать №пп воина
	bool isUnderShield(shared_ptr<IBaseUnit> unit); //Узнать под щитом воин или инет
	void print(); //Печать команды
	void deleteDead(); //Удаление мёртвых бойцов
	void moveMagic(); //Ходят маги
	void UpgradeHigt1(); //Улучшаются тяжёлые первый способ
	void move0(Team& enemies); //Ход первой стратегией
	void move1(Team& enemies); //Ход второй стратегией
	void move2(Team& enemies); //Ход третьей стратегией
};


#endif
