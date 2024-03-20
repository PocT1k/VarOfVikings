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
public:
	char type = 'b';
	int health; //��������
	int MAX_HP; //���������� ������������� ��������
	int armor; //�����
	int damage; //����
	float chanceDodge = 0; //���� ��������� 1 = dodge
	int price; //����
};

//˸���� ����
class LowUnit : public BaseUnit {
public:
	LowUnit() {
		type = 'l';
		health = 25;
		MAX_HP = health;
		armor = 0;
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
		chanceDodge = 0;
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
		armor = 0;
		damage = 30;
		chanceDodge = 0.25;
		price = 200;
	}
	int lenUse = 2;
};

//������� ����
class HillerUnit : public BaseUnit {
public:
	HillerUnit() {
		type = 'p';
		health = 25;
		MAX_HP = health;
		armor = 0;
		damage = -20;
		chanceDodge = 0;
		price = 150;
	}
	int lenUse = 2;
	float chanceUse = 0.5;
};

//���������� ����
class MagicUnit : public BaseUnit {
public:
	MagicUnit() {
		type = 'c';
		health = 25;
		MAX_HP = health;
		armor = 0;
		damage = 0;
		chanceDodge = 0;
		price = 400;
	}
	int lenUse = 1;
	float chanceUse = 0.125;
};


#endif
