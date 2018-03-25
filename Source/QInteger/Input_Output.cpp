#include "Input_Output.h"

//doc file
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
			int dem = atoi(ds[0].c_str());
			if (ds.size() == 4)
			{
				if (dem == 2)//cac phep toan voi day 01
				{
					QInt a, b, c;
					a = BinToByte(BinStringToBool(ds[1]));
					b = BinToByte(BinStringToBool(ds[3]));

					if (ds[2] == "+")
						c = a + b;
					if (ds[2] == "-")
						c = a - b;
					if (ds[2] == "*")
						c = a * b;
					if (ds[2] == "/")
						c = a / b;
					bool* result = ByteToBin(c);
					for (int i = 0; i < 128; i++)
						g << result[i];
					g << endl;
				}
				if (dem == 16)
				{
					QInt a, b, c;
					a = HexToByte(ds[1]);

					b = HexToByte(ds[3]);

					if (ds[2] == "+")
						c = a + b;
					if (ds[2] == "-")
						c = a - b;
					if (ds[2] == "*")
						c = a * b;
					if (ds[2] == "/")
						c = a / b;
					char* result = ByteToHex(c);
					for (int i = 0; i < 32; i++)
					{
						g << result[i];
					}
					g << endl;
				}
				if (dem == 10)
				{
					QInt a, b;
					string result;
					a = DecToByte(ds[1].c_str());
					int value = atoi(ds[3].c_str());
					if (ds[2] == "<<")
					{
						b = a << value;
						result = ByteToDec(b);
					}
					else if (ds[2] == ">>")
					{
						b = a >> value;
						result = ByteToDec(b);
					}

					g << result;
					g << endl;
				}
			}

			//co 4 cai size bang 3
			if (ds.size() == 3)
			{
				if (dem == 2)
					if (atoi(ds[1].c_str()) == 10)
					{
						QInt a;
						a = BinToByte(BinStringToBool(ds[2]));
						g << ByteToDec(a);
						g << endl;
					}
				if (dem == 10)
					if (atoi(ds[1].c_str()) == 2)
					{
						QInt a;
						a = DecToByte(ds[2].c_str());
						bool* result = ByteToBin(a);
						for (int i = 0; i < 128; i++)
							g << result[i];
						g << endl;
					}
				if (dem == 10)
					if (ds[1].c_str() == "~")
					{
						g << endl;
					}
				if (dem == 2)
					if (atoi(ds[1].c_str()) == 16)
					{
						QInt a;
						a = BinToByte(BinStringToBool(ds[2]));
						char* result = ByteToHex(a);
						for (int i = 0; i < 32; i++)
						{
							g << result[i];
						}
						g << endl;
					}
				if (dem == 10)
					if (atoi(ds[1].c_str()) == 16)
					{
						QInt a;
						a = DecToByte(ds[2].c_str());
						char* result = ByteToHex(a);
						for (int i = 0; i < 32; i++)
						{
							g << result[i];
						}
						g << endl;
					}
			}
		}
	}
}
