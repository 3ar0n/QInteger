#include "Input_Output.h"

// Đọc chuỗi (ứng với cơ số), lưu giá trị QInt
QInt ConvertToQInt(int source_base, string source_value)
{
	QInt result;
	switch (source_base)
	{
	case _Bin:
		result = BinToQInt(BinStringToBool(source_value));
		break;
	case _Dec:
		result = DecToQInt(source_value);
		break;
	case _Hex:
		result = HexToQInt(source_value);
		break;
	}
	return result;
}

// Xuất giá trị QInt thành chuỗi (ứng với cơ số)
void ConvertFromQInt(int dest_base, QInt a, ofstream& output)
{
	if (a.overflow)
		output << "Overflow" << endl;
	else
	{
		switch (dest_base)
		{
		case _Dec:
			output << QIntToDec(a) << endl;
			break;
		case _Bin:
			output << ClearZero(QIntToBin(a)) << endl;
			break;
		case _Hex:
			output << ClearZero(QIntToHex(a)) << endl;
			break;
		}
	}
}

// Đọc và ghi file
void ReadAndWriteFile(ifstream& f, ofstream& g)
{
	string str;
	while (getline(f, str, '\n'))
	{
		stringstream ss;
		ss.str(str);
		vector<string> ds;
		string temp;
		while (getline(ss, temp, ' '))
		{
			ds.push_back(temp);
		}
		int dem = atoi(ds[0].c_str());	// Xác định cơ số cần thao tác (BIN, DEC, HEX)	

		if (ds.size() == 4)	// Toán tử 2 ngôi (+ - * / & | ^ >> <<)
		{
			QInt a = ConvertToQInt(dem, ds[1]);
			QInt b, result;
			int shift;

			/*
			Trường hợp toán tử >> và <<, tham số thứ 4 là số bit dịch "shift"
			Các trường hợp còn lại, tham số thứ 4 là giá trị b
			*/
			if ((ds[2] == "<<") || (ds[2] == ">>"))
			{
				shift = atoi(ds[3].c_str());
				result = OperationResult(ds[2], a, b, shift);
			}
			else
			{
				b = ConvertToQInt(dem, ds[3]);
				result = OperationResult(ds[2], a, b);
			}
			ConvertFromQInt(dem, result, g);
		}
		else if (ds.size() == 3)	// Toán tử 1 ngôi (~) hoặc đổi cơ số
		{
			QInt a = ConvertToQInt(dem, ds[2]);
			int dest_base;

			if (ds[1] == "~")
			{
				a = ~a;
				dest_base = dem;
			}
			else
				dest_base = atoi(ds[1].c_str());
			ConvertFromQInt(dest_base, a, g);
		}
	}
}