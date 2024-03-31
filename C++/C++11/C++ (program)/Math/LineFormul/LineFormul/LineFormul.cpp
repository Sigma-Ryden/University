#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	float a, b, x;

	cout << "Please input a and b for a*x+b=0:" << endl;
	cin >> a >> b;
	if (a == 0) {
		if (b == 0) {
			cout << "x is R";
		}
		else {
			cout << "X is not R" << endl;
		}
	}
	else {
		x = -b / a;
		cout << "x=" << x;
	}
	return 0;
}