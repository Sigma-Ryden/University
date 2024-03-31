#include "pch.h"
#include <iostream>

using namespace std;

int main() {

	double a, b, sum = 0, x;

		cout << "Please input volume for a and b:" << endl;
		cin >> a >> b;

		while (a <= b) {
			sum = sum + a;
			a++;
		}
		x = sum / b;
		cout << "sum/n:" << x;

	return 0;
} 