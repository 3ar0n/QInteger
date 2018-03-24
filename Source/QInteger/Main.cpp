#include "QInt.h"
#include "Convert.h"
#include "Operator.h"
#include "Input_Output.h"

//Hàm xuất (DEC, HEX, BIN)
void outPut_QInt(QInt x)
{
	//Thập phân
	string Dec = ByteToDec(x);
	cout << "DEC" << endl;
	cout << Dec << "    " << endl << endl;

	//Thập lục phân
	char* Hex = ByteToHex(x);
	cout << "HEX" << endl;
	if (Hex)
	{
		for (int i = 0; i < 32; i++)
		{
			if (i % 4 == 0 && i > 0)
				cout << " ";
			cout << Hex[i];
		}
		delete[] Hex;
	}
	else
		cout << "overflow";

	//Nhị phân
	bool* Bin = ByteToBin(x);
	cout << endl << endl << "BIN" << endl;
	if (Bin)
	{
		for (int i = 0; i < 128; i++)
		{
			if (i % 4 == 0 && i > 0)
				cout << " ";
			cout << Bin[i];
		}
		delete[] Bin;
	}
	else
		cout << "overflow";
	cout << endl << endl;
}

// Xử lý theo tham số dòng lệnh cmd
int main(int argc, char **argv)
{
	// test giá trị (giả sử chuỗi nhập vào và các phép tính đều hợp lệ - không cần kiểm tra)
	string a = "1234567890";
	string b = "-123456789";
	QInt A = DecToByte(a);
	QInt B = DecToByte(b);

	cout << a << " * " << b << " =" << endl << endl;
	outPut_QInt(A * B);
	// END test

	_getch();
	return 0;
}