#pragma once

#include "QInt.h"
#include "Convert.h"
#include "Operator.h"

QInt ConvertToQInt(int source_base, string source_value);		// Đọc chuỗi (ứng với cơ số), lưu giá trị QInt
void ConvertFromQInt(int dest_base, QInt a, ofstream& output);	// Ghi chuỗi (ứng với cơ số) của giá trị QInt
void ReadAndWriteFile(ifstream& f, ofstream& g);				// Đọc và ghi file .txt