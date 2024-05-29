#include "Units.h"


void playDeadSound() {
	cout << "\a";
	//this_thread::sleep_for(chrono::seconds(1));
}


void IBaseUnit::takeDamage(int damage) {
	if (health == 0) { //�������, ���� ���� ��� ����
		return;
	}
	if (chanceDodge * 100 > rand() % 100) { //���� �������
		if (logStream != nullptr) { (*logStream) << "�" << numberTeam << endl; }
		return;
	}

	damage -= armor; //��������� ���� �� �������� �����
	health -= damage; //��������� ����
	if (health <= 0) { //���� ����
		health = 0;
		playDeadSound();
	}
}

//void Team::takeDamage(int damage) { //������� ���������� ����� ��� ���� �������
//	if (healthShield == 0) { return; } //�������, ���� ��� ��� �����
//	healthShield -= damage; //��������� ����
//	if (logStream != nullptr) { (*logStream) << "��� ������� �" << numberTeam << " ������� ���� " << damage << endl; }
//
//	if (healthShield <= 0) { //��������� �� ������ �� ���. ���� ��, �� ������� ���
//		healthShield = 0;
//		lenShield = 0;
//		if (logStream != nullptr) { (*logStream) << "��� ������� �" << numberTeam << " ������" << endl; }
//	}
//}

void IBaseUnit::takeHealth(int health) {
	if (this->health <= 0) { //���� ��������������� = 0, �� ���� ����, ����� �� ���������
		return;
	}
	this->health + health > MAX_HP ? health = MAX_HP : this->health += health;
	//���� ��������������� + ����� ������ ������������� => ��������������� = ������������, ����� ��������������� = ��������������� + �����
}


LowUnit::LowUnit(int numberTeam) : IBaseUnit(numberTeam) {
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

MediumUnit::MediumUnit(int numberTeam) : IBaseUnit(numberTeam) {
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

HigtUnit::HigtUnit(int numberTeam) : IBaseUnit(numberTeam) {
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

void HigtUnit::upgrade() { //TODO
	return;
}

ArcherUnit::ArcherUnit(int numberTeam) : IBaseUnit(numberTeam) {
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

HillerUnit::HillerUnit(int numberTeam) : IBaseUnit(numberTeam) {
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

MagicUnit::MagicUnit(int numberTeam) : IBaseUnit(numberTeam) {
	type = 'c';

	health = 25;
	armor = 0;
	damage = 30;
	medication = 0;
	chanceDodge = 0;
	lenDamage = 0;
	lenUse = 1;
	chanceUse = 1.0 / (startMoney / 250); //2500 sM => 0.1, 25000 sM => 0.01
	chanceUse > 0.5 ? chanceUse = 0.5 : false; /*�� ��� ����� ����������� ����� ������� ������� ��� ����� �������
	� ������ ��� ��������� ��� ������� ���������� ����� � ������*/

	price = 400;
	MAX_HP = health;
}
