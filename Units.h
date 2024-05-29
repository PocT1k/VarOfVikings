#pragma once
#ifndef VAROFVIKINGS_UNITS
#define VAROFVIKINGS_UNITS

#include <iostream>
#include <string>
#include <thread>

using namespace std;


extern ostream* logStream;
extern int startMoney; //Стартовые деньги, нужно для рандома копимага

void playDeadSound();
void timeSleep(int milliseconds = 1000);


class IBaseUnit; //-b Базовый воин

class LowUnit; //-l Лёгкий воин
class MediumUnit; //-m Среднйи воин
class HigtUnit; //-h Тяжёлый воин
class ArcherUnit; //-a Воин лучник
class HillerUnit; //-p Лечащий воин
class MagicUnit; //-c Копирующий воин


class IBaseUnit { //Базовый воин
protected:
	int health; //здоровье
	int MAX_HP; //переменная максимального здоровья
public:
	char type = 'b';
	int numberTeam = 0; //Номер команды - 1 или 2
	int armor = 0; //броня
	int damage = 0; //урон
	int medication = 0; //лечение
	float chanceDodge = 0; //шанс уклонения, 1 = dodge
	int price; //цена
	int lenDamage = 0; //Расстояние использования урона
	int lenUse = 0; //Расстояние использования способностей
	float chanceUse = 1;

	IBaseUnit(int numberTeam) { this->numberTeam = numberTeam; };
	void takeDamage(int damage); //Функция применения урона
	void takeHealth(int health); //Функция применения отхила

	//getters & setters
	int getHealth() { return health; }
	int getMAX_HP() { return MAX_HP; }
	virtual string getName() = 0;
};


class LowUnit : public IBaseUnit { //Лёгкий воин
public:
	LowUnit(int numberTeam);
	string getName() override { return "Лёгкий"; }
};


class MediumUnit : public IBaseUnit { //Среднйи воин
public:
	MediumUnit(int numberTeam);
	string getName() override { return "Средний"; }
};


class HigtUnit : public IBaseUnit { //Тяжёлый воин
public:
	int mod = 0; //Улучшение

	HigtUnit(int numberTeam);

	void upgrade(); //Функция прокачки
	string names[5] = { "ёлый", ".1", ".2", ".3", ".4" };
	string getName() override { return "Тяж" + names[mod]; }
};


class ArcherUnit : public IBaseUnit { //Воин лучник
public:
	ArcherUnit(int numberTeam);
	string getName() override { return "Лучник"; }
};


class HillerUnit : public IBaseUnit { //Лечащий воин
public:
	HillerUnit(int numberTeam);
	string getName() override { return "Хиллер"; }
};


class MagicUnit : public IBaseUnit { //Копирующий воин
public:
	MagicUnit(int numberTeam);
	string getName() override { return "Копимаг"; }
};


#endif
