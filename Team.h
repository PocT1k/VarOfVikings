#pragma once
#ifndef VAROFVIKINGS_TEAM
#define VAROFVIKINGS_TEAM

#include <iostream>
#include <vector>

#include "Units.h"

using namespace std;


extern int startMoney;
extern int prices[6];
extern int minPrice;


class Team;


class Team {
public:
	int number = 0;
	int money = 0;
	int len = 0;
	vector<shared_ptr<BaseUnit>> units;

	Team(int number);
	shared_ptr<BaseUnit> randomUnit();
	void print();
	void move(Team& enemies);
};


#endif
