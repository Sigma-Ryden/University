/*Не підключаючи д00аткових модулів (зокремa, math) та не використовуючи функцій,
виконати наступні завдання (введення вхідних данних реалізувати з клавіатури):*/
#include <iostream>
using namespace std;

int main()
{
	int numb;
	cout << "Hi, I have a couple of tasks:\n\n";
	cout << "\t1. Comparing two numbers.\n" << "\t2. Finding the sum of a series.\n";
	cout << "\t3. Multiply two numbers using the addition operation.\n";
	cout<< "\t4. Division of two numbers using the subtraction operation.\n";

	rs:cout << "\nChoose task: ";
	cin >> numb;
	cout << '\n';

	switch (numb)
	{
	case 1:
	{
		/*Написати программу порівняння двох чисел*/
		float a, b;
		cout << "Please enter value for a and b:\n";

		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;

		if (a > b)
		{
			cout << a << " > " << b << '\n';
		}
		else if (a < b)
		{
			cout << a << " < " << b << '\n';
		}
		else
		{
			cout << a << " = " << b << '\n';
		}
		cout << '\n';
		break;
	}
	case 2:
	{
		/*Написати програму, яка в циклі обчислює суму ряду Sigma [n=1, to N] 3^n*n!/n^n
		із виведенням резулютату суми (не n-го члена) для кожної терації*/
		int N;
		double pow_numb = 1, P_n = 1.0, pow_for3 = 1.0, sum_row = 0.0, sum_row_lv = 0;

		cout << "Enter N for Sigma [n=1, to N] 3^n*n!/n^n : ";
		cin >> N;
		N++;
		for (int pn=1, lv=0; pn!=N; pn++)
		{
			pow_for3 *= 3;
			P_n *= pn;
			do
			{
				pow_numb *= pn;
				lv++;
			} while (lv != pn);
			lv = 0;
			sum_row_lv = pow_for3 * P_n / pow_numb;
			sum_row += pow_for3 * P_n / pow_numb;
			cout << "Sigma [when n= " << pn << "] = " << sum_row_lv << '\n';
			pow_numb = 1.0;
		}
		cout << "Sigma [n=1, to " << --N << "] 3^n*n!/n^n = " << sum_row << '\n';
		break;
	}
	case 3:
	{
		/*Написати програму, яка виконує множення натуральних чисел через
		операцію додавання, не використовуючи при цьому операцію множення*/
		int a, b,b_out, sum = 0;
		cout << "I can solve a*b, please input Natural number a and b:\n";
		
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		b_out = b;

		for (; b > 0; b--) 
		{
			sum += a;
		}
		cout << "Composition: " << a << " * " << b_out << " = " << sum << '\n';
		break;
	}
	case 4:
	{
		/*Написати програму, яка виконує цілочисельне ділення натуральних
		чисел через операцію віднімання, не використовуючи операцію ділення*/
		int a, b, a_out, div = 0;

		cout << "I can solve a/b, please input Natural number a and b:\n";
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		a_out = a;

		while (a > 0)
		{
			a -= b;
			if (a >= 0) div += 1;
		}
		cout << "Integer division a/b - {a/b} : " << a_out << " / " << b << " = " << div << '\n';
		break;
	}
	default:
		cout << "Enter value number from 1 do 4!\n\n";
		goto rs;
	}
	char ans;
	cout << "\nMaybe another task?\nY\\N: ";
	
	do
	{
		cin >> ans;
			if (ans == 'Y') goto rs;
			else if (ans == 'N') break;
			else cout << "Please chose between Y or N: ";
	} while (ans != 'Y' || ans != 'N');

	system("pause");
	return 0;
}