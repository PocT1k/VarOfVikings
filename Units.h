#pragma once
#ifndef VAROFVIKINGS_UNITS
#define VAROFVIKINGS_UNITS

//#include <iostream>


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
	float chanceDodge = 0; //шанс уклонения 1 = dodge
	int price; //цена
	int lenUse = 0;
	float chanceUse;

	void takeHealth(int health) {
		this->health + health > MAX_HP ? health = MAX_HP : this->health += health;
	}

	void takeDamage(int damage) {
		this->health - damage < 0 ? health = 0 : this->health -= damage;
	}

	int getHealth() { return this->health; }
};

//Лёгкий воин
class LowUnit : public BaseUnit {
public:
	LowUnit() {
		type = 'l';
		health = 25;
		MAX_HP = health;
		damage = 30;
		chanceDodge = 0.5;
		price = 100;
	}
};

//Среднйи воин
class MediumUnit : public BaseUnit {
public:
	MediumUnit() {
		type = 'm';
		health = 50;
		MAX_HP = health;
		armor = 5;
		damage = 55;
		chanceDodge = 0.25;
		price = 250;
	}
};

//Тяжёлый воин
class HigtUnit : public BaseUnit {
public:
	HigtUnit() {
		type = 'h';
		health = 100;
		MAX_HP = health;
		armor = 25;
		damage = 95;
		price = 350;
	}
};

//Воин лучник
class ArcherUnit : public BaseUnit {
public:
	ArcherUnit() {
		type = 'a';
		health = 25;
		MAX_HP = health;
		damage = 30;
		chanceDodge = 0.25;
		price = 200;
		lenUse = 2;
	}
};

//Лечащий воин
class HillerUnit : public BaseUnit {
public:
	HillerUnit() {
		type = 'p';
		health = 25;
		MAX_HP = health;
		damage = 20;
		price = 150;
		lenUse = 2;
		chanceUse = 0.5;
	}
};

//Копирующий воин
class MagicUnit : public BaseUnit {
public:
	MagicUnit() {
		type = 'c';
		health = 25;
		MAX_HP = health;
		price = 400;
		lenUse = 1;
		chanceUse = 0.125;
	}
};


#endif
