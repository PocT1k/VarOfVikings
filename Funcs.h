#pragma once
#ifndef VAROFVIKINGS_FUNCS
#define VAROFVIKINGS_FUNCS

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <random>

#include "Team.h"

using namespace std;


#define COUNT_OF_STRATEG 3
#define COUNT_OF_STREAM 3

#define kESC 27
#define kSPACE 32
#define kENTER 13
#define kBACKSPACE 8
#define k0 48
#define k1 49
#define k2 50
#define k3 51
#define k4 52
#define k5 53
#define k6 54
#define k7 55
#define k8 56
#define k9 57


void printCommands();
void menuStop();
void menuClear();
void editMoney();
void editStrateg();
void editStream();
void outInfo();
void runSimulation();


#endif
