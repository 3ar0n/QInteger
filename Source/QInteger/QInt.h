#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#define ArraySize (int)15
#define Byte (int)8
#define _Bin (int)2
#define _Dec (int)10
#define _Hex (int)16

struct QInt
{
	unsigned char data[ArraySize];
	bool overflow;
};