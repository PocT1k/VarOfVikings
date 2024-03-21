#pragma once
#ifndef VAROFVIKINGS_UNITS
#define VAROFVIKINGS_UNITS

//#include <iostream>


class BaseUnit; //-b ������� ����

class LowUnit; //-l ˸���� ����
class MediumUnit; //-m ������� ����
class HigtUnit; //-h ������ ����
class ArcherUnit; //-a ���� ������

class HillerUnit; //-p ������� ����
class MagicUnit; //-c ���������� ����


//������� ����
class BaseUnit {
protected:
	int health; //��������
	int MAX_HP; //���������� ������������� ��������
public:
	char type = 'b';
	int armor = 0; //�����
	int damage = 0; //����
	float chanceDodge = 0; //���� ��������� 1 = dodge
	int price; //����
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

//˸���� ����
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

//������� ����
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

//������ ����
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

//���� ������
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

//������� ����
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

//���������� ����
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
