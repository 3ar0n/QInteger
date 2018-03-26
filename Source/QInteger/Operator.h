#pragma once

#include "QInt.h"

QInt operator + (QInt a, QInt b);		// Cộng
QInt operator - (QInt a, QInt b);		// Trừ
QInt operator * (QInt a, QInt b);		// Nhân
QInt operator / (QInt a, QInt b);		// Chia
QInt operator & (QInt a, QInt b);		// AND
QInt operator | (QInt a, QInt b);		// OR
QInt operator ^ (QInt a, QInt b);		// XOR
QInt operator ~ (QInt a);				// NOT
QInt operator << (QInt a, int shift);	// Dịch trái
QInt operator >> (QInt a, int shift);	// Dịch phải
QInt OperationResult(string operation, QInt a, QInt b, int shift = 0);	// Thực hiện các phép toán 2 ngôi