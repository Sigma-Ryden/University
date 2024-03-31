//Обчислити суму цифр заданного натурального числа N;
#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int num, i, sum = 0;
	st: cout << "Pleasce input value for N-numbers:";
	cin >> num;
	if (num > 0) {
		for (int y = 1; y <= num; y++) {
			cout << "number#" << y << ":";
			cin >> i;
			sum += i;
		}
		cout << "SUM:" << sum;
	}
	else {
		cout << "Please check confition N-number>0 and try again!\n";
		goto st;
	}

	return 0;
	system("pause");
}