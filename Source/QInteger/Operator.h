#pragma once

#include "QInt.h"

// Phép + - * /
QInt operator + (QInt a, QInt b);
QInt operator - (QInt a, QInt b);
QInt operator * (QInt a, QInt b);
QInt operator / (QInt a, QInt b);

// Phép AND, OR, NOT

// Phép dịch trái/phải
QInt operator << (QInt a, int shift);
QInt operator >> (QInt a, int shift);