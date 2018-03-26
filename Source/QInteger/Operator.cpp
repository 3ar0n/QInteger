#include "Operator.h"
#include "Convert.h"

// Phép cộng - addition
QInt operator + (QInt a, QInt b)
{
	QInt c;
	c.overflow = false;
	if (a.overflow || b.overflow)
		c.overflow = true;
	else
	{
		int tmp = 0; // số nhớ
		for (int i = Base - 1; i >= 0; i--)
		{
			// Thực hiện phép cộng tương tự như cơ số 10, nếu vượt quá 255 thì nhớ 1 cho phép cộng của phần tử đằng trước
			c.data[i] = (a.data[i] + b.data[i] + tmp) % 256;
			tmp = (a.data[i] + b.data[i] + tmp) / 256;
		}
		//if (tmp != 0)
		//	c.overflow = true;
		// Kiểm tra tràn số: nếu a, b cùng dấu mà kết quả c trái dấu với a, b thì tràn số
		if ((a.data[0] <= 127 && b.data[0] <= 127 && c.data[0] > 127) || (a.data[0] > 127 && b.data[0] > 127 && c.data[0] <= 127))
			c.overflow = true;
	}
	return c;
}

// Phép trừ - subtraction
QInt operator - (QInt a, QInt b)
{
	return (a + Minus(b)); // Cộng với số bù 2
}

// Phép nhân - multiplication
QInt operator * (QInt a, QInt b)
{
	/*
		Thuật toán nhân 2 số có dấu
		chuỗi bit [D, a, Q] với chuỗi bit [D] khởi tạo = 0; bit Q = 0 (Q có kiểu bool - 8 bit - nhưng chỉ sử dụng bit cuối để tính toán)
		P là giá trị bit cuối của dãy bit [a] (tương tự như Q - chỉ xét giá trị bit cuối)
		xét giá trị 2 bit PQ để tính (D - b) hoặc (D + b) dựa theo thuật toán nhân
	*/
	QInt D;
	D.overflow = false;
	for (int i = 0; i < Base; i++)
		D.data[i] = 0;

	bool P, Q = 0x0;
	for (int j = 0; j < Base * Byte; j++)
	{
		P = getBit(a.data[Base - 1], 0);
		if (P && !Q)		// PQ = 10
			D = D - b;
		else if (!P && Q)	// PQ = 01
			D = D + b;
		D.overflow = false;

		/* Dịch phải dãy bit [D, a, Q)
			Q nhận giá trị bit cuối hiện tại của a
			Dịch phải toàn bộ 8 bit (trong từng thành phần 16 bytes) của a theo chiều từ phải sang trái
			Giá trị bit7 = giá trị bit0 của byte phía trước ((unsigned char)1 << 7 == 128)
			Riêng bit7 của byte đầu tiên sẽ = giá trị bit0 của byte cuối cùng của D
		*/
		Q = getBit(a.data[Base - 1], 0);
		for (int i = Base - 1; i > 0; i--)	
		{
			a.data[i] = a.data[i] >> 1;
			a.data[i] = a.data[i] + (a.data[i - 1] & 0x1) * 128;
		}
		a.data[0] = a.data[0] >> 1;
		a.data[0] = a.data[0] + (D.data[Base - 1] & 0x1) * 128;
		
		/* Dịch phải D tương tự như với a
			Đối với bit7 của byte đầu tiên phải giữ nguyên dấu (trước và sau khi dịch phải giống nhau)
		*/ 
		for (int i = Base - 1; i > 0; i--)
		{
			D.data[i] = D.data[i] >> 1;
			D.data[i] = D.data[i] + (D.data[i - 1] & 0x1) * 128;
		}
		D.data[0] = D.data[0] >> 1;
		if (getBit(D.data[0], 6) == true)
			D.data[0] = D.data[0] + 128;
	}

	/* Kiểm tra tràn số
		Mặc dù kết quả của phép nhân là [D, a] (16*2 bytes) nhưng chỉ lấy phần kết quả [a] (16 bytes)
		Do đó nếu [D] chỉ toàn dãy bit 1 hoặc 0 => không tràn
	*/
	int k = 0;
	bool theSame = true;
	while (k < Base)
	{
		if (D.data[k] != D.data[0])
		{
			a.overflow = true;
			theSame = false;
			break;
		}
		k++;
	}
	if (theSame)
	{
		if ((D.data[0] == 0 && getBit(a.data[0], 7) == true ) || (D.data[0] == 255 && getBit(a.data[0], 7) == false))
			a.overflow = true;
	}
	return a;
}

// Phép chia - division
QInt operator / (QInt a, QInt b)
{
	/*
		Sử dụng thuật toán chia 2 số không dấu
		=> Chuyển giá trị số bị chia, số chia thành giá trị dương, sau đó đổi dấu thương nếu số bị chia và số chia (ban đầu) trái dấu
	*/
	bool sign = false;
	if ((a.data[0] > 127 && b.data[0] <= 127) || (a.data[0] <= 127 && b.data[0] > 127))
		sign = true;

	// Chuyển sang phép chia 2 số không dấu
	if (a.data[0] > 127)
		a = Minus(a);
	if (b.data[0] > 127)
		b = Minus(b);

	// khởi tạo số c gồm 128 bit 0 (nếu a dương) hoặc 128 bit 1 (nếu a âm)
	QInt c, Sub;
	c.overflow = false;
	unsigned char tmp;
	if (a.data[0] > 127)
		tmp = 255;
	else
		tmp = 0;
	for (int i = 0; i < Base; i++)
		c.data[i] = tmp;

	for (int j = 0; j < Base * Byte; j++)
	{
		// Dịch trái dãy bit [c, a] (tương tự với dịch phải của phép nhân nhưng theo chiều ngược lại - trái/phải, đầu/cuối)
		for (int i = 0; i < Base - 1; i++)
		{
			c.data[i] = c.data[i] << 1;
			c.data[i] += (c.data[i + 1] >> 7) & 0x1;
		}
		c.data[Base - 1] = c.data[Base - 1] << 1;
		c.data[Base - 1] += (a.data[0] >> 7) & 0x1;
		for (int i = 0; i < Base - 1; i++)
		{
			a.data[i] = a.data[i] << 1;
			a.data[i] += (a.data[i + 1] >> 7) & 0x1;
		}
		a.data[Base - 1] = a.data[Base - 1] << 1;

		// Kiểm tra c - b
		Sub = c - b;			// Tính nháp
		if (Sub.data[0] <= 127)	// Tức c - b >= 0
		{
			c = c - b;			// Tính thật
			a.data[Base - 1] += 0x1;
			/*
				Nếu c - b < 0 => bit cuổi của a = 0 (không cần thay đổi vì sau khi dịch trái, bit cuối của a luôn = 0
				Ngược lại, chỉ cần cộng byte cuối của a với bit 1 (hay 0x1)
			*/
		}
	}
	if (sign)
		a = Minus(a);
	return a;
}

// Phép dịch trái
QInt operator << (QInt a, int shift)
{
	/* Để dịch trái số QInt:
		- dịch trái toàn bộ 16 phần tử (1 byte)
		- bit7 của byte phía sau trở thành bit0 của byte phía trước
	=> dịch trái n bit <=> dịch trái n lần 1 bit
	*/
	bool sign = getBit(a.data[0], 7);			// lấy giá trị bit dấu
	int _borrow = 0, _return = 0;
	for (int i = 0; i < shift; i++)				// mỗi lần dịch trái 1 bit
	{
		for (int j = Base - 1; j >= 0; j--)		// dịch trái từng phần tử (8 bits) của QInt từ sau lên trước
		{
			if (a.data[j] > 127)				// nếu bit đầu của phần tử là bit 1 thì nhớ 1 để cộng vào phần tử đằng trước
				_borrow = 1;
			else
				_borrow = 0;
			a.data[j] = (a.data[j] << 1) + _return;
			_return = _borrow;
		}
	}
	if (sign == true != getBit(a.data[0], 7))		// kiểm tra tràn số
		a.overflow = true;
	else
		a.overflow = false;
	return a;
}

// Phép dịch phải
QInt operator >> (QInt a, int shift)
{
	/* Để dịch phải số QInt:
		- dịch phải toàn bộ 16 phần tử (1 byte)
		- bit0 của byte phía trước trở thành bit7 của byte phía sau
		- giữ nguyên bit dấu
	=> dịch phải n bit <=> dịch phải n lần 1 bit
	*/
	bool sign = getBit(a.data[0], 7);
	int _borrow = 0;
	int _return;

	for (int i = 0; i < shift; i++)				// mỗi lần dịch phải 1 bit
	{
		if (sign == true)
			_return = 128;
		else
			_return = 0;

		for (int j = 0; j < Base; j++)			// dịch phải từng phần tử (8 bits) của QInt từ trước ra sau
		{
			if (a.data[j] % 2 != 0)
				_borrow = 128;
			else
				_borrow = 0;
			a.data[j] = (a.data[j] >> 1) + _return;
			_return = _borrow;
		}
	}
	return a;
}

// Toán tử AND
QInt operator & (QInt a, QInt b)
{
	QInt c;
	c.overflow = false;
	for (int i = 0; i < Base; i++)
		c.data[i] = a.data[i] & b.data[i];
	return c;
}

// Toán tử OR
QInt operator | (QInt a, QInt b)
{
	QInt c;
	c.overflow = false;
	for (int i = 0; i < Base; i++)
		c.data[i] = a.data[i] | b.data[i];
	return c;
}

// Toán tử XOR
QInt operator ^ (QInt a, QInt b)
{
	QInt c;
	c.overflow = false;
	for (int i = 0; i < Base; i++)
		c.data[i] = a.data[i] ^ b.data[i];
	return c;
}

// Toán tử NOT
QInt operator ~ (QInt a)
{
	for (int i = 0; i < Base; i++)
		a.data[i] = ~a.data[i];
	return a;
}

// Thực hiện các phép toán 2 ngôi
QInt OperationResult(string operation, QInt a, QInt b, int shift)
{
	QInt c;
	c.overflow = false;

	if (operation == "+")
		c = a + b;
	else if (operation == "-")
		c = a - b;
	else if (operation == "*")
		c = a * b;
	else if (operation == "/")
		c = a / b;
	else if (operation == "&")
		c = a & b;
	else if (operation == "|")
		c = a | b;
	else if (operation == "^")
		c = a ^ b;
	else if (operation == "<<")
		c = a << shift;
	else if (operation == ">>")
		c = a >> shift;
	return c;
}