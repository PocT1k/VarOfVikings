#include "Units.h"


void playDeadSound() {
	//cout << "\a";
}

void timeSleep(int milliseconds) {
	//this_thread::sleep_for(chrono::milliseconds(milliseconds));
}


void IBaseUnit::takeDamage(int damage) {
	if (health == 0) { return; } //�������, ���� ���� ��� ����
	if (chanceDodge * 100 > rand() % 100) { //���� �������
		if (logStream != nullptr) { (*logStream) << "  | " << getName() << " �� �" << numberTeam << " ��������� �� �����" << endl; }
		return;
	}

	damage -= armor; //��������� ���� �� �������� �����
	health -= damage; //��������� ����
	if (logStream != nullptr) { (*logStream) << "  V " << getName() << " �� �" << numberTeam << " ������� ���� " << damage << endl; }

	if (health <= 0) { //���� ����
		health = 0;
		playDeadSound();
		if (logStream != nullptr) { (*logStream) << " X " << getName() << " �� �" << numberTeam << " ����" << endl; }
	}
}

void IBaseUnit::takeHealth(int health) {
	if (this->health <= 0) { //���� ��������������� = 0, �� ���� ����, ����� �� ���������
		return;
	}
	this->health + health > MAX_HP ? health = MAX_HP : this->health += health;
	//���� ��������������� + ����� ������ ������������� => ��������������� = ������������, ����� ��������������� = ��������������� + �����
	if (logStream != nullptr) { (*logStream) << " H " << getName() << " �� �" << numberTeam << " ������� ������� " << health << endl; }
}

void IBaseUnit::upgrade() {
	if (mod != 0) { return; } //��� �������

	mod = rand() % 4 + 1; // �� 1 �� 4
	switch (mod) {
	case 1: //��������� ��������
		health = health + health * 0.5;
		MAX_HP *= 1.5;
		break;
	case 2: //��������� �����
		armor *= 2;
		break;
	case 3: //��������� �����
		damage *= 2.5;
		break;
	case 4: //��������� ����� ���������
		chanceDodge = 0.25;
		break;
	}
	if (logStream != nullptr) { (*logStream) << " U " << "������" << " �� �" << numberTeam << " ��������� �� " << getName() << endl; }
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
	chanceUseAbility = 0;

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
	chanceUseAbility = 0;

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
	chanceUseAbility = 1.0 / (startMoney / 250); //2500 sM => 0.1, 25000 sM => 0.01
	chanceUseAbility > 0.5 ? chanceUseAbility = 0.5 : false; /*�� ��� ����� ����� ������� ������� ��� ����� �������
	� ������ ��� ��������� ��� ������� ���������� ����� � ������*/

	price = 350;
	MAX_HP = health;
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
	chanceUseAbility = 0;

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
	chanceUseAbility = 0.25;

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
	chanceUseAbility = 1.0 / (startMoney / 250); //2500 sM => 0.1, 25000 sM => 0.01
	chanceUseAbility > 0.5 ? chanceUseAbility = 0.5 : false; /*�� ��� ����� ����� ������� ������� ��� ����� �������
	� ������ ��� ��������� ��� ������� ���������� ����� � ������*/

	price = 400;
	MAX_HP = health;
}
