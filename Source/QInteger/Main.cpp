#include "QInt.h"
#include "Convert.h"
#include "Operator.h"
#include "Input_Output.h"

// Hàm xuất chuỗi thể hiện (DEC, HEX, BIN) giá trị của số QInt lên màn hình console 
void outPut_QInt(QInt x)
{
	//Thập phân
	string Dec = ByteToDec(x);
	//cout << endl << "DEC  ";
	cout << Dec << "    " << endl << endl;

	//Thập lục phân
	//char* Hex = ByteToHex(x);
	//cout << "HEX  ";
	//if (Hex)
	//{
	//	for (int i = 0; i < 32; i++)
	//	{
	//		if (i % 4 == 0 && i > 0)
	//			cout << " ";
	//		cout << Hex[i];
	//	}
	//	delete[] Hex;
	//}
	//else
	//	cout << "overflow";
	//cout << endl;

	//Nhị phân
	bool* Bin = ByteToBin(x);
	cout << "BIN  ";
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
	// test các phép toán và xuất ra màn hình console
	//string a = "0";
	//string b = "-1";
	//QInt A = DecToByte(a);
	//QInt B = DecToByte(b);

	//cout << "a = ";
	//outPut_QInt(A);

	//cout << "b = ";
	//outPut_QInt(B);

	//cout << a << " + " << b << " = ";
	//outPut_QInt(A + B);
	//cout << a << " - " << b << " = ";
	//outPut_QInt(A - B);
	//cout << a << " * " << b << " = ";
	//outPut_QInt(A * B);
	//cout << a << " / " << b << " = ";
	//outPut_QInt(A / B);

	//int shift = 3;
	//cout << b << " << " << shift << " = ";
	//outPut_QInt(B << shift);
	//cout << b << " >> " << shift << " = ";
	//outPut_QInt(B >> shift);

	//cout << a << " & " << b << " = ";
	//outPut_QInt(A & B);
	//cout << a << " | " << b << " = ";
	//outPut_QInt(A | B);
	//cout << a << " ^ " << b << " = ";
	//outPut_QInt(A ^ B);
	//cout << " ~ " << b << " = ";
	//outPut_QInt(~ B);
	// END test

	// test không dùng tham số dòng lệnh
	//ifstream f("input.txt");
	//ofstream g("output.txt");
	//if (f)
	//{
	//	ReadAndWriteFile(f, g);
	//	f.close();
	//	cout << "Da Chay Xong" << endl;
	//}
	//else
	//{
	//	cout << "Khong tim thay file input" << endl;
	//}
	//g.close();
	// END test

	//_getch();

	if (argc != 3)
	{
		cout << "Nhap sai cu phap" << endl;
	}
	else
	{
		ifstream f(argv[1]);
		ofstream g(argv[2]);
		if (f && g)
		{
			ReadAndWriteFile(f, g);
			f.close();
			g.close();
			cout << "Da chay xong" << endl;
		}
		else
		{
			cout << "Nhap sai cu phap hoac khong tim thay input" << endl;
			if (f)
				f.close();
			if (g)
				g.close();
		}
		
	}
	return 0;
}