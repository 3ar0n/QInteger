#pragma once

#include "QInt.h"

// Lấy giá trị bit trong 1 phần tử Base256 (mảng QInt)
bool getBit(unsigned char byte, int position);

// Chuỗi nhị phân dạng "string" -> "bool" (hỗ trợ BIN -> Base256)
bool* BinStringToBool(string s);

// giá trị thập phân <-> kí tự thập lục phân
char NumberToHex(int n);
int HexToNumber(char ch);

// Lấy số bù 2
QInt Minus(QInt x);

// Kiểm tra số âm/dương (DEC)
int CheckSign(string s);

// DEC -> BIN

// DEC -> HEX

// BIN -> DEC

// BIN -> HEX

/*
Thực hiện chuyển đổi thông qua Base256
*/

// DEC/BIN/HEX <-> Base256
QInt DecToByte(string s);
QInt BinToByte(bool *bit);
QInt HexToByte(string s);
string ByteToDec(QInt x);
bool* ByteToBin(QInt x);
char* ByteToHex(QInt x);

/*
CÁCH CHUYỂN CƠ SỐ BASE256 -> DEC
	Số X trình bày ở Base256 có dạng [a0 a1 a2 .... ai] (với a(i) = [0,255] và i = [0,15] )
	S1, S2... là các chuỗi "string" biểu diễn dạng thập phân, ta có:
	S1  = 256 * S0 + a0 = a0		(với S0 = 0)
	S2  = 256 * S1 + a1
	...
	S16 = 256 * Si + ai
	Chuỗi S16 chính là chuỗi biểu diễn thập phân của X
*/