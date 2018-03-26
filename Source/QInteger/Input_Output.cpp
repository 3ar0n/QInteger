#include "Input_Output.h"

// Đọc chuỗi (ứng với cơ số), lưu giá trị QInt
QInt ConvertResult(int source_base, string source_value)
{
	QInt result;
	switch (source_base)
	{
	case _Bin:
		result = BinToByte(BinStringToBool(source_value));
		break;
	case _Dec:
		result = DecToByte(source_value);
		break;
	case _Hex:
		result = HexToByte(source_value);
		break;
	}
	return result;
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
			int dem = atoi(ds[0].c_str());	// Xác định cơ số cần thao tác (BIN, DEC, HEX)	

			if (ds.size() == 4)	// Toán tử 2 ngôi (+ - * / & | ^ >> <<)
			{
				QInt a = ConvertResult(dem, ds[1]);
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
					b = ConvertResult(dem, ds[3]);
					result = OperationResult(ds[2], a, b);
				}

				// Chuyển cơ số và ghi file
				if (dem == _Bin)
					g << ClearZero(ByteToBin(result)) << endl;
				else if (dem == _Hex)
					g << ClearZero(ByteToHex(result)) << endl;
				else if (dem == _Dec)
					g << ByteToDec(result) << endl;
			}
			if (ds.size() == 3)	// Toán tử 1 ngôi (~) hoặc đổi cơ số
			{
				QInt a = ConvertResult(dem, ds[2]);
				int dest_base;

				if (ds[1] == "~")
				{
					a = ~a;
					dest_base = dem;
				}
				else
					dest_base = atoi(ds[1].c_str());

				// Chuyển cơ só và ghi file
				if (dest_base == _Dec)
					g << ByteToDec(a) << endl;
				else if (dest_base == _Bin)
					g << ClearZero(ByteToBin(a)) << endl;
				else if (dest_base == _Hex)
					g << ClearZero(ByteToHex(a)) << endl;
			}
		}
	}
}