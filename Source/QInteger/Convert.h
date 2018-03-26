#pragma once

#include "QInt.h"

bool getBit(unsigned char byte, int position);		// Lấy giá trị bit trong 1 phần tử Base256 (mảng QInt)
bool* BinStringToBool(string s);					// Chuỗi nhị phân dạng "string" -> "bool" (hỗ trợ BIN -> Base256)
string ClearZero(char* s);							// Loại bỏ các số 0 ở đầu trong chuỗi HEX
string ClearZero(bool* s);							// Loại bỏ các số 0 ở đầu trong chuỗi BIN
char NumberToHex(int n);							// giá trị thập phân -> kí tự thập lục phân
int HexToNumber(char ch);							// kí tự thập lục phân -> giá trị thập phân
QInt Minus(QInt x);									// Lấy số bù 2
int CheckSign(string s);							// Kiểm tra số âm/dương (chuỗi DEC)
		
QInt DecToQInt(string s);							// DEC/BIN/HEX <-> Base256				
QInt BinToQInt(bool *bit);
QInt HexToQInt(string s);
string QIntToDec(QInt x);
bool* QIntToBin(QInt x);
char* QIntToHex(QInt x);

/* CÁCH CHUYỂN CƠ SỐ BASE256 -> DEC
	Số X trình bày ở Base256 có dạng [a0 a1 a2 .... ai] (với a(i) = [0,255] và i = [0,15] )
	S1, S2... là các chuỗi "string" biểu diễn dạng thập phân, ta có:
	S1  = 256 * S0 + a0 = a0		(với S0 = 0)
	S2  = 256 * S1 + a1
	...
	S16 = 256 * Si + ai
	Chuỗi S16 chính là chuỗi biểu diễn thập phân của X
*/