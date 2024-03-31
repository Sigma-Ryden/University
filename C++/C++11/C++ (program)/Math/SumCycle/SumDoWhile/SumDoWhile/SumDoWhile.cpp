#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int NumSt, NumFn, Sum = 0;
	cout << "NumSt and NumFn:" << endl;
	cin >> NumSt >> NumFn;
	if (NumSt < NumFn) {
		do {
			Sum += NumSt;
			NumSt++;
		} while (NumSt <= NumFn);
		cout << "Sum:" << Sum;
	}
	else cout << "Please input value, that NumSt<NumFn and try again!";
	return 0;
}