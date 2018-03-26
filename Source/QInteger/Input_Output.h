#pragma once

#include "QInt.h"
#include "Convert.h"
#include "Operator.h"

QInt ConvertResult(int source_base, string source_value);	// Đọc chuỗi (ứng với cơ số), lưu giá trị QInt
void ReadAndWriteFile(ifstream& f, ofstream& g);			// Đọc và ghi file .txt