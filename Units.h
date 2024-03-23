#pragma once
#ifndef VAROFVIKINGS_UNITS
#define VAROFVIKINGS_UNITS

#include <string>


extern int startMoney;

class BaseUnit; //-b Базовый воин

class LowUnit; //-l Лёгкий воин
class MediumUnit; //-m Среднйи воин
class HigtUnit; //-h Тяжёлый воин
class ArcherUnit; //-a Воин лучник

class HillerUnit; //-p Лечащий воин
class MagicUnit; //-c Копирующий воин


//Базовый воин
class BaseUnit {
protected:
	int health; //здоровье
	int MAX_HP; //переменная максимального здоровья
public:
	char type = 'b';
	int armor = 0; //броня
	int damage = 0; //урон
	int medication = 0; //Лечение
	float chanceDodge = 0; //шанс уклонения 1 = dodge
	int price; //цена
	int lenDamage = 0; //Расстояние использования урона
	int lenUse = 0; //Расстояние использования способностей
	float chanceUse = 1;

	void takeHealth(int health) {
		this->health + health > MAX_HP ? health = MAX_HP : this->health += health;
	}

	void takeDamage(int damage) {
		damage -= armor;
		chanceDodge * 100 > rand() % 100 ? damage = 0 : false; //Шанс промаха
		health - damage < 0 ? health = 0 : health -= damage;
	}

	int getHealth() { return health; }
};

//Лёгкий воин
class LowUnit : public BaseUnit {
public:
	LowUnit() {
		type = 'l';

		health = 25;
		armor = 0;
		damage = 30;
		medication = 0;
		chanceDodge = 0.5;
		lenDamage = 0;
		lenUse = 0;
		chanceUse = 1;

		price = 100;
		MAX_HP = health;
	}
};

//Среднйи воин
class MediumUnit : public BaseUnit {
public:
	MediumUnit() {
		type = 'm';

		health = 50;
		armor = 5;
		damage = 55;
		medication = 0;
		chanceDodge = 0.25;
		lenDamage = 0;
		lenUse = 0;
		chanceUse = 1;

		price = 250;
		MAX_HP = health;
	}
};

//Тяжёлый воин
class HigtUnit : public BaseUnit {
public:
	HigtUnit() {
		type = 'h';

		health = 100;
		armor = 25;
		damage = 95;
		medication = 0;
		chanceDodge = 0;
		lenDamage = 0;
		lenUse = 0;
		chanceUse = 1;

		price = 350;
		MAX_HP = health;
	}
};

//Воин лучник
class ArcherUnit : public BaseUnit {
public:
	ArcherUnit() {
		type = 'a';

		health = 25;
		armor = 0;
		damage = 30;
		medication = 0;
		chanceDodge = 0.25;
		lenDamage = 2;
		lenUse = 0;
		chanceUse = 1;

		price = 200;
		MAX_HP = health;
	}
};

//Лечащий воин
class HillerUnit : public BaseUnit {
public:
	HillerUnit() {
		type = 'p';

		health = 25;
		armor = 0;
		damage = 30;
		medication = 25;
		chanceDodge = 0;
		lenDamage = 0;
		lenUse = 1;
		chanceUse = 0.25;

		price = 150;
		MAX_HP = health;
	}
};

//Копирующий воин
class MagicUnit : public BaseUnit {
public:
	MagicUnit() {
		type = 'c';

		health = 25;
		armor = 0;
		damage = 30;
		medication = 0;
		chanceDodge = 0;
		lenDamage = 0;
		lenUse = 1;
		chanceUse = 1.0 / (startMoney / 250); //2500 sM -> 0.1, 25000 sM -> 0.01
		chanceUse > 0.875 ? chanceUse = 0.875 : false; /*Не даём шансу копирования стать слишком большим при малых деньгах
		и делаем его маленьким при большом количестве денег*/

		price = 400;
		MAX_HP = health;
	}
};


#endif
