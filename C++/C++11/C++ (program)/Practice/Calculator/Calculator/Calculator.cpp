#include "pch.h"
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	double a, b, c;
	char resl;

	cout << "Введите значение переменной a: ";
	cin >> a;
	cout << "Введите значение переменной b: ";
	cin >> b;
	cout << "Доступные операции над числами { + - * / ^ } выберите одну: ";
	cin >> resl;

	switch (resl)
	{
		case '+':
		{
			c = a + b;
			cout << "a + b = " << c;
			break;
		}
		case '-':
		{
			c = a - b;
			cout << "a - b = " << c;
			break;
		}
		case '*':
		{
			c = a * b;
			cout << "a * b = " << c;
			break;
		}
		case '/':
		{
			if (b != 0)
			{
				c = a / b;
				cout << "a / b = " << c;
				break;
			}
			else cout << "Деление на ноль запрещено!";
		}
		case '^':
		{
			c = pow(a, b);
			cout << "a ^ b = " << c;
			break;
		}
		default: 
			cout << "Введите существующие операции!\n";

	}
	cout << '\n';
	system("pause");
}