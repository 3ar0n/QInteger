#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

#define Base (int)16
#define Byte (int)8
#define _Bin (int)2
#define _Dec (int)10
#define _Hex (int)16

struct QInt
{
	unsigned char data[Base];
	bool overflow;
};

//void ScanQInt(QInt &x);
//void PrintQInt(QInt x);